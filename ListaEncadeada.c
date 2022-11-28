#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

//criação listas

typedef struct _node{//node representando dados do aluno

    //dados do alunos
    char name[50];
    int enrollment;
    float note;
    float frequency;
    char class;
    
    //ponteiro para o próximo nó
    struct _node *next;

}node_aluno;

typedef struct{//representação da lista

    node_aluno *begin; //ponteiro para o primeiro nó da lista
    node_aluno *end;    //ponteiro para o últimp nó da lista

} Lista;

//fim das listas


//criação das funções do funcionamento da lista

Lista* onCreate(){//cria lista

    //criando a lista (obs; a lista em si é um ponteiro, pois aponta paras os nós)
    Lista *lista = (Lista*) malloc(sizeof(Lista)); 

    if(lista == NULL){//caso não haja memória

        printf("\nMeméria insuficiente!\n");
        exit(1); 

    }

    lista->begin = NULL;//setando inicio/fim da lista
    lista->end = NULL;  //(no caso NULL, pois n há elementos)

    return lista; //retornando a lista

}

void insert_aluno(Lista *lista, int mat, char nome[], float nota, float frequencia, char turma){

    //lista nó criada
    if(lista == NULL) return;

    //criando nó (obs; o nó em si é um ponteiro, pois aponta para seus respectivos valores)
    node_aluno *node = (node_aluno*) malloc(sizeof(node_aluno));

    if(node == NULL){//caso nó haja meméria

        printf("\nMeméria insuficiente!\n");
        exit(1); 

    }

    //passando dados para os nós
    strcpy(node -> name, nome);
    node -> enrollment = mat;
    node -> note = nota;
    node -> frequency = frequencia;
    node -> class = turma;

    

    //atualizando posições
    node -> next = lista -> begin;  //o nó começa a apontar para o que era o primeiro nó (begin)
    lista -> begin = node;          //e ele passa a ser o primeiro nó

    if(lista -> begin == NULL){

        //caso o inicio seja nulo n existem nós
        //portanto esse novo nó passa a ser o fim
        lista -> end = node;        

    }

    printf("\nAluno cadastrado com sucesso!\n");

}

void remove_aluno(Lista *lista, int mat){

    //lista n criada
    if(lista == NULL){
         printf("\nLista nó criada.\n");
         return;
    }
    //n há nós
    if(lista -> begin == NULL){
        printf("\nnó hé alunos.\n");
        return;
    }


    //criando dois nós auxiliares, 
    node_aluno *before, *after;
    //(um vai ser o nó anterior, e o outro o próximo)

    //este for esta em função do after (ate ele chegar no fim)
    for(after = lista -> begin; after != NULL; before = after, after = after -> next ){
    //a cada laço, ambos os nós (after e before) avançam

        //achando a matrícula
        if(after -> enrollment == mat){

            //caso só tenha UM nó
            if(lista -> begin == lista -> end){

                lista -> begin = NULL;
                lista -> end = NULL;

            }else{
            //caso n

                //se for o primeiro nó
                if(lista -> begin = after){

                    lista -> begin = after -> next;
                    //o inicio pega o próximo nó

                }else if(lista -> end == after){

                    lista -> end = before;
                    before -> next = NULL;
                    //o inicio pega o ultimo nó

                }else{

                    //o nó anterior passa a apontar para o nó da frente do next
                    before -> next = after -> next;

                }
            }
            //em todos os casos, isolamos o nó after

            free(after);
            //liberamos o nó isolado

            printf("\nAluno removido com sucesso.\n");
            return;
        }
        

    }//fim do for

    printf("\nAluno nó encontrado.\n");
    return;

}

void onDestroy(Lista *lista){

    //lista n criada
    if(lista == NULL) return;
    //n há nós
    if(lista -> begin == NULL) return;

    node_aluno *node;
    //se n houver meméria
    if(node == NULL){

        printf("\nMeméria insuficiente!\n");
        exit(1); 

    }

    while(lista -> begin != NULL){

        //aux assume o valor do inicio da lista
        node = lista -> begin;

        //inicio da lista pega o préximo valor (um dps do aux)
        lista -> begin = node -> next;

        //libera aux
        free(node);
    }

    //libera lista
    free(lista);

}
//fim das funções do funcionamento da lista



//funções logicas

int Check_Mat(Lista *lista, int mat){

    //lista n criada
    if(lista == NULL){

        printf("\nLista nó criada!\n"); 
        return;

    }
    //n há alunos
    if(lista -> begin == NULL){
        printf("\nnó hé alunos.\n");
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

        printf("\nLista nó criada!\n"); 
        return;

    }
    //nó há alunos
    if(lista -> begin == NULL){
        printf("\nnó hé alunos.\n");
        return;
    }

    node_aluno *i;

    for(i = lista -> begin; i != NULL; i = i -> next){

        if(strcmp(nome, i -> name)==0){

            printf("\nMatrécula: %d\n", i -> enrollment);
            printf("Nome: %s\n", i -> name);
            printf("Nota: %.2f\n", i -> note);
            printf("Frequéncia: %.2f\n", i -> frequency);
            printf("Turma: %c\n", i -> class);
            printf("\n");
            return;

        }

    }
    
    printf("\nAluno nó encontrado!\n");
    return;

}

