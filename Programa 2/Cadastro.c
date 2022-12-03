#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

/*---------------------------------------------------------Estruturas das listas----------------------------------------------------------------*/

typedef struct{

    char street[64];
    char district[64];
    char number[16];
    char CEP[16];

}Adress;

typedef struct _node{//node representando dados do user

    //dados do user
    int id;
    char name[64];
    Adress adress;
    char type;
    char user;
    char password;

    //ponteiro para o proximo node
    struct _node *next;

    //"trileano" representando os status de salvamento do node
    int onSave;
    //0 -> não gravado
    //1 -> gravado
    //-1 ->removido

}node_user;

typedef struct{//representação da lista

    node_user *begin; //ponteiro para o primeiro node da lista
    node_user *end;    //ponteiro para o ultimo node da lista

} Lista;

/*---------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------Funções para seu "funcionamento"---------------------------------------------------*/

Lista* onCreate(){//cria lista

    //criando a lista (obs; a lista em si é um ponteiro, pois aponta paras os nós)
    Lista *lista = (Lista*) malloc(sizeof(Lista)); 

    if(lista == NULL){//caso não haja memória

        printf("\nMemória insuficiente!\n");
        exit(1); 

    }

    lista->begin = NULL;//setando inicio/fim da lista
    lista->end = NULL;  //(no caso NULL, pois n há elementos)

    return lista; //retornando a lista

}


void insert_user(Lista *lista, node_user *User){

    if(lista == NULL) return;

    //criando node (obs; o node em si é um ponteiro, pois aponta para seus respectivos valores)
    node_user *node = (node_user*) malloc(sizeof(node_user));

    if(node == NULL){//caso não haja memória

        printf("\nMemória insuficiente!\n");
        exit(1); 

    }

    //passando dados para os nós
    node = User;
    /*O ERRO TA NESSA POR%RA*/

    //atualizando posições
    node -> next = lista -> begin;  //o node começa a apontar para o que era o primeiro node (begin)
    lista -> begin = node;          //e ele passa a ser o primeiro node

    if(lista -> begin == NULL){

        //caso o inicio seja nulo n existem nodes
        //portanto esse novo node passa a ser o fim
        lista -> end = node;        

    }
}


//função para recarregar a lista caso haja uma
void reloadList(Lista *lista, FILE *fp){

    int position;
    while(1){
        //while1 pois feof(fp) da mt dor de cabeça

        node_user *node = (node_user*) malloc(sizeof(node_user));
        fread(node , sizeof(node_user), 1, fp);
        //node que anda de espaços de nodes em nodes no arquivo

        if(feof(fp)){
            //chegou ao fim do arquivo
            break;
        }

        if(node -> onSave != -1){
            //se onSave não for -1 significa que o node não foi removido

            //passamos td ao insert
            insert_user(lista, node);
        }
    }   
}

void remove_user(Lista *lista, int id, FILE *fp){

    //lista n criada
    if(lista == NULL){
         printf("\nLista não criada.\n");
         return;
    }
    //n há nodes
    if(lista -> begin == NULL){
        printf("\nNão há users\n");
        return;
    }


    //criando dois nodes auxiliares, 
    node_user *before;
    //(um vai ser o node anterior, e o outro o próximo)

    //este for esta em função do after (ate ele chegar no fim)
    for(node_user *after = lista -> begin; after != NULL; before = after, after = after -> next ){
    //a cada laço, ambos os nodes (after e before) avançam
        
        //achando a matrícula
        if(after -> id == id){

            //caso só tenha UM nó
            if(lista -> begin == lista -> end){

                lista -> begin = NULL;
                lista -> end = NULL;

            }else{
            //caso n

                //se for o primeiro nó
                if(lista -> begin == after){

                    lista -> begin = after -> next;
                    //o inicio pega o proximo nó

                }else if(lista -> end == after){
                
                    lista -> end = before;
                    before -> next = NULL;
                    //o anterior assume o ultimo nó

                }else{

                    //o node anterior passa a apontar para o node da frente do next
                    before -> next = after -> next;

                }
            }
            //em todos os casos, isolamos o node after
            
            //verificando se o node estava no arquivo
            if(after -> onSave == 1){
                fp = fopen(".//data//database.bin", "r+b");
                int i; 
                while(1){
                    
                    node_user *node = (node_user*) malloc(sizeof(node_user));
                    i = ftell(fp);

                    fread(node, sizeof(node_user), 1, fp);

                    if(feof(fp)){
                        break;
                    }
                    if(node -> id == after -> id){
                        //basicmente percorremos o arquivo para subscrever o onSave deste node
                        node -> onSave = -1;
                        printf("%d", node -> onSave);
                        fseek(fp, i, SEEK_SET); 
                        fwrite(node,sizeof(node_user), 1, fp);
                        break;
                    }
                }
                fclose(fp);
            }
    
            free(after);
            //liberamos o node isolado

            printf("\nUser removido com sucesso.\n");
            return;
        }
        

    }//fim do for

    printf("\nuser n? encontrado.\n");
    return;

}

//função para liberar toda a lista da memoria
void onDestroy(Lista *lista){

    //lista n criada
    if(lista == NULL) return;
    //n há nós
    if(lista -> begin == NULL) return;

    node_user *node;
    //se n houver memória
    if(node == NULL){

        printf("\nMem?ria insuficiente!\n");
        exit(1); 

    }

    while(lista -> begin != NULL){

        //aux assume o valor do inicio da lista
        node = lista -> begin;

        //inicio da lista pega o próximo valor (um dps do aux)
        lista -> begin = node -> next;

        //libera aux
        free(node);
    }

    //libera lista
    free(lista);

}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------Main---------------------------------------------------------------------------*/


int main()
{
    Lista *lista = onCreate(); //criando lista
    FILE *fp = fopen(".//data//database.bin", "rb");
    if(fp!=NULL){
        printf("Carregando database.bin...\n\n");
        reloadList(lista, fp);
        printf("Carregada!\n");
    }else{
        printf("Criando database.bin...\n\n");
        fp = fopen(".//data//database.bin", "wb");
        printf("Criada!\n");
    }
    fclose(fp);
    return 0;
}
