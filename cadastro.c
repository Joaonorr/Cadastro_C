#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

//-------------------------------------------
// Criando as structs para os clientes e para os pacotes
typedef struct Ficha_de_usuario
{
    char nome_pessoa[50];
    char endereco[100];
    int cpf; 
    int idade;
}Ficha_de_usuario;
Ficha_de_usuario usuario;

typedef struct Ficha_de_pacote
{
    char nome_pacote[50];
    float preco;
    char info[100];
    int cod;
    int quantidade;
}Ficha_de_pacote;

Ficha_de_pacote pacote;


//-------------------------------------------
// Função para cadastrar clientes
void cadastro_cliente()
{
    system("CLS");

    FILE *cliente;
    cliente = fopen ("cadastro.txt","ab");


    if(cliente == NULL)
    {
        printf("ERRO DA ABERTURA DE ARQUIVO!");
        system("pause");
        exit(1);
    }
    else {
    printf ("Informe o nome do cliente: ");
    scanf(" %[^\n]",usuario.nome_pessoa);
    flush_in();
    printf ("\nInforme seu endereço: ");
    scanf(" %[^\n]",usuario.endereco);
    flush_in();
    printf("\nInforme seu CPF(caso comece com 0, digite o número 1 antes de inserir o CPF): ");
    scanf ( "%d",&usuario.cpf);
    printf ("\nInforme sua idade: ");
    scanf ( "%d",&usuario.idade);
    printf("\nCadastro realizado com sucesso!\n\n");

    fwrite(&usuario, sizeof(Ficha_de_usuario), 1, cliente);
    fclose(cliente);
    }
    
}


//-------------------------------------------
// Função para ver os clientes cadastrados
void visualizar_cliente()
{
    system("CLS");

    FILE *cliente;
    cliente = fopen("cadastro.txt","rb");

    int num=1;

    while(fread(&usuario, sizeof(Ficha_de_usuario),1,cliente)==1)
    {
        printf("-----------------%d-------------------\n",num);
        printf ( "Nome: %s\n",usuario.nome_pessoa);    
        printf ( "Endereço: %s\n",usuario.endereco);   
        printf ( "CPF: %d\n",usuario.cpf);  
        printf ( "Idade: %d\n",usuario.idade);
        printf("--------------------------------------\n",num);

        num++;
    }

    fclose(cliente);
    system("pause");
}


//-------------------------------------------
// Função para ler espaços
void flush_in(){ 
int ch;
while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}


//-------------------------------------------
// Função para cadastrar pacotes
void cadastro_pacote()
{
    system("CLS");

    FILE *pacotes;
    pacotes = fopen ("pacotes.txt","ab");
    if(pacotes == NULL)
    {
        printf("ERRO DA ABERTURA DE ARQUIVO!");
        system("pause");
        exit(1);
    }
    else {
    printf("Nome do pacote: ");
    scanf(" %[^\n]",pacote.nome_pacote);
    flush_in();
    printf("\nPreço do pacote: ");
    scanf("%f",&pacote.preco);
    printf("\nDigite as informações adicionais sobre o pacote: ");
    scanf(" %[^\n]",pacote.info);
    flush_in();
    printf("\nNúmeros de vagas do pacote: ");
    scanf("%d",&pacote.quantidade);
    printf("\nDigite o código do pacote: ");
    scanf("%d",&pacote.cod);

    fwrite(&pacote, sizeof(Ficha_de_pacote), 1, pacotes);
    fclose(pacotes);
    }
}


//-------------------------------------------
// Função para ver os pacotes existentes
void visualizar_pacote(){
    system("CLS");
    FILE *pacotes;
    pacotes = fopen("pacotes.txt","rb");

    while(fread(&pacote, sizeof(Ficha_de_pacote),1,pacotes)==1)
    {
    printf("\n---------------------------------------\n");       
    printf("Nome do pacote: %s\n",pacote.nome_pacote);
    printf("Preço do pacote: R$ %.2f\n",pacote.preco);
    printf("Informações do pacote: %s\n",pacote.info);
    printf("Codigo do pacote: %d\n",pacote.cod);
    printf("---------------------------------------\n");       

    }

    fclose(pacotes);
    system("pause");
}


