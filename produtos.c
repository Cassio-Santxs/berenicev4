#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "headers.h"

void menuDeProdutos( cadastro_produtos **ptrProdutos,
                     int *tamanhoVetorProdts, int * contadorProdutos)
{

    int flag = 1, codigo;
    int i = 0;
    char voltar = 'q';

    cadastro_produtos *auxHead = (cadastro_produtos*) calloc(1,sizeof(cadastro_produtos));

    while(flag == 1)
    {
        while(codigo != 7)
        {
            auxHead = *ptrProdutos;

            system("cls");

            printf("\n\n=====\t\t||\t\t MENU DE PRODUTOS \t\t||\t\t=====\n\n");
            printf("\n \t Código  \t Opção              \t\n");
            printf("\n \t 1       \t Exibir             \t");
            printf("\n \t 2       \t Cadastrar          \t");
            printf("\n \t 3       \t Atualizar          \t");
            printf("\n \t 4       \t Excluir            \t");
            printf("\n \t 5       \t Salvar             \t");
            printf("\n \t 6       \t Ler                \t");
            printf("\n \t 7       \t Voltar             \t\n");

            printf("\nDigite o código para selecionar a opção: ");
            scanf("%d", &codigo);
            getchar();

            switch(codigo)
            {

            //EXIBIR PRODUTOS
            case 1:
                flag = 0;

                system("cls");

                if(*contadorProdutos > 0)
                {
                    char voltar;

                    printf("%ld", (*ptrProdutos)->id);

                    printf("\n\n=====\t\t||\t\t PRODUTOS \t\t||\t\t=====\n\n");
                    printf("\n\t ID      \t Produto \t Preço        \t Estoque \t\n");

                    while(*ptrProdutos != NULL)
                    {

                        if((*ptrProdutos)->id > 0)
                        {
                            printf("\n\t %ld   \t\t   %s     \t R$ %.2f      \t %i      \t",
                                   (*ptrProdutos)->id,
                                   (*ptrProdutos)->nome,
                                   (*ptrProdutos)->preco,
                                   (*ptrProdutos)->estoque);
                        }

                        *ptrProdutos = (*ptrProdutos)->next;
                    }
                }
                else
                {
                    printf("\n\aAVISO: Você não possui produtos cadastrados.\n");
                }

                *ptrProdutos = auxHead;

                break;

            //     CADASTRO DE PRODUTOS
            case 2:
                flag = 0;

                int ptr = -1,
                    estoque = -1;

                float preco = -1;

                long int id = -1, retorno = 0;

                system("cls");

                printf("\n\n=====\t\t||\t\t CADASTRO DE PRODUTOS \t\t||\t\t=====\n\n");

                cadastro_produtos *novoProduto = (cadastro_produtos*) calloc(1, sizeof(cadastro_produtos));

                novoProduto->next = *ptrProdutos;
                novoProduto->prev = NULL;

                if(*ptrProdutos != NULL)
                {
                    (*ptrProdutos)->prev = novoProduto;
                }

                while (retorno == 0)
                {
                    printf("\nDigite o ID do produto sendo este maior que 0: ");
                    scanf("%li", &id);
                    getchar();

                    if(id < 1)
                    {
                        retorno = 0;
                        printf("\nCódigo inválido");
                    }
                    else
                    {

                        retorno = 1;
                        novoProduto->id = id;
                    }

                    while(*ptrProdutos != NULL)
                    {
                        if((*ptrProdutos)->id == id)
                        {
                            break;
                        }

                        *ptrProdutos = (*ptrProdutos)->next;
                    }

                    if(*ptrProdutos != NULL)
                    {
                        retorno = 0;
                        printf("\nCódigo já cadastrado");
                    }
                    else
                    {
                        retorno = 1;
                    }
                }

                printf("\nDigite o nome do produto de ID %li com até 25 caracteres: ", id);
                fgets(novoProduto->nome,25,stdin);

                char lenp1 = strlen(novoProduto->nome);

                if(novoProduto->nome[lenp1 -1]=='\n')
                {
                    novoProduto->nome [--lenp1] = 0;
                }
                else
                {
                    int ch;
                    do ch = getchar();
                    while (ch != '\n'); // limpa caracteres extra
                }

                do
                {
                    printf("\nDigite o estoque do produto de ID %li sendo este valor maior ou igual a 0: ", id);
                    scanf("%i", &estoque);
                    getchar();

                    if(estoque < 0)
                    {
                        printf("Quantidade inválida!");
                    }

                }
                while(estoque < 0);

                novoProduto->estoque = estoque;

                do
                {
                    printf("\nDigite o preço do produto de ID %li sendo este valor maior ou igual a 0: ", id);
                    scanf("%f", &preco);
                    getchar();

                    if(preco < 0)
                    {
                        printf("Quantidade inválida!");
                    }
                }
                while(preco < 0);

                novoProduto->preco = preco;

                *ptrProdutos = novoProduto;

                *tamanhoVetorProdts = *tamanhoVetorProdts + 1;
                *contadorProdutos = *contadorProdutos + 1;

                break;

            case 3:
                flag = 0;

                long int idDigitado = 0;

                int estoqueAntigo;

                float precoAntigo;

                cadastro_produtos *auxAtualizaProduto = (cadastro_produtos*) calloc(1,sizeof(cadastro_produtos));

                auxAtualizaProduto = *ptrProdutos;

                system("cls");

                // EXIBIR PRODUTOS
                if(*contadorProdutos > 0)
                {
                    printf("\n\n=====\t\t||\t\t PRODUTOS \t\t||\t\t=====\n\n");
                    printf("\n\t ID      \t Produto \t Preço        \t Estoque \t\n");

                    while(auxAtualizaProduto != NULL)
                    {

                        if(auxAtualizaProduto->id > 0)
                        {
                            printf("\n\t %ld   \t\t   %s     \t R$ %.2f      \t %i      \t",
                                   auxAtualizaProduto->id,
                                   auxAtualizaProduto->nome,
                                   auxAtualizaProduto->preco,
                                   auxAtualizaProduto->estoque);
                        }

                        auxAtualizaProduto = auxAtualizaProduto->next;
                    }

                    auxAtualizaProduto = auxHead;
                    //

                    // ATUALIZAR PRODUTOS
                    printf("\n\n=====\t\t||\t\t ATUALIZAÇÃO DE PRODUTOS \t\t||\t\t=====\n\n");

                    retorno = 0;
                    while (retorno == 0)
                    {
                        printf("\nDigite o ID do produto que você que alterar: ");
                        scanf("%li", &idDigitado);
                        getchar();


                        while(*ptrProdutos != NULL)
                        {
                            if((*ptrProdutos)->id == idDigitado)
                            {
                                break;
                            }
                            *ptrProdutos = (*ptrProdutos)->next;
                        }

                        if(*ptrProdutos != NULL)
                        {
                            retorno = 1;
                            estoqueAntigo = (*ptrProdutos)->estoque;
                            precoAntigo = (*ptrProdutos)->preco;
                        }
                        else
                        {
                            printf("\nProduto não encontrado");
                            retorno = 0;
                            *ptrProdutos = auxHead;
                        }

                    }

                    do
                    {
                        printf("\nDigite o novo estoque do produto de ID %li sendo este valor maior ou igual a 0: ", (*ptrProdutos)->id);
                        scanf("%i",  &estoque);
                        getchar();

                        if(estoque < 0)
                        {
                            printf("Quantidade inválida!");
                        }
                    }
                    while(estoque < 0);

                    do
                    {
                        printf("\nDigite o novo preço do produto de ID %li sendo este valor maior ou igual a 0: ", (*ptrProdutos)->id);
                        scanf("%f", &preco);
                        getchar();

                        if(preco < 0)
                        {
                            printf("Quantidade inválida!");
                        }
                    }
                    while(preco < 0);

                    (*ptrProdutos)->preco = preco;
                    (*ptrProdutos)->estoque = estoque;


                    system("cls");

                    printf("\n\n=====\t\t||\t\t         ANTIGO          \t\t||\t\t=====\n\n");

                    printf("\n\t ID     \t Produto \t Preço     \t Quantidade \t\n");
                    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", (*ptrProdutos)->id, (*ptrProdutos)->nome, precoAntigo, estoqueAntigo);

                    printf("\n\n=====\t\t||\t\t          NOVO           \t\t||\t\t=====\n\n");
                    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", (*ptrProdutos)->id, (*ptrProdutos)->nome, (*ptrProdutos)->preco, (*ptrProdutos)->estoque);

                }
                else
                {
                    printf("\n\aAVISO: Você não possui produtos cadastrados.\n");
                }

                *ptrProdutos = auxHead;

                break;

            case 4:
                flag = 0;

                system("cls");

                if(*contadorProdutos > 0)
                {
                    exibirProdutos(*ptrProdutos);

                    if(excluirProduto(*ptrProdutos,
                                      *tamanhoVetorProdts) == 1)
                    {
                        *contadorProdutos = *contadorProdutos - 1;
                    }
                }
                else
                {
                    printf("\n\aAVISO: Você não possui produtos cadastrados.\n");
                }

                break;

            case 5:
                flag = 0;

                if(*contadorProdutos > 0)
                {
                    salvarProdutos(*ptrProdutos, *tamanhoVetorProdts, *contadorProdutos);
                    printf("\nArquivo salvo com sucesso!");
                }
                else
                {
                    printf("\n\aAVISO: Você não possui produtos cadastrados.\n");
                }

                break;

            case 6:
                flag = 0;

                lerProdutos(*ptrProdutos, *tamanhoVetorProdts, *contadorProdutos);
                printf("\nArquivo lido com sucesso!");

                break;

            case 7:
                flag = 0;

                printf("\nVocê será redirecinado ao menu principal. Aperte qualquer tecla para continuar.");
                scanf("%c", &voltar);

                system("cls");

                break;

            default:
                flag = 1;
                printf("\n\aCódigo inválido!");
                scanf("%c", &voltar);

                system("cls");

                break;
            }

            if(codigo != 7)
            {
                printf("\n\nVocê será redirecinado ao menu de produtos. Aperte qualquer tecla para continuar.");
                scanf("%c", &voltar);
            }
        }
    }
}

