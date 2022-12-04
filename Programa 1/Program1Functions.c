#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

/*---------------------------------------------------------Estruturas das listas----------------------------------------------------------------*/

typedef struct _node{//node representando dados do aluno

    //dados do alunos
    char name[50];
    int enrollment;
    float note;
    float frequency;
    char class;
    
    //ponteiro para o proximo node
    struct _node *next;

    //"trileano" representando os status de salvamento do node
    int onSave;
    //0 -> n�o gravado
    //1 -> gravado
    //-1 ->removido

}node_aluno;

typedef struct{//representa��o da lista

    node_aluno *begin; //ponteiro para o primeiro node da lista
    node_aluno *end;    //ponteiro para o ultimo node da lista

} Lista;

/*---------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------Fun��es para seu "funcionamento"---------------------------------------------------*/

Lista* onCreate(){//cria lista

    //criando a lista (obs; a lista em si � um ponteiro, pois aponta paras os n�s)
    Lista *lista = (Lista*) malloc(sizeof(Lista)); 

    if(lista == NULL){//caso n�o haja mem�ria

        printf("\nMemória insuficiente!\n");
        exit(1); 

    }

    lista->begin = NULL;//setando inicio/fim da lista
    lista->end = NULL;  //(no caso NULL, pois n h� elementos)

    return lista; //retornando a lista

}


void insert_aluno(Lista *lista, int mat, char nome[], float nota, float frequencia, char turma, int save){

    /*debug: */
    /* printf("%d\n", mat);
    printf("%s\n", nome);
    printf("%f\n", nota);
    printf("%f\n", frequencia);
    printf("%c\n", turma); */
    //Lista n�o criada
    if(lista == NULL) return;

    //criando node (obs; o node em si � um ponteiro, pois aponta para seus respectivos valores)
    node_aluno *node = (node_aluno*) malloc(sizeof(node_aluno));

    if(node == NULL){//caso n�o haja mem�ria

        printf("\nMem?ria insuficiente!\n");
        exit(1); 

    }

    //passando dados para os n?s
    strcpy(node -> name, nome);
    node -> enrollment = mat;
    node -> note = nota;
    node -> frequency = frequencia;
    node -> class = turma;
    node -> onSave = save;
    

    //atualizando posi��es
    node -> next = lista -> begin;  //o node come�a a apontar para o que era o primeiro node (begin)
    lista -> begin = node;          //e ele passa a ser o primeiro node

    if(lista -> begin == NULL){

        //caso o inicio seja nulo n existem nodes
        //portanto esse novo node passa a ser o fim
        lista -> end = node;        

    }
}


//fun��o para recarregar a lista caso haja uma
void reloadList(Lista *lista, FILE *fp){

    int position;
    while(1){
        //while1 pois feof(fp) da mt dor de cabe�a

        node_aluno *node = (node_aluno*) malloc(sizeof(node_aluno));
        fread(node , sizeof(node_aluno), 1, fp);
        //node que anda de espa�os de nodes em nodes no arquivo

        if(feof(fp)){
            //chegou ao fim do arquivo
            break;
        }

        if(node -> onSave != -1){
            //se onSave n�o for -1 significa que o node n�o foi removido
            int mat = node -> enrollment;
            float nota = node -> note, freq = node -> frequency;
            char nome[50], turma = node -> class;
            int save = node -> onSave;
            strcpy(nome, node -> name);

            //passamos td ao insert
            insert_aluno(lista, mat, nome, nota, freq, turma, save);
        }
    }   
}

void remove_aluno(Lista *lista, int mat, FILE *fp){

    //lista n criada
    if(lista == NULL){
         printf("\nLista não criada.\n");
         return;
    }
    //n h� nodes
    if(lista -> begin == NULL){
        printf("\nNão há alunos\n");
        return;
    }


    //criando dois nodes auxiliares, 
    node_aluno *before;
    //(um vai ser o node anterior, e o outro o pr�ximo)

    //este for esta em fun��o do after (ate ele chegar no fim)
    for(node_aluno *after = lista -> begin; after != NULL; before = after, after = after -> next ){
    //a cada la�o, ambos os nodes (after e before) avan�am
        
        //achando a Matrícula
        if(after -> enrollment == mat){

            //caso s� tenha UM n�
            if(lista -> begin == lista -> end){

                lista -> begin = NULL;
                lista -> end = NULL;

            }else{
            //caso n

                //se for o primeiro n�
                if(lista -> begin == after){

                    lista -> begin = after -> next;
                    //o inicio pega o proximo n�

                }else if(lista -> end == after){
                
                    lista -> end = before;
                    before -> next = NULL;
                    //o anterior assume o ultimo n�

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
                    
                    node_aluno *node = (node_aluno*) malloc(sizeof(node_aluno));
                    i = ftell(fp);

                    fread(node, sizeof(node_aluno), 1, fp);

                    if(feof(fp)){
                        break;
                    }
                    if(node -> enrollment == after -> enrollment){
                        //basicmente percorremos o arquivo para subscrever o onSave deste node
                        node -> onSave = -1;
                        /* printf("%d", node -> onSave); */
                        fseek(fp, i, SEEK_SET); 
                        fwrite(node,sizeof(node_aluno), 1, fp);
                        break;
                    }
                }
                fclose(fp);
            }
    
            free(after);
            //liberamos o node isolado

            printf("\nAluno removido com sucesso.\n");
            return;
        }
        

    }//fim do for

    printf("\nAluno não encontrado.\n");
    return;

}

