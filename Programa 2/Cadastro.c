#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

/*---------------------------------------------------------Estruturas das listas----------------------------------------------------------------*/

typedef struct
{
    char street[64];
    char district[64];
    char number[16];
    char CEP[32];

} Adress;

typedef struct _node
{ // node representando dados do user

    // dados do user
    int id;
    char name[64];
    Adress adress;
    char type;
    char user[64];
    char password[257]; // sha256 + 1

    // ponteiro para o proximo node
    struct _node *next;

    //"trileano" representando os status de salvamento do node
    int onSave;
    // 0 -> não gravado
    // 1 -> gravado
    //-1 -> removido

} node_user;

typedef struct
{ // representação da lista

    node_user *begin; // ponteiro para o primeiro node da lista
    node_user *end;   // ponteiro para o ultimo node da lista

} Lista;

/*---------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------Funções para seu "funcionamento"---------------------------------------------------*/

Lista *onCreate()
{ // cria lista

    // criando a lista (obs; a lista em si é um ponteiro, pois aponta paras os nós)
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    if (lista == NULL)
    { // caso não haja memória

        printf("\nMemória insuficiente!\n");
        exit(1);
    }

    lista->begin = NULL; // setando inicio/fim da lista
    lista->end = NULL;   //(no caso NULL, pois n há elementos)

    return lista; // retornando a lista
}

void insert_user(Lista *lista, node_user *User)
{

    if (lista == NULL)
        return;

    // criando node (obs; o node em si é um ponteiro, pois aponta para seus respectivos valores)
    node_user *node = (node_user *)malloc(sizeof(node_user));

    if (node == NULL)
    { // caso não haja memória

        printf("\nMemória insuficiente!\n");
        exit(1);
    }
    // passando dados para os nós
    node = User;
    /*O ERRO TA NESSA POR%RA*/

    // atualizando posições
    node->next = lista->begin; // o node começa a apontar para o que era o primeiro node (begin)
    lista->begin = node;       // e ele passa a ser o primeiro node

    if (lista->begin == NULL)
    {

        // caso o inicio seja nulo n existem nodes
        // portanto esse novo node passa a ser o fim
        lista->end = node;
    }
}

// função para recarregar a lista caso haja uma
void reloadList(Lista *lista, FILE *fp)
{

    int position;
    while (1)
    {
        // while1 pois feof(fp) da mt dor de cabeça

        node_user *node = (node_user *)malloc(sizeof(node_user));
        fread(node, sizeof(node_user), 1, fp);
        // node que anda de espaços de nodes em nodes no arquivo

        if (feof(fp))
        {
            // chegou ao fim do arquivo
            break;
        }

        printf("\n%d", node->onSave);
        if (node->onSave != -1)
        {
            /* printf("\n%d", node -> onSave); */
            // se onSave não for -1 significa que o node não foi removido

            // passamos td ao insert
            insert_user(lista, node);
        }
    }
}

void remove_user(Lista *lista, int id, FILE *fp)
{

    // lista n criada
    if (lista == NULL)
    {
        printf("\nLista não criada.\n");
        return;
    }
    // n há nodes
    if (lista->begin == NULL)
    {
        printf("\nNão há users\n");
        return;
    }

    // criando dois nodes auxiliares,
    node_user *before;
    //(um vai ser o node anterior, e o outro o próximo)

    // este for esta em função do after (ate ele chegar no fim)
    for (node_user *after = lista->begin; after != NULL; before = after, after = after->next)
    {
        // a cada laço, ambos os nodes (after e before) avançam

        // achando a matrícula
        if (after->id == id)
        {

            // caso só tenha UM nó
            if (lista->begin == lista->end)
            {

                lista->begin = NULL;
                lista->end = NULL;
            }
            else
            {
                // caso n

                // se for o primeiro nó
                if (lista->begin == after)
                {

                    lista->begin = after->next;
                    // o inicio pega o proximo nó
                }
                else if (lista->end == after)
                {

                    lista->end = before;
                    before->next = NULL;
                    // o anterior assume o ultimo nó
                }
                else
                {

                    // o node anterior passa a apontar para o node da frente do next
                    before->next = after->next;
                }
            }
            // em todos os casos, isolamos o node after

            // verificando se o node estava no arquivo
            /* printf("\n%d\n", after -> onSave); */
            if (after->onSave == 1)
            {
                fp = fopen(".//data//database.bin", "r+b");
                int i;
                while (1)
                {

                    node_user *node = (node_user *)malloc(sizeof(node_user));
                    i = ftell(fp);

                    fread(node, sizeof(node_user), 1, fp);

                    if (feof(fp))
                    {
                        break;
                    }
                    if (node->id == after->id)
                    {
                        // basicmente percorremos o arquivo para subscrever o onSave deste node
                        node->onSave = -1;
                        printf("%d", node->onSave);
                        fseek(fp, i, SEEK_SET);
                        fwrite(node, sizeof(node_user), 1, fp);
                        break;
                    }
                }
                fclose(fp);
            }

            free(after);
            // liberamos o node isolado

            printf("\nUser removido com sucesso.\n");
            return;
        }

    } // fim do for

    printf("\nuser n? encontrado.\n");
    return;
}