void exibirProdutos(cadastro_produtos **ptrProdutos)
{
    char voltar;

    printf("%ld", (*ptrProdutos)->id);

    printf("\n\n=====\t\t||\t\t PRODUTOS \t\t||\t\t=====\n\n");
    printf("\n\t ID      \t Produto \t Preço        \t Estoque \t\n");

    while((*ptrProdutos)->next != NULL)
    {
        if((*ptrProdutos)->id > 0)
        {
            printf("\n\t %ld   \t\t   %s     \t R$ %.2f      \t %i      \t",
                   (*ptrProdutos)->id,
                   (*ptrProdutos)->nome,
                   (*ptrProdutos)->preco,
                   (*ptrProdutos)->estoque);
        }
        ptrProdutos = (*ptrProdutos)->next;
    }
}

void cadastrarProdutos(cadastro_produtos **ptrProdutos)
{
    int ptr = -1,
        estoque = -1,
        flag = 0;

    float preco = -1;

    long int id = -1;

    cadastro_produtos *novoProduto = (cadastro_produtos*) calloc(1, sizeof(cadastro_produtos));

    novoProduto->next = ptrProdutos;
    novoProduto->prev = NULL;

    if(ptrProdutos != NULL)
    {
        (*ptrProdutos)->prev = novoProduto;
    }

    while (flag == 0)
    {
        printf("\nDigite o ID do produto sendo este maior que 0: ");
        scanf("%li",&id);
        getchar();
        if(id < 1)
        {
            flag = 0;
            printf("\nCódigo inválido");
        }
        /*
        else if(procuraProduto(*ptrProdutos, id) != -1)
        {
            flag = 0;
            printf("\nCódigo ja existente!\n");
        }
        */
        else
        {
            flag = 1;
            novoProduto->id = id;
        }
    }

    printf("\nDigite o nome do produto de ID %li com até 25 caracteres: ", id);
    fgets(novoProduto->nome,25,stdin);

    char lenp1 = strlen(novoProduto->nome);

    if(novoProduto->nome[lenp1 -1]=='\n')
    {
        novoProduto->nome [--lenp1] = 0;
    }
    else
    {
        int ch;
        do ch = getchar();
        while (ch != '\n'); // limpa caracteres extra
    }

    do
    {
        printf("\nDigite o estoque do produto de ID %li sendo este valor maior ou igual a 0: ", id);
        scanf("%i", &estoque);
        getchar();

        if(estoque < 0)
        {
            printf("Quantidade inválida!");
        }

    }
    while(estoque < 0);

    novoProduto->estoque = estoque;

    do
    {
        printf("\nDigite o preço do produto de ID %li sendo este valor maior ou igual a 0: ", id);
        scanf("%f", &preco);
        getchar();

        if(preco < 0)
        {
            printf("Quantidade inválida!");
        }
    }
    while(preco < 0);

    novoProduto->preco = preco;

    *ptrProdutos = novoProduto;
}