//fun��o para liberar toda a lista da memoria
void onDestroy(Lista *lista){

    //lista n criada
    if(lista == NULL) return;
    //n h� n�s
    if(lista -> begin == NULL) return;

    node_aluno *node;
    //se n houver mem�ria
    if(node == NULL){

        printf("\nMemória insuficiente!\n");
        exit(1); 

    }

    while(lista -> begin != NULL){

        //aux assume o valor do inicio da lista
        node = lista -> begin;

        //inicio da lista pega o pr�ximo valor (um dps do aux)
        lista -> begin = node -> next;

        //libera aux
        free(node);
    }

    //libera lista
    free(lista);

}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------Fun��es "l�gicas"-------------------------------------------------------------------*/

int Check_Mat(Lista *lista, int mat){

    //lista n criada
    if(lista == NULL){

        printf("\nLista não criada!\n"); 
        return;

    }
    

    node_aluno *i;
    for(i = lista -> begin; i != NULL ; i = i -> next){

        if(i -> enrollment == mat){

            return 1;

        }

    }
    return 0;


}

void print_name(Lista *lista, char nome[]){

    if(lista == NULL){

        printf("\nLista não criada!\n"); 
        return;

    }
    //n�o h� alunos
    if(lista -> begin == NULL){
        printf("\nNão há alunos\n");
        return;
    }

    node_aluno *i;

    for(i = lista -> begin; i != NULL; i = i -> next){

        if(strcmp(nome, i -> name)==0){

            printf("\nMatrícula: %d\n", i -> enrollment);
            printf("Nome: %s\n", i -> name);
            printf("Nota: %.2f\n", i -> note);
            printf("Frequência: %.2f\n", i -> frequency);
            printf("Turma: %c\n", i -> class);
            printf("Salvo: %d\n", i -> onSave);
            printf("\n");
            return;

        }

    }
    
    printf("\nAluno não encontrado!\n");
    return;

}

void print_mat(Lista *lista, int mat){

    if(lista == NULL){

        printf("\nLista não criada!\n"); 
        return;

    }
    //n�o h� alunos
    if(lista -> begin == NULL){
        printf("\nNão há alunos\n");
        return;
    }


    node_aluno *i;

    for(i = lista -> begin; i != NULL; i = i -> next){

        if(i -> enrollment == mat){

            printf("\nMatrícula: %d\n", i -> enrollment);
            printf("Nome: %s\n", i -> name);
            printf("Nota: %.2f\n", i -> note);
            printf("Frequência: %.2f\n", i -> frequency);
            printf("Turma: %c\n", i -> class);
            printf("Salvo: %d\n", i -> onSave);
            printf("\n");
            return;

        }

    }
    
    printf("\nAluno não encontrado!\n");
    return;

}

void Name_Sort(Lista *lista){

    //lista n criada
    if(lista == NULL){
         printf("\nLista não criada.\n");
         return;
    }
    //n h? alunos
    if(lista -> begin == NULL){
        printf("\nNão há alunos\n");
        return;
    }

    if(lista -> begin == lista -> end){

        return;

    }

    node_aluno *j, *i;

    node_aluno *aux = (node_aluno*) malloc(sizeof(node_aluno));
    
    for(i = lista -> begin; i != NULL; i = i -> next ){

        for(j = i -> next; j != NULL; j = j -> next){
            
            if(strcmp(j -> name, i -> name) < 0){

                strcpy(aux -> name, i -> name);
                strcpy(i -> name, j -> name);
                strcpy(j -> name, aux -> name);

                aux -> enrollment = i -> enrollment;
                i -> enrollment = j -> enrollment;
                j -> enrollment = aux -> enrollment;

                aux -> note = i -> note;
                i -> note = j -> note;
                j -> note = aux -> note;

                aux -> frequency = i -> frequency;
                i -> frequency = j -> frequency;
                j -> frequency = aux -> frequency;
        
                aux -> class = i -> class;
                i -> class = j -> class;
                j -> class = aux -> class;
                

            }

        }

    }
    free(aux);

    return;

}



void recordAluno(node_aluno *aluno, FILE *fp){

    /* printf("aluno recorder"); */
    fp = fopen(".//data//database.bin", "r+b");
    if(fp==NULL){
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }
    
    int i; 
    while(1){

        node_aluno *node = (node_aluno*) malloc(sizeof(node_aluno));
        i = ftell(fp);

        fread(node, sizeof(node_aluno), 1, fp);

        if(node -> onSave == -1){
            fseek(fp, i, SEEK_SET); 
            aluno -> onSave = 1;
            fwrite(aluno,sizeof(node_aluno), 1, fp);
            break;
        }

        if(feof(fp)){
            aluno -> onSave = 1;
            fwrite(aluno,sizeof(node_aluno), 1, fp);
            break;
        }
    }

    fclose(fp);
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/