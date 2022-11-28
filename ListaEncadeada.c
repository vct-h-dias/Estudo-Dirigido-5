#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

//criaï¿½ï¿½o listas/nï¿½s

typedef struct _node{//node representando dados do aluno

    //dados do alunos
    char name[50];
    int enrollment;
    float note;
    float frequency;
    char class;
    
    //ponteiro para o prï¿½ximo nï¿½
    struct _node *next;

}node_aluno;

typedef struct{//representaï¿½ï¿½o da lista

    node_aluno *begin; //ponteiro para o primeiro nï¿½ da lista
    node_aluno *end;    //ponteiro para o ï¿½ltimo nï¿½ da lista

} Lista;

//fim das listas/nï¿½s


//criaï¿½ï¿½o das funï¿½ï¿½es do funcionamento da lista

Lista* onCreate(){//cria lista

    //criando a lista (obs; a lista em si ï¿½ um ponteiro, pois aponta paras os nï¿½s)
    Lista *lista = (Lista*) malloc(sizeof(Lista)); 

    if(lista == NULL){//caso nï¿½o haja memï¿½ria

        printf("\nMemória insuficiente!\n");
        exit(1); 

    }

    lista->begin = NULL;//setando inicio/fim da lista
    lista->end = NULL;  //(no caso NULL, pois n hï¿½ elementos)

    return lista; //retornando a lista

}

void insert_aluno(Lista *lista, int mat, char nome[], float nota, float frequencia, char turma){

    //lista nï¿½o criada
    if(lista == NULL) return;

    //criando nï¿½ (obs; o nï¿½ em si ï¿½ um ponteiro, pois aponta para seus respectivos valores)
    node_aluno *node = (node_aluno*) malloc(sizeof(node_aluno));

    if(node == NULL){//caso nï¿½o haja memï¿½ria

        printf("\nMemória insuficiente!\n");
        exit(1); 

    }

    //passando dados para os nï¿½s
    strcpy(node -> name, nome);
    node -> enrollment = mat;
    node -> note = nota;
    node -> frequency = frequencia;
    node -> class = turma;

    

    //atualizando posiï¿½ï¿½es
    node -> next = lista -> begin;  //o nï¿½ comeï¿½a a apontar para o que era o primeiro nï¿½ (begin)
    lista -> begin = node;          //e ele passa a ser o primeiro nï¿½

    if(lista -> begin == NULL){

        //caso o inicio seja nulo nï¿½o existem nï¿½s
        //portanto esse novo nï¿½ passa a ser o fim
        lista -> end = node;        

    }

    printf("\nAluno cadastrado com sucesso!\n");

}

void remove_aluno(Lista *lista, int mat){

    //lista nï¿½o criada
    if(lista == NULL){
         printf("\nLista não criada.\n");
         return;
    }
    //nï¿½o hï¿½ nï¿½s
    if(lista -> begin == NULL){
        printf("\nNão há alunos.\n");
        return;
    }


    //criando dois nï¿½s auxiliares, 
    node_aluno *before, *after;
    //(um vai ser o nï¿½ anterior, e o outro o prï¿½ximo)

    //este for esta em funï¿½ï¿½o do after (ate ele chegar no fim)
    for(after = lista -> begin; after != NULL; before = after, after = after -> next ){
    //a cada laï¿½o, ambos os nï¿½s (after e before) avanï¿½a

        //achando a matrï¿½cula
        if(after -> enrollment == mat){

            //caso sï¿½ tenha UM nï¿½
            if(lista -> begin == lista -> end){

                lista -> begin = NULL;
                lista -> end = NULL;

            }else{
            //caso nï¿½o

                //se for o primeiro nï¿½
                if(lista -> begin = after){

                    lista -> begin = after -> next;
                    //o inicio pega o prï¿½ximo nï¿½

                }else if(lista -> end == after){

                    lista -> end = before;
                    before -> next = NULL;
                    //o inicio pega o ultimo nï¿½

                }else{

                    //o nï¿½ anterior passa a apontar para o nï¿½ da frente do next
                    before -> next = after -> next;

                }
            }
            //em todos os casos, isolamos o nï¿½ after

            free(after);
            //liberamos o nï¿½ isolado

            printf("\nAluno removido com sucesso.\n");
            return;
        }
        

    }//fim do for

    printf("\nAluno não encontrado.\n");
    return;

}

