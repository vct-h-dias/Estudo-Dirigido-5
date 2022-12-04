#include "Program1Functions.c" 

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



            printf("Digite a Frequ�ncia do(a) aluno(a): ");
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

            //apos escolher uma turma um la�o de repeti��o percorre toda a lista
            //caso tenha os alunos dessa turma suas infos sao printadas
            for(aux = lista -> begin; aux != NULL; aux = aux -> next){

                if(aux -> class == turma){

                    cont++;//contando alunos da turma
                    printf("%d . %s\n", cont, aux -> name);

                }

            }

            //caso o contador for 0, n�o h� alunos daquela turma
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