void atualizarProduto(cadastro_produtos *ptrProdutos,
                      int tamanhoVetorProdts)
{
    printf("\n\n=====\t\t||\t\t ATUALIZAÇÃO DE PRODUTOS \t\t||\t\t=====\n\n");
    long int idDigitado = 0;

    int flag = 0,
        quantidadeAntiga,
        quantidadeNova = -1,
        indice;

    float valorAntigo,
          valorNovo = -1;

    char voltar;



    do
    {
        printf("\nDigite o ID do produto que você que alterar: ");
        scanf("%li", &idDigitado);
        getchar();

        indice = procuraProduto(ptrProdutos, idDigitado);

        flag = 1;

        if(indice == -1)
        {
            flag = 0;
            printf("\nProduto não encontrado!");
        }
    }
    while(flag == 0);


    quantidadeAntiga = ptrProdutos->estoque;
    valorAntigo = ptrProdutos->preco;



    do
    {
        printf("\nDigite o novo estoque do produto de ID %li sendo este valor maior ou igual a 0: ", ptrProdutos->id);
        scanf("%i", &ptrProdutos->estoque);
        getchar();

        if(ptrProdutos->estoque < 0)
        {
            printf("Quantidade inválida!");
        }
    }
    while(ptrProdutos->estoque < 0);

    do
    {
        printf("\nDigite o novo preço do produto de ID %li sendo este valor maior ou igual a 0: ", ptrProdutos[indice].id);
        scanf("%f", ptrProdutos->preco);
        getchar();

        if(ptrProdutos->preco < 0)
        {
            printf("Quantidade inválida!");
        }
    }
    while(ptrProdutos->preco < 0);

    system("cls");

    printf("\n\n=====\t\t||\t\t         ANTIGO          \t\t||\t\t=====\n\n");

    printf("\n\t ID     \t Produto \t Preço     \t Quantidade \t\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", ptrProdutos->id, ptrProdutos->nome, valorAntigo, quantidadeAntiga);

    printf("\n\n=====\t\t||\t\t          NOVO           \t\t||\t\t=====\n\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", ptrProdutos->id, ptrProdutos->nome, ptrProdutos->preco, ptrProdutos->estoque);
}