void onDestroy(Lista *lista){

    //lista nï¿½o criada
    if(lista == NULL) return;
    //nï¿½o hï¿½ nï¿½s
    if(lista -> begin == NULL) return;

    node_aluno *node;
    //se nï¿½o houver memï¿½ria
    if(node == NULL){

        printf("\nMemória insuficiente!\n");
        exit(1); 

    }

    while(lista -> begin != NULL){

        //aux assume o valor do inicio da lista
        node = lista -> begin;

        //inicio da lista pega o prï¿½ximo valor (um dps do aux)
        lista -> begin = node -> next;

        //libera aux
        free(node);
    }

    //libera lista
    free(lista);

}
//fim das funï¿½ï¿½es do funcionamento da lista



//funï¿½ï¿½es logicas

int Check_Mat(Lista *lista, int mat){

    //lista nï¿½o criada
    if(lista == NULL){

        printf("\nLista não criada!\n"); 
        return;

    }
    //nï¿½o hï¿½ alunos
    if(lista -> begin == NULL){
        printf("\nNão há alunos.\n");
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
    //nï¿½o hï¿½ alunos
    if(lista -> begin == NULL){
        printf("\nNão há alunos.\n");
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
    //nï¿½o hï¿½ alunos
    if(lista -> begin == NULL){
        printf("\nNão há alunos.\n");
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
            printf("\n");
            return;

        }

    }
    
    printf("\nAluno não encontrado!\n");
    return;

}

void Name_Sort(Lista *lista){

    //lista não criada
    if(lista == NULL){
         printf("\nLista não criada.\n");
         return;
    }
    //não há alunos
    if(lista -> begin == NULL){
        printf("\nNão há alunos.\n");
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

    //lista não criada
    if(lista == NULL){
         printf("\nLista não criada.\n");
         return;
    }
    //não há alunos
    if(lista -> begin == NULL){
        printf("\nNão há alunos.\n");
        return;
    }

    for(node_aluno *i = lista -> begin; i != NULL; i = i-> next){

        printf("%s\n", i -> name);

    }
    return;

}

//fim das funï¿½ï¿½es lï¿½gicas

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
        
        printf("Escolha uma opção:\n\n");
        printf("1. Cadastrar aluno no início da lista;\n");
        printf("2. Remover aluno;\n");
        printf("3. Pesquisar aluno pelo nome;\n");
        printf("4. Pesquisar aluno por matrícula;\n");
        printf("5. Mostrar todos os alunos de uma turma;\n");
        printf("6. Ordenar toda a lista de alunos por nome;\n");
        printf("7. Mostrar os alunos com a maior e menor nota;\n");
        printf("8. Sair.\n");
        printf("\nDigite sua opção:");
        scanf("%d",&o);
        printf("\n");
        

        switch (o){

        case 1:

            system("pause");
            system("cls");
            
            printf("1 . Cadastrar aluno:\n\n");


            printf("Digite a matrícula do(a) aluno(a): ");
            scanf("%d",&mat);
            while(mat>99999||mat<0){
                printf("Matrícula inválida, são aceitos números entre 0 e 99999\nInsira uma matrícula válida: ");
                scanf("%d",&mat);
            }
            //checagem de matrï¿½cula
            while(Check_Mat(lista,mat)==1){
                printf("Matrícula já cadastrada!\nInsira outro número de matrícula:");
                scanf("%d",&mat);
            }
                    

            printf("Digite o nome do(a) aluno(a): ");
            setbuf(stdin,NULL);
            gets(nome);


            printf("Digite a nota do(a) aluno(a): ");
            scanf("%f",&nota);
            while(nota>10.0||nota<0.0){
                printf("Nota inválida, sâo aceitos números entre 0,0 e 10,0\nInsira uma nota válida: ");
                scanf("%f",&nota);
            }



            printf("Digite a frequï¿½ncia do(a) aluno(a): ");
            scanf("%f",&frequencia);
            while(frequencia>100.0||frequencia<0.0){
                printf("Frequência inválida, são aceitos números entre 0,0 e 100,0\nInsira uma frequência válida: ");
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
            insert_aluno(lista,mat,nome,nota,frequencia,turma);

            system("pause");
            system("cls");
            
            break;
        

        case 2:

            system("pause");
            system("cls");

            printf("2 . Remover Aluno:\n\n");

            printf("Digite o número de matrícula do aluno que será removido: ");
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

            printf("4 . Pesquisar aluno pela matrícula:\n\n");

            printf("Digite a matrícula do aluno que será pesquisado: ");
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

            //caso o contador for 0, não alunos daquela turma
            if(cont==0){

                printf("Não existem alunos nessa turma!\n");

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
        
            printf("Você saiu do programa...\n");
            onDestroy(lista);//liberamos a lista

            break;

        default:
            
            //caso a entrada não for válida
            printf("Insira uma opção válida!\n");

            break;
        }



    } while(o!=8);
    
    

    return 0;
}