void print_mat(Lista *lista, int mat){

    if(lista == NULL){

        printf("\nLista nó criada!\n"); 
        return;

    }
    //n há alunos
    if(lista -> begin == NULL){
        printf("\nnó hé alunos.\n");
        return;
    }


    node_aluno *i;

    for(i = lista -> begin; i != NULL; i = i -> next){

        if(i -> enrollment == mat){

            printf("\nMatrécula: %d\n", i -> enrollment);
            printf("Nome: %s\n", i -> name);
            printf("Nota: %.2f\n", i -> note);
            printf("Frequéncia: %.2f\n", i -> frequency);
            printf("Turma: %c\n", i -> class);
            printf("\n");
            return;

        }

    }
    
    printf("\nAluno nó encontrado!\n");
    return;

}

void Name_Sort(Lista *lista){

    //lista n criada
    if(lista == NULL){
         printf("\nLista nó criada.\n");
         return;
    }
    //n há alunos
    if(lista -> begin == NULL){
        printf("\nnó hé alunos.\n");
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

lista_print(Lista *lista){

    //lista n criada
    if(lista == NULL){
         printf("\nLista nó criada.\n");
         return;
    }
    //nó há alunos
    if(lista -> begin == NULL){
        printf("\nnó hé alunos.\n");
        return;
    }

    for(node_aluno *i = lista -> begin; i != NULL; i = i-> next){

        printf("%s\n", i -> name);

    }
    return;

}

//fim das funções légicas

int main()
{
    setlocale(LC_ALL, "portuguese");
    int o=0;
    char nome[50], name[50], turma;
    int mat,m;
    float frequencia, nota;
    node_aluno *aux;
    int cont=0;
    int big = -0.01, little = 10.01;
    
    Lista *lista = onCreate(); //criando lista

    do
    {
        
        printf("Escolha uma opééo:\n\n");
        printf("1. Cadastrar aluno no inócio da lista;\n");
        printf("2. Remover aluno;\n");
        printf("3. Pesquisar aluno pelo nome;\n");
        printf("4. Pesquisar aluno por matrécula;\n");
        printf("5. Mostrar todos os alunos de uma turma;\n");
        printf("6. Ordenar toda a lista de alunos por nome;\n");
        printf("7. Mostrar os alunos com a maior e menor nota;\n");
        printf("8. Sair.\n");
        printf("\nDigite sua opééo:");
        scanf("%d",&o);
        printf("\n");
        

        switch (o){

        case 1:

            system("pause");
            system("cls");
            
            printf("1 . Cadastrar aluno:\n\n");


            printf("Digite a matrécula do(a) aluno(a): ");
            scanf("%d",&mat);
            while(mat>99999||mat<0){
                printf("Matrécula invélida, séo aceitos nómeros entre 0 e 99999\nInsira uma matrécula vélida: ");
                scanf("%d",&mat);
            }
            //checagem de matrécula
            while(Check_Mat(lista,mat)==1){
                printf("Matrécula jé cadastrada!\nInsira outro nómero de matrécula:");
                scanf("%d",&mat);
            }
                    

            printf("Digite o nome do(a) aluno(a): ");
            setbuf(stdin,NULL);
            gets(nome);


            printf("Digite a nota do(a) aluno(a): ");
            scanf("%f",&nota);
            while(nota>10.0||nota<0.0){
                printf("Nota invélida, séo aceitos nómeros entre 0,0 e 10,0\nInsira uma nota vélida: ");
                scanf("%f",&nota);
            }



            printf("Digite a frequéncia do(a) aluno(a): ");
            scanf("%f",&frequencia);
            while(frequencia>100.0||frequencia<0.0){
                printf("Frequéncia invélida, séo aceitos nómeros entre 0,0 e 100,0\nInsira uma frequéncia vélida: ");
                scanf("%f",&frequencia);
            }
            setbuf(stdin,NULL);



            printf("Digite A para aluno(a) na turma A ou B para aluno(a) na turma B: ");
            scanf("%c",&turma);
            setbuf(stdin,NULL);
            while(turma!='A'&&turma!='B'){
                printf("Turma invélida, séo aceitos os caracteres 'A' e 'B'\nInsira uma turma vélida: ");
                scanf("%c",&turma);
                setbuf(stdin,NULL);
            }

            //inserindo dados na lista
            insert_aluno(lista,mat,nome,nota,frequencia,turma);

            system("pause");
            system("cls");
            
            break;
        

        case 2:

            system("pause");
            system("cls");

            printf("2 . Remover Aluno:\n\n");

            printf("Digite o nómero de matrécula do aluno que seré removido: ");
            scanf("%d",&m);
        
            //apos ler a mat removemos ela
            remove_aluno(lista,m);
            
            system("pause");
            system("cls");

            break;
        

        case 3:

            system("pause");
            system("cls");

            printf("3 . Pesquisar aluno pelo nome:\n\n");

            printf("Digite o nome do aluno que seré pesquisado: ");
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

            printf("4 . Pesquisar aluno pela matrécula:\n\n");

            printf("Digite a matrécula do aluno que seré pesquisado: ");
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
                printf("Turma invélida, séo aceitos os caracteres 'A' e 'B'\nInsira uma turma vélida: ");
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

                printf("nó existem alunos nessa turma!\n");

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
                printf("    Matrécula: %d\n", i -> enrollment);
                printf("    Nota: %.2f\n", i -> note);
                printf("    Frequéncia: %.2f%\n", i -> frequency);
                printf("    Turma: %c\n\n", i -> class);

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
        
            printf("Vocé saiu do programa...\n");
            onDestroy(lista);//liberamos a lista

            break;

        default:
            
            //caso a entrada n for válida
            printf("Insira uma opééo vélida!\n");

            break;
        }



    } while(o!=8);
    
    

    return 0;
}
