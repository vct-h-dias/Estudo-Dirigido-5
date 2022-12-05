#include "Program2Functions.c"

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

        strcpy(node->password, SHA256(node -> password));
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
    char usuario[64], senha[257], name[64], type;

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
            fgets(senha, 257, stdin);

            strcpy(senha, SHA256(senha));
            
            /* printf("\n%s\n", senha); */
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

                                strcpy(senha, SHA256(senha));
                                strcpy(i->password, senha);
                                
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
                                onDestroy(lista);
                                exit(1);
                                break;

                            /*debug*/
                            /* case 21:

                                print_list(lista);
                                break; */

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
                                scanf("%c", &user->type);
                                setbuf(stdin, NULL);
                                while (user->type != 'A' && user->type != 'C')
                                {
                                    if (user->type == 'S')
                                    {
                                        printf("Já existe um superusuário no sistema.\nInsira uma tipo válida: ");
                                    }
                                    else
                                    {
                                        printf("Tipo inválida, são aceitos os caracteres 'S' ou 'C' ou 'A'\nInsira uma tipo válida: ");
                                    }
                                    scanf("%c", &user->type);
                                    setbuf(stdin, NULL);
                                }

                                while(i -> type == 'A' && user -> type != 'C'){
                                    printf("Como Administrador só é possivel cadastrar Clientes!\nInsira um tipo válido: ");
                                    scanf("%c", &user->type);
                                    setbuf(stdin, NULL);
                                }
                                // lendo user
                                setbuf(stdin, NULL);
                                printf("Usuário: ");
                                fgets(user->user, 64, stdin);
                                while (Check_Name(lista, user->user) == 1)
                                {
                                    printf("Usuário já cadastrada!\nInsira outro noem de usuário:");
                                    fgets(user->user, 64, stdin);
                                }

                                // lendo senha
                                setbuf(stdin, NULL);
                                printf("Senha: ");
                                fgets(user->password, 257, stdin);
                                strcpy(user->password, SHA256(user->password));

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

                                int verif = 1;
                                for (node_user *j = lista->begin; j != NULL; j = j->next)
                                {

                                    if (j->id == id)
                                    {
                                        if (j->type == 'S')
                                        {
                                            printf("\nNão é possível remover o superusuário\n");
                                            verif = 0;
                                            system("pause");
                                            system("cls");
                                            break;
                                        }

                                        if (i->type == 'A' && j->type != 'C')
                                        {
                                            verif = 0;
                                            printf("\nComo Administrador só é possivel remover Clientes!\n");
                                            system("pause");
                                            system("cls");
                                            break;
                                        }
                                    }
                                }
                                if(verif != 1) break;
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

                                strcpy(senha, SHA256(senha));
                                strcpy(i->password, senha);
                                if(i->onSave == 1){
                                    updateUser(i, fp);
                                }
                                printf("\nSenha modificada com sucesso\n ");

                                printf("\n");
                                system("pause");
                                system("cls");

                                break;

                            case 5:

                                printf("Você saiu do programa...\n");
                                onDestroy(lista); 
                                exit(1);

                                break;

                            /*debug*/
                            /* case 21:

                                print_list(lista);
                                break;  */

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
        /* case 21:

            print_list(lista);
            break;  */

        default:

            printf("\nInsira uma opção válida.\n\n");
            break;
        }

    } while (startOption != 2);

    return 0;
}
