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
    //0 -> não gravado
    //1 -> gravado
    //-1 ->removido

}node_aluno;

typedef struct{//representação da lista

    node_aluno *begin; //ponteiro para o primeiro node da lista
    node_aluno *end;    //ponteiro para o ultimo node da lista

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


void insert_aluno(Lista *lista, int mat, char nome[], float nota, float frequencia, char turma, int save){

    /*debug: */
    /* printf("%d\n", mat);
    printf("%s\n", nome);
    printf("%f\n", nota);
    printf("%f\n", frequencia);
    printf("%c\n", turma); */
    //Lista não criada
    if(lista == NULL) return;

    //criando node (obs; o node em si é um ponteiro, pois aponta para seus respectivos valores)
    node_aluno *node = (node_aluno*) malloc(sizeof(node_aluno));

    if(node == NULL){//caso não haja memória

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

        node_aluno *node = (node_aluno*) malloc(sizeof(node_aluno));
        fread(node , sizeof(node_aluno), 1, fp);
        //node que anda de espaços de nodes em nodes no arquivo

        if(feof(fp)){
            //chegou ao fim do arquivo
            break;
        }

        if(node -> onSave != -1){
            //se onSave não for -1 significa que o node não foi removido
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
    //n há nodes
    if(lista -> begin == NULL){
        printf("\nNão há alunos\n");
        return;
    }


    //criando dois nodes auxiliares, 
    node_aluno *before;
    //(um vai ser o node anterior, e o outro o próximo)

    //este for esta em função do after (ate ele chegar no fim)
    for(node_aluno *after = lista -> begin; after != NULL; before = after, after = after -> next ){
    //a cada laço, ambos os nodes (after e before) avançam
        
        //achando a matrícula
        if(after -> enrollment == mat){

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

    printf("\nAluno n? encontrado.\n");
    return;

}

//função para liberar toda a lista da memoria
void onDestroy(Lista *lista){

    //lista n criada
    if(lista == NULL) return;
    //n há nós
    if(lista -> begin == NULL) return;

    node_aluno *node;
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



/*--------------------------------------------------------------Funções "lógicas"-------------------------------------------------------------------*/

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
    //não há alunos
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
    
    printf("\nAluno n? encontrado!\n");
    return;

}

void print_mat(Lista *lista, int mat){

    if(lista == NULL){

        printf("\nLista não criada!\n"); 
        return;

    }
    //não há alunos
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


/*-------------------------------------------------------------------Main---------------------------------------------------------------------------*/

int main()
{
    setlocale(LC_ALL, "portuguese");
    int o=0;
    char nome[50], name[50], turma, g;
    int mat,m;
    float frequencia, nota;
    node_aluno *aux;
    int cont=0;
    int big = -0.01, little = 10.01;
    
    Lista *lista = onCreate(); //criando lista
    FILE *fp = fopen(".//data//database.bin", "rb");
    if(fp!=NULL){
        reloadList(lista, fp);
    }else{
        fp = fopen(".//data//database.bin", "wb");
    }
    fclose(fp);

    do
    {
        
        printf("Escolha uma opção:\n\n");
        printf("1. Cadastrar aluno no início da lista;\n");
        printf("2. Remover aluno;\n");
        printf("3. Pesquisar aluno pelo nome;\n");
        printf("4. Pesquisar aluno por Matrícula;\n");
        printf("5. Mostrar todos os alunos de uma turma;\n");
        printf("6. Ordenar toda a lista de alunos por nome;\n");
        printf("7. Mostrar os alunos com a maior e menor nota;\n");
        printf("8. Gravar no arquivo;\n");
        printf("9. Sair.\n");
        printf("\nDigite sua opção:");
        scanf("%d",&o);
        printf("\n");
        

        switch (o){

        case 1:

            system("pause");
            system("cls");
            
            printf("1 . Cadastrar aluno:\n\n");


            printf("Digite a Matrícula do(a) aluno(a): ");
            scanf("%d",&mat);
            while(mat>99999||mat<0){
                printf("Matrícula inválida, são aceitos números entre 0 e 99999\nInsira uma Matrícula válida: ");
                scanf("%d",&mat);
            }
            //checagem de Matrícula
            while(Check_Mat(lista,mat)==1){
                printf("Matrícula já cadastrada!\nInsira outro número de Matrícula:");
                scanf("%d",&mat);
            }
                    

            printf("Digite o nome do(a) aluno(a): ");
            setbuf(stdin,NULL);
            gets(nome);


            printf("Digite a nota do(a) aluno(a): ");
            scanf("%f",&nota);
            while(nota>10.0||nota<0.0){
                printf("Nota inválida, são aceitos números entre 0,0 e 10,0\nInsira uma nota válida: ");
                scanf("%f",&nota);
            }



            printf("Digite a Frequência do(a) aluno(a): ");
            scanf("%f",&frequencia);
            while(frequencia>100.0||frequencia<0.0){
                printf("Frequência inválida, são aceitos números entre 0,0 e 100,0\nInsira uma Frequência válida: ");
                scanf("%f",&frequencia);
            }
            setbuf(stdin,NULL);



            printf("Digite A para aluno(a) na turma A ou B para aluno(a) na turma B: ");
            scanf("%c",&turma);
            setbuf(stdin,NULL);
            while(turma!='A'&&turma!='B'){
                printf("Turma inválida, são aceitos os caracteres 'A' e 'B'\nInsira uma turma válida: ");
                scanf("%c",&turma);
                setbuf(stdin,NULL);
            }

            //inserindo dados na lista
            insert_aluno(lista,mat,nome,nota,frequencia,turma, 0);
            printf("\nAluno cadastrado com sucesso!\n");

            printf("Deseja salvar o aluno?\n");
            scanf("%c", &g);
            setbuf(stdin,NULL);
            while(g!='S'&&g!='s'&&g!='N'&&g!='n'){
                printf("Opção inválida são aceitos apenas os caracteres 'S'/'s' ou 'N'/'n'\nInsira uma Opção válida: ");
                scanf("%c",&g);
                setbuf(stdin,NULL);
            }

            if(g == 'S' || g == 's'){
                recordAluno(lista -> begin, fp); 
            }else{
                lista -> begin -> onSave = 0;
            }

            system("pause");
            system("cls");
            
            break;
        

        case 2:

            system("pause");
            system("cls");

            printf("2 . Remover Aluno:\n\n");

            printf("Digite o número de Matrícula do aluno que será removido: ");
            scanf("%d",&m);
        
            //apos ler a mat removemos ela
            remove_aluno(lista, m, fp);
            
            system("pause");
            system("cls");

            break;
        

        case 3:

            system("pause");
            system("cls");

            printf("3 . Pesquisar aluno pelo nome:\n\n");

            printf("Digite o nome do aluno que será pesquisado: ");
            setbuf(stdin,NULL);
            gets(name);

            //apos ler o nome printamos ele
            print_name(lista,name);
            
            system("pause");
            system("cls");

            break;
        

        case 4:

            system("pause");
            system("cls");

            printf("4 . Pesquisar aluno pela Matrícula:\n\n");

            printf("Digite a Matrícula do aluno que será pesquisado: ");
            scanf("%d", &mat);

            //apos ler a mat printamos ela
            print_mat(lista,mat);
            
            system("pause");
            system("cls");

            break;
        

        case 5:

            system("pause");
            system("cls");

            printf("5 . Mostrar todos os alunos de uma turma:\n\n");

            setbuf(stdin,NULL);
            printf("Digite a turma: ");
            scanf("%c",&turma);
            setbuf(stdin,NULL);
            while(turma!='A'&&turma!='B'){
                printf("Turma inválida, são aceitos os caracteres 'A' e 'B'\nInsira uma turma válida: ");
                scanf("%c",&turma);
                setbuf(stdin,NULL);
            }

            printf("\n");

            //apos escolher uma turma um laço de repetição percorre toda a lista
            //caso tenha os alunos dessa turma suas infos sao printadas
            for(aux = lista -> begin; aux != NULL; aux = aux -> next){

                if(aux -> class == turma){

                    cont++;//contando alunos da turma
                    printf("%d . %s\n", cont, aux -> name);

                }

            }

            //caso o contador for 0, não há alunos daquela turma
            if(cont==0){

                printf("n? existem alunos nessa turma!\n");

            }

            printf("\n");
            cont = 0;

            system("pause");
            system("cls");

            break;
        
        case 6:

            system("pause");
            system("cls");

            printf("6 . Ordenar toda a lista de alunos por nome;\n\n");

            Name_Sort(lista);//ordena a lista
            
            
            cont = 1;//(contador apenas para numerar os alunos)
            //imprimimos a lista
            for(node_aluno *i = lista -> begin; i != NULL ; i = i -> next){

                printf("%d. Nome: %s\n", cont, i -> name);
                printf("    Matrícula: %d\n", i -> enrollment);
                printf("    Nota: %.2f\n", i -> note);
                printf("    Frequência: %.2f%\n", i -> frequency);
                printf("    Turma: %c\n", i -> class);
                printf("    Salvo: %d\n\n", i -> onSave);

                cont++;
            }
            cont = 0;
            
            system("pause");
            system("cls");

            break;

        case 7:

            system("pause");
            system("cls");

            printf("7 . Mostrar os alunos com a maior e menor nota;\n\n");

            //percorremos a lista definindo a maior nota (big) e menor nota (little)
            for(node_aluno *i = lista -> begin; i != NULL ; i = i -> next){

                if(i -> note > big){
                    big = i -> note;
                }

                if(i -> note < little){
                    little = i -> note;
                }

            }

            printf("Menor(es):\n");
            //percorremos dnv e printamos todos aqueles com aquela nota
            for(node_aluno *i = lista -> begin; i != NULL ; i = i -> next){

                if(i -> note == little){
                    printf("%.2f . %s\n", i -> note, i -> name);
                    cont++;
                }

            }
            

            printf("\nMaior(es):\n");
            //percorremos dnv e printamos todos aqueles com aquela nota
            for(node_aluno *i = lista -> begin; i != NULL ; i = i -> next){

                if(i -> note == big){
                    printf("%.2f . %s\n", i -> note, i -> name);
                    
                }

            }
            
            printf("\n");
            system("pause");
            system("cls");
            
            break;        
        
        case 8:
        
            system("pause");
            system("cls");

            printf("8 . Gravar no arquivo;\n\n");
            
            fp = fopen(".//data//database.bin", "rb");

            if(fp==NULL){
                printf("\nErro ao abrir o arquivo!\n");
            }

            node_aluno *i = (node_aluno*) malloc(sizeof(node_aluno));
            for(i = lista -> begin ; i != NULL ; i = i -> next){

                if( i -> onSave == 0){

                    recordAluno(i,fp);

                }

            }
            fclose(fp);
            printf("Mudanças salvas!");

            printf("\n");
            system("pause");
            system("cls");
            break;

        case 9:
        
            printf("Você saiu do programa...\n");
            onDestroy(lista);//liberamos a lista

            break;



        default:
            
            //caso a entrada n for válida
            printf("Insira uma opção válida!\n");

            break;
        }



    } while(o!=9);
    
    

    return 0;
}