int excluirProduto(cadastro_produtos *ptrProdutos,
                   int *tamanhoVetorProdts)
{

    long int idDigitado = 0;

    int flag = 0,
        indice,
        confirma,
        retorno = 0;

    char voltar;


    printf("\n\n=====\t\t||\t\t EXCLUIR PRODUTOS \t\t||\t\t=====\n\n");

    do
    {
        printf("\nDigite o ID do produto que você que excluir: ");
        scanf("%li", &idDigitado);
        getchar();

        indice = procuraProduto(ptrProdutos, idDigitado);

        flag = 1;

        if(indice == -1)
        {
            flag = 0;
            printf("\nProduto não encontrado!");
        }
    }
    while(flag == 0);

    printf("\n\n=====\t\t||\t\t CONFIRMAR EXCLUSÃO \t\t||\t\t=====\n\n");
    printf("\n\t %d     \t %s      \t R$ %.2f   \t %d         \t", ptrProdutos[indice].id, ptrProdutos[indice].nome, ptrProdutos[indice].preco, ptrProdutos[indice].estoque);

    while(flag == 1)
    {
        printf("\n\nAperte 1 para confirmar e 2 para cancelar: ");
        scanf("%i", &confirma);
        getchar();

        switch(confirma)
        {
        case 1:
            flag = 0;
            ptrProdutos[indice].id = 0;
            printf("\nProduto excluido com sucesso.");
            retorno = 1;

            break;

        case 2:
            flag = 0;
            printf("\nAção cancelada.");
            retorno = 0;

            break;

        default:
            flag = 1;

            printf("\nCódigo inválido!");

            break;
        }
    }

    return retorno;
}

int procuraProduto(cadastro_produtos *ptrProdutos, long int idDigitado)
{

    int i = 0;
    int retorno = 0;

    return retorno;
}

void salvarProdutos(cadastro_produtos *ptrProdutos,
                    int tamanhoVetorProdts,
                    int contadorProdutos)
{
    int i = 0;

    FILE *arquivo = fopen("produtos.txt","w");
    if(arquivo == NULL)
    {
        printf("\nERRO NA ABERTURA DO ARQUIVO\n");
        exit(2);
    }
    printf("TESTE");
    fprintf(arquivo, "\nTamanhoVetorProdts: %d", tamanhoVetorProdts);
    fprintf(arquivo, "\nContadorProdutos: %d", contadorProdutos);
    printf("TESTE");

    for(i = 0; i < tamanhoVetorProdts; i++)
    {
        fprintf(arquivo, "\nID: %ld", ptrProdutos[i].id);
        fprintf(arquivo, "\nProduto: %s", ptrProdutos[i].nome);
        fprintf(arquivo, "\nEstoque: %d", ptrProdutos[i].estoque);
        fprintf(arquivo, "\nValor: %.2f", ptrProdutos[i].preco);
    }
    printf("TESTE");
    fclose(arquivo);
}

void lerProdutos(cadastro_produtos *ptrProdutos,
                 int *tamanhoVetorProdts,
                 int *contadorProdutos)
{
    int i = 0;

    FILE *arquivo = fopen("produtos.txt","r");

    if(arquivo == NULL)
    {
        printf("ERRO NA ABERTURA DO ARQUIVO");
        exit(2);
    }

    for(i = 0; i < tamanhoVetorProdts; i++) //usado para printar
    {
        fscanf(arquivo, "%d %d %ld %s %d %.2f", tamanhoVetorProdts, contadorProdutos, ptrProdutos[i].id, ptrProdutos[i].nome, ptrProdutos[i].estoque, ptrProdutos[i].preco);
    }

    fclose(arquivo);

}