//-------------------------------------------
// Função para remover cadastro de clientes
void remover_cliente(){
    system("CLS");

    int excluir;
    printf("Qual é o CPF do usuario que voce deseja excluir?\n");
    scanf("%d",&excluir);

    FILE *arquivo_auxiliar, *cliente;
    arquivo_auxiliar = fopen("aux_arq.txt","w");
    cliente = fopen ("cadastro.txt","r");

    while(fread(&usuario, sizeof(Ficha_de_usuario),1,cliente)==1)
    {
       if(excluir != usuario.cpf)
       fwrite(&usuario, sizeof(Ficha_de_usuario),1,arquivo_auxiliar);
       
    }

    fclose(arquivo_auxiliar);
    fclose(cliente);
    remove("cadastro.txt");
    rename("aux_arq.txt","cadastro.txt");

}


//-------------------------------------------
//Função para remover pacotes cadastrados
void remover_pacote(){
    system("CLS");

    int excluir;
    printf("Digite o código do pacote que você deseja excluir?");
    scanf("%d",&excluir);

    FILE *pacote_auxiliar, *pacotes;
    pacote_auxiliar = fopen("aux_arq.txt","w");
    pacotes = fopen ("pacotes.txt","r");

    while(fread(&pacote, sizeof(Ficha_de_pacote),1,pacotes)==1)
    {
       if(excluir != pacote.cod)
       fwrite(&pacote, sizeof(Ficha_de_pacote),1,pacote_auxiliar);
       
    }

    fclose(pacote_auxiliar);
    fclose(pacotes);
    remove("pacotes.txt");
    rename("aux_arq.txt","pacotes.txt");
}


//-------------------------------------------
// Função para comprar pacotes
void comprar_pacote(){
    int comprar;
    printf("Qual o código do pacote que você deseja comprar?");
    scanf("%d",&comprar);

    FILE *arquivo_auxiliar, *cliente;
    arquivo_auxiliar = fopen("aux_arq.txt","w");
    cliente = fopen ("cadastro.txt","r");

    while(fread(&usuario, sizeof(Ficha_de_usuario),1,cliente)==1)
    {
       if(comprar != usuario.cpf)
       fwrite(&usuario, sizeof(Ficha_de_usuario),1,arquivo_auxiliar);
       
    }

    fclose(arquivo_auxiliar);
    fclose(cliente);
    remove("cadastro.txt");
    rename("aux_arq.txt","cadastro.txt");
}


//-------------------------------------------
int main(){
    setlocale(LC_ALL, "Portuguese_Brasil");
    system("chcp 65001");

    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    int i=0,acao;

    printf("***************\n");
    printf("*                                           *\n");
    printf("*     Seja bem-vindo(a) a Nerrer_AirLines   *\n");
    printf("*                                           *\n");
    printf("***************\n");
    //printf("\nPressione qualquer tecla para continuar\n");
    system("pause");
    
    while(i == 0)
    {
        system("CLS");
        printf("\n-------------------------MENU-------------------------\n\n");
    
        printf("Aperte (1) para cadastrar cliente.\n");
        printf("Aperte (2) para visualizar clientes.\n");
        printf("Aperte (3) parar comprar pacote.\n");
        printf("Aperte (4) para cadastrar pacotes.\n");
        printf("Aperte (5) para visualizar pacotes.\n");
        printf("Aperte (6) para remover usuario.\n");
        printf("Aperte (7) para remover pacote.\n");
        printf("Aperte (8) para sair.\n");
        printf("------------------------------------------------------\n\n");

        scanf("%d",&acao);
        switch (acao)
        {
            case 1 : cadastro_cliente();
            break;

            case 2 : visualizar_cliente();
            break;

            case 3 : comprar_pacote();
            break;

            case 4 : cadastro_pacote();
            break;

            case 5 : visualizar_pacote();
            break;

            case 6 : remover_cliente();
            break;

            case 7 : remover_pacote();
            break;

            case 8 : i = 1;
            break;
        }
    }

    SetConsoleOutputCP(CPAGE_DEFAULT);
    return 0;
}