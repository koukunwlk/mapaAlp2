#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#define max 100

//Definindo os atributos de cada obra
typedef struct obra
{
    char title[50];
    int edition;
    char authorName[50];
    char publisher[50];
    int isbn;
    int qnt;
    int box;
    int year;
    int type;

} newObra;

void newItem(newObra ficha[max]);
int count(newObra ficha[max]);
void listBooks(newObra ficha[max]);
void boxItens(int boxId, newObra ficha[max]);
void header();

int main()
{
    newObra ficha[max];
    setlocale(LC_ALL, "Portuguese");
    system("chcp 65001"); //Define o CMD para utf-8

        int choose,
        category, boxId;
    do
    {
        header();
        printf("\n [1] para cadastrar uma nova obra\n");
        printf(" [2] para listar todos os livros\n");
        printf(" [3] para listar todas as revistas\n");
        printf(" [4] para listar itens por caixa\n");
        printf(" [0] para sair do sistema\n");
        printf(" O que deseja fazer dessa vez: ");
        scanf("%d", &choose);

        switch (choose)
        {
        case 1:
            newItem(ficha);
            break;

        case 2:
            category = 2;
            listByCategory(category, ficha);
            system("pause");
            break;

        case 3:
            category = 1;
            listByCategory(category, ficha);
            system("pause");
            break;

        case 4:
            printf("Pesquisando produtos por caixa\nEscolha a caixa: [1 Caixa] | [2 Caixa] | [3 Caixa]");
            printf("\n Digite o numero da caixa: ");
            fflush(stdin);
            scanf("%d", &boxId);

            boxItens(boxId, ficha);
            system("pause");
            break;

        case 0:
            printf("Você saiu do sistema ate logo!\n");
            system("pause");
            break;

        default:
            printf("Valor incorreto!");
            system("pause");
            break;
        }
    } while (choose != 0);
    return 0;
}

//Chamada da identificação do aluno
void header()
{
    system("cls");
    int i;
    printf("\n*****Engenharia de Software*****");
    printf("\n*****Moacir Amaro da Silva Junior*****");
    printf("\n*****RA: 20087479-5*****\n");
    for (i = 0; i < 50; i++)
        printf("=");
}

void newItem(newObra ficha[max]) // Essa função vai adicionar um novo item no arquivo txt
{
    FILE *file;
    int i;
    file = fopen("obras.txt", "a+");
    header();

    if (file != NULL)
    {
        for (i = 0; i < 2; i++)
        {
            printf("\nDigite o titulo da obra: ");
            fflush(stdin);
            gets(ficha[i].title);
            printf("\nDigite o nome do autor da obra: ");
            fflush(stdin);
            gets(ficha[i].authorName);
            printf("\nDigite a editora da obra: ");
            fflush(stdin);
            gets(ficha[i].publisher);
            printf("\nDigite a edição da obra: ");
            fflush(stdin);
            scanf("%d", &ficha[i].edition);
            printf("\nDigite o ISBN da obra: ");
            fflush(stdin);
            scanf("%d", &ficha[i].isbn);
            printf("\nDigite a quantidade da obra: ");
            fflush(stdin);
            scanf("%d", &ficha[i].qnt);
            printf("\nEm qual caixa a obra esta\n [1 Caixa] | [2 Caixa] | [3 Caixa]: ");
            fflush(stdin);
            scanf("%d", &ficha[i].box);
            printf("\nDigite o ano da obra: ");
            fflush(stdin);
            scanf("%d", &ficha[i].year);
            printf("Categoria: \n[1] Revista | [2] Livro: ");
            fflush(stdin);
            scanf("%d", &ficha[i].type);
            fwrite(&ficha[i], sizeof(newObra), 1, file);
            system("cls");
            fclose(file);
        }
    }
}

int count(newObra ficha[max]) //Essa função vai contar o numero de registros no arquivo txt
{
    FILE *file = fopen("obras.txt", "r");

    if (file != NULL)
    {
        int counter = 0;
        while (1)
        {
            newObra f;

            int registry = fread(&f, sizeof(newObra), 1, file);

            if (registry < 1)
                break;
            else
                ficha[counter] = f;
            counter++;
        }
        fclose(file);
        return counter;
    }
    else
    {
        printf("\nErro ao abrir o arquivo para leitura!\n");
        exit(1); // aborta o programa
    }
}

void listByCategory(int category, newObra ficha[max]) // Essa função vai listar os registros pela categoria, livro ou revista recebendo a categoria na chamada da função
{
    header();
    int qnt = count(ficha);
    int i;
    printf("\n****Lista de obras por categoria*****\n");
    if (category == 1)
    {
        printf("Categoria: Revistas\n");
    }
    else
    {
        printf("Categoria: Livros\n");
    }
    printf("TITULO \t| AUTOR \t| EDIÇÃO \t| EDITORA \t| ISBN \t| QUANTIDADE \t| ANO\n");
    for (i = 0; i < qnt; i++)
    {
        if (ficha[i].type == category)
        {
            printf("\n %s \t| %s \t| %d \t| %s \t| %d \t| %d \t| %d \n", ficha[i].title, ficha[i].authorName, ficha[i].edition, ficha[i].publisher, ficha[i].isbn, ficha[i].qnt, ficha[i].year);
        };
    };
}

void boxItens(int boxId, newObra ficha[max]) // Essa função vai listar os registros por caixa, recebendo o numero da caixa na chamada da função
{
    header();
    int qnt = count(ficha);
    int i;
    printf("\n[%d Caixa] Items:\n", boxId);
    printf("TITULO \t| AUTOR \t| EDIÇÃO \t| EDITORA \t| ISBN \t| QUANTIDADE \t| ANO\n");
    for (i = 0; i < qnt; i++)
    {
        if (ficha[i].box == boxId)
        {
            printf("\n %s \t| %s \t| %d \t| %s \t| %d \t| %d \t| %d \n", ficha[i].title, ficha[i].authorName, ficha[i].edition, ficha[i].publisher, ficha[i].isbn, ficha[i].qnt, ficha[i].year);
        }
    }
}