// função para liberar toda a lista da memoria
void onDestroy(Lista *lista)
{

    // lista n criada
    if (lista == NULL)
        return;
    // n há nós
    if (lista->begin == NULL)
        return;

    node_user *node;
    // se n houver memória
    if (node == NULL)
    {

        printf("\nMem?ria insuficiente!\n");
        exit(1);
    }

    while (lista->begin != NULL)
    {

        // aux assume o valor do inicio da lista
        node = lista->begin;

        // inicio da lista pega o próximo valor (um dps do aux)
        lista->begin = node->next;

        // libera aux
        free(node);
    }

    // libera lista
    free(lista);
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------Funções "lógicas"------------------------------------------------------------------*/

int id_disponivel(Lista *lista)
{

    int cont = 0, loop = 1;

    while (loop)
    {
        loop = 0;
        for (node_user *i = lista->begin; i != NULL; i = i->next)
        {
            if (i->id == cont)
            {
                cont++;
                loop = 1;
            }
        }
    }

    return cont;
}

int Check_Mat(Lista *lista, int nome)
{

    // lista n criada
    if (lista == NULL)
    {

        printf("\nLista n�o criada!\n");
        return;
    }

    node_user *i;
    for (i = lista->begin; i != NULL; i = i->next)
    {

        if (i->name == nome)
        {

            return 1;
        }
    }
    return 0;
}

void print_id(Lista *lista, int id)
{

    if (lista == NULL)
    {

        printf("\nLista não criada!\n");
        return;
    }
    // não há users
    if (lista->begin == NULL)
    {
        printf("\nNão há users\n");
        return;
    }

    node_user *i;

    for (i = lista->begin; i != NULL; i = i->next)
    {
        printf("\nID: %d\n", i->id);
        if (i->id == id)
        {

            printf("\nID: %d\n", i->id);
            printf("Nome: %s", i->name);
            printf("Endereço:\n");
            printf("\tRua: %s", i->adress.street);
            printf("\tBairro: %s", i->adress.district);
            printf("\tNúmero: %s", i->adress.number);
            printf("\tCEP: %s", i->adress.CEP);
            printf("Tipo: %c\n", i->type);
            printf("Usuário: %s", i->user);

            printf("Senha: %s", i->password);
            printf("Salvo: %d\n", i->onSave);

            printf("\n");
        }
    }

    printf("\nUser não encontrado!\n");
    return;
}

print_list(Lista *lista)
{

    node_user *i;
    for (i = lista->begin; i != NULL; i = i->next)
    {
        printf("\nID: %d\n", i->id);
        printf("Nome: %s", i->name);
        printf("Endereço:\n");
        printf("\tRua: %s", i->adress.street);
        printf("\tBairro: %s", i->adress.district);
        printf("\tNúmero: %s", i->adress.number);
        printf("\tCEP: %s", i->adress.CEP);
        printf("Tipo: %c\n", i->type);
        printf("Usuário: %s", i->user);

        printf("Senha: %s", i->password);
        printf("Salvo: %d\n", i->onSave);

        printf("\n");
    }
    return;
}

void recordUser(node_user *user, FILE *fp)
{

    fp = fopen(".//data//database.bin", "r+b");
    if (fp == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    int i;
    while (1)
    {

        node_user *node = (node_user *)malloc(sizeof(node_user));
        i = ftell(fp);

        fread(node, sizeof(node_user), 1, fp);

        if (node->onSave == -1)
        {
            fseek(fp, i, SEEK_SET);
            user->onSave = 1;
            fwrite(user, sizeof(node_user), 1, fp);
            break;
        }

        if (feof(fp))
        {
            user->onSave = 1;
            fwrite(user, sizeof(node_user), 1, fp);
            break;
        }
    }

    fclose(fp);
}

updateUser(node_user *user, FILE *fp){

    fp = fopen(".//data//database.bin", "r+b");
    if (fp == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    int i;
    while (1)
    {

        node_user *node = (node_user *)malloc(sizeof(node_user));
        i = ftell(fp);

        fread(node, sizeof(node_user), 1, fp);

        if (node->id == user->id)
        {
            fseek(fp, i, SEEK_SET);
            user->onSave = 1;
            fwrite(user, sizeof(node_user), 1, fp);
            break;
        }

        if (feof(fp))
        {
            user->onSave = 1;
            fwrite(user, sizeof(node_user), 1, fp);
            break;
        }
    }

}

void print_name(Lista *lista, char nome[])
{

    if (lista == NULL)
    {

        printf("\nLista não criada!\n");
        return;
    }
    // não há users
    if (lista->begin == NULL)
    {
        printf("\nNão há users\n");
        return;
    }

    node_user *i;

    for (i = lista->begin; i != NULL; i = i->next)
    {

        if (strcmp(nome, i->name) == 0)
        {

            printf("\nID: %d\n", i->id);
            printf("Nome: %s", i->name);
            printf("Endereço:\n");
            printf("\tRua: %s", i->adress.street);
            printf("\tBairro: %s", i->adress.district);
            printf("\tNúmero: %s", i->adress.number);
            printf("\tCEP: %s", i->adress.CEP);
            printf("Tipo: %c\n", i->type);
            printf("Usuário: %s", i->user);

            printf("Senha: %s", i->password);
            printf("Salvo: %d\n", i->onSave);

            printf("\n");
            return;
        }
    }

    printf("\nUser não encontrado!\n");
    return;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------Main---------------------------------------------------------------------------*/

int main()
{
    Lista *lista = onCreate(); // criando lista
    FILE *fp = fopen(".//data//database.bin", "rb");
    if (fp != NULL)
    {
        printf("Carregando database.bin...\n");
        reloadList(lista, fp);
        printf("Carregada!\n");
    }
    else
    {
        printf("Criando database.bin...\n");

        printf("Cadastre o Superusuário:\n\n");
        node_user *node = (node_user *)malloc(sizeof(node_user));

        // lendo id(definido automaticamente)
        node->id = id_disponivel(lista);
        printf("ID: %d\n", node->id);

        // lendo nome
        setbuf(stdin, NULL);
        printf("Insira seu nome: ");
        fgets(node->name, 64, stdin);

        // lendo endereço
        setbuf(stdin, NULL);
        printf("Insira seu endereço:\n");
        printf("\tRua: ");
        fgets(node->adress.street, 64, stdin);
        setbuf(stdin, NULL);
        printf("\tBairro: ");
        fgets(node->adress.district, 64, stdin);
        setbuf(stdin, NULL);
        printf("\tNúmero: ");
        fgets(node->adress.number, 16, stdin);
        setbuf(stdin, NULL);
        printf("\tCEP: ");
        fgets(node->adress.CEP, 32, stdin);
        setbuf(stdin, NULL);

        // lendo tipo (definido automaticamente)
        printf("Tipo: S - Superusuário\n");
        node->type = 'S';

        // lendo user
        setbuf(stdin, NULL);
        printf("Usuário: ");
        fgets(node->user, 64, stdin);

        // lendo senha
        setbuf(stdin, NULL);
        printf("Senha: ");
        fgets(node->password, 257, stdin);
        /* fazer */

        // salvar no arquivo

        insert_user(lista, node);

        lista->begin->onSave = 1;

        fp = fopen(".//data//database.bin", "wb");

        recordUser(node, fp);
        printf("\n");
        system("pause");
        system("cls");
    }
    fclose(fp);

    int startOption, C_option, S_Adm_option, id;
    char usuario[64], senha[64], name[64], type;

    do
    {

        printf("Escolha uma opção:\n\n");
        printf("1. Login;\n");
        printf("2. Sair;\n");
        scanf("%d", &startOption);
        printf("\n");
        system("pause");
        system("cls");

        switch (startOption)
        {
        case 1:

            setbuf(stdin, NULL);
            printf("Usuário: ");
            fgets(usuario, 64, stdin);

            setbuf(stdin, NULL);
            printf("Senha: ");
            fgets(senha, 64, stdin);
            // fazer hash
            setbuf(stdin, NULL);

            // i como se fosse o "user atual"
            for (node_user *i = lista->begin; i != NULL; i = i->next)
            {

                if (strcmp(i->password, senha) == 0 && strcmp(i->user, usuario) == 0)
                {

                    system("pause");
                    system("cls");
                    printf("Bem vindo %s(Tipo: %c) Escolha uma opção:\n\n", i->name, i->type);

                    switch (i->type)
                    {
                    case 'C':

                        do
                        {
                            printf("1. Alterar senha;\n");
                            printf("2. Sair;\n");
                            scanf("%d", &C_option);
                            fgets(senha, 64, stdin);

                            printf("\n");
                            system("pause");
                            system("cls");

                            switch (C_option)
                            {
                            case 1:

                                printf("Insira sua nova senha: ");
                                setbuf(stdin, NULL);
                                fgets(senha, 64, stdin);
                                setbuf(stdin, NULL);

                                strcpy(i->password, senha);
                                /* *i->password = senha; */
                                if(i->onSave == 1){
                                    updateUser(i, fp);
                                }
                                printf("\nSenha modificada com sucesso\n ");

                                printf("\n");
                                system("pause");
                                system("cls");
                                break;

                            case 2:

                                printf("\nSalvando modificações\n\n");
                                exit(1);
                                break;

                                /*debug*/
                            case 21:

                                print_list(lista);
                                break;

                            default:

                                printf("\nInsira uma opção válida!\n");

                                break;
                            }

                        } while (C_option != 2);

                    default:

                        do
                        {

                            printf("1. Cadastrar Usuárioa;\n");
                            printf("2. Remover Usuário;\n");
                            printf("3. Pesquisar Usuário por nome;\n");
                            printf("4. Alterar senha;\n");
                            printf("5. Sair;\n");
                            scanf("%d", &S_Adm_option);

                            printf("\n");
                            system("pause");
                            system("cls");

                            switch (S_Adm_option)
                            {
                            case 1:

                                printf("1. Cadastrar Usuárioa;\n\n");
                                node_user *user = (node_user *)malloc(sizeof(node_user));

                                // lendo id(definido automaticamente)
                                user->id = id_disponivel(lista);
                                printf("ID: %d\n", user->id);

                                // lendo nome
                                setbuf(stdin, NULL);
                                printf("Insira seu nome: ");
                                fgets(user->name, 64, stdin);
                                while (Check_Mat(lista, user->name) == 1)
                                {
                                    printf("Usuário já cadastrada!\nInsira outro noem de usuário:");
                                    fgets(user->name, 64, stdin);
                                }

                                // lendo endereço
                                setbuf(stdin, NULL);
                                printf("Insira seu endereço:\n");
                                printf("\tRua: ");
                                fgets(user->adress.street, 64, stdin);
                                setbuf(stdin, NULL);
                                printf("\tBairro: ");
                                fgets(user->adress.district, 64, stdin);
                                setbuf(stdin, NULL);
                                printf("\tNúmero: ");
                                fgets(user->adress.number, 16, stdin);
                                setbuf(stdin, NULL);
                                printf("\tCEP: ");
                                fgets(user->adress.CEP, 32, stdin);
                                setbuf(stdin, NULL);

                                // lendo tipo (definido automaticamente)
                                printf("Tipo: ");
                                scanf("%c", &type);
                                setbuf(stdin, NULL);
                                while (type != 'A' && type != 'C')
                                {
                                    if (type == 'S')
                                    {
                                        printf("Já existe um superusuário no sistema.\nInsira uma tipo válida: ");
                                    }
                                    else
                                    {
                                        printf("Tipo inválida, são aceitos os caracteres 'S' ou 'C' ou 'A'\nInsira uma tipo válida: ");
                                    }
                                    scanf("%c", &type);
                                    setbuf(stdin, NULL);
                                }

                                // lendo user
                                setbuf(stdin, NULL);
                                printf("Usuário: ");
                                fgets(user->user, 64, stdin);

                                // lendo senha
                                setbuf(stdin, NULL);
                                printf("Senha: ");
                                fgets(user->password, 257, stdin);
                                /* fazer */

                                insert_user(lista, user);

                                /* printf("\n%s", i->user);
                                printf("%s", lista->begin->user);*/

                                char g;
                                printf("Deseja salvar o user?\n");
                                scanf("%c", &g);
                                setbuf(stdin, NULL);
                                while (g != 'S' && g != 's' && g != 'N' && g != 'n')
                                {
                                    printf("Opção inválida são aceitos apenas os caracteres 'S'/'s' ou 'N'/'n'\nInsira uma Opção válida: ");
                                    scanf("%c", &g);
                                    setbuf(stdin, NULL);
                                }

                                if (g == 'S' || g == 's')
                                {
                                    recordUser(lista->begin, fp);
                                }
                                else
                                {
                                    /* printf("%s", lista->begin->name); */
                                    lista->begin->onSave = 0;
                                }

                                system("pause");
                                system("cls");

                                break;

                            case 2:

                                printf("2 . Remover user:\n\n");

                                printf("Digite o número de ID do user que será removido: ");
                                scanf("%d", &id);
                                if (id == i->id)
                                {
                                    printf("\nNão é possível remover o usuário que esta logado agora! (literalmente você)\n");
                                    system("pause");
                                    system("cls");
                                    break;
                                }

                                for (node_user *j = lista->begin; j != NULL; j = j->next)
                                {

                                    if (j->id == id)
                                    {
                                        if (j->type == 'S')
                                        {
                                            printf("\nNão é possível remover o superusuário\n ");
                                            system("pause");
                                            system("cls");
                                            break;
                                        }

                                        if (i->type == 'A' && j->type != 'C')
                                        {
                                            printf("\nComo Administrador só é possivel remover Clientes!\n ");
                                            system("pause");
                                            system("cls");
                                            break;
                                        }
                                    }
                                }

                                // apos ler a mat removemos ela
                                remove_user(lista, id, fp);

                                system("pause");
                                system("cls");

                                break;

                            case 3:

                                printf("3 . Pesquisar user pelo nome:\n\n");

                                printf("Digite o nome do user que será pesquisado: ");
                                setbuf(stdin, NULL);
                                fgets(name, 64, stdin);
                                setbuf(stdin, NULL);
                                // apos ler o nome printamos ele
                                print_name(lista, name);

                                system("pause");
                                system("cls");

                                break;

                            case 4:

                                printf("4. Alterar senha:\n\n");

                                printf("Insira sua nova senha: ");
                                setbuf(stdin, NULL);
                                fgets(senha, 64, stdin);
                                setbuf(stdin, NULL);

                                strcpy(i->password, senha);
                                updateUser(i, fp);
                                printf("\nSenha modificada com sucesso\n ");

                                printf("\n");
                                system("pause");
                                system("cls");

                                break;

                            case 5:

                                printf("\nVocê saiu do programa...\n");
                                exit(1);

                                break;

                            /*debug*/
                            case 21:

                                print_list(lista);
                                break;

                            default:

                                printf("\nInsira uma opção válida!\n");
                                break;
                            }
                        } while (S_Adm_option != 5);

                        break;
                    }
                }
            }

            printf("\nUsuário ou Senha incorreta...");
            printf("\n");
            system("pause");
            system("cls");

            break;

        case 2:

            printf("\nVocê saiu do programa...\n");
            onDestroy(lista); // liberamos a lista
            break;

        /*debug*/
        case 21:

            print_list(lista);
            break;

        default:

            printf("\nInsira uma opção válida.\n\n");
            break;
        }

    } while (startOption != 2);

    return 0;
}
