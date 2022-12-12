#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#include "headers.h"

void menuDeVendas(cadastro_produtos **ptrProdutos,
                  int tamanhoVetorProdts)
{

    char voltar = 'q';

    int flag = 1,
        codigo,
        i,
        quantidade = 0;

    cadastro_produtos *auxHead = (cadastro_produtos*) calloc(1,sizeof(cadastro_produtos));
    auxHead = *ptrProdutos;

    while(flag == 1)
    {
        while(codigo != 3)
        {

            system("cls");

            printf("\n\n=====\t\t||\t\t MENU DE VENDAS \t\t||\t\t=====\n\n");

            printf("\n \t Código  \t Opção              \t\n");
            printf("\n \t 1       \t Realizar venda           \t");
            printf("\n \t 2       \t Relatorio de venda          \t");
            printf("\n \t 3       \t Voltar             \t\n");

            printf("\nDigite o código para selecionar a opção: ");
            scanf("%d", &codigo);
            getchar();

            switch(codigo)
            {
            case 1:
                flag = 0;

                long int idDigitado;

                int encerrarCompra = 1, qtdCompra;

                float subtotalFinal = 0,
                      subtotal = 0;

                cadastro_produtos *auxCompra = (cadastro_produtos*) calloc(1, sizeof(cadastro_produtos));


                while(encerrarCompra != 3)
                {
//validacao se o id existe
                    system("cls");

                    auxCompra = *ptrProdutos;
                    qtdCompra = 0;

                    printf("\n\n=====\t\t||\t\t PRODUTOS \t\t||\t\t=====\n\n");
                    printf("\n\t ID      \t Produto \t Preço        \t Estoque \t\n");

                    while(auxCompra != NULL)
                    {
                        if(auxCompra->id > 0)
                        {
                            printf("\n\t %ld   \t\t   %s     \t R$ %.2f      \t %i      \t",
                                   auxCompra->id,
                                   auxCompra->nome,
                                   auxCompra->preco,
                                   auxCompra->estoque);
                        }

                        auxCompra = auxCompra->next;
                    }

                    auxCompra = *ptrProdutos;

                    int retorno = 0;
                    while (retorno == 0)
                    {
                        printf("\n\nDigite o ID do produto que você deseja comprar: ");
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
                        }
                        else
                        {
                            printf("\nProduto não encontrado");
                            retorno = 0;

                            *ptrProdutos = auxHead;

                        }
                    }
//fechamento da validacao do id

//validacao de estoque

                    int flagQuantidadeCompra = 0;

                    do
                    {
                        printf("\nDigite a quantidade desejada: ");
                        scanf("%d", &qtdCompra);

                        if(qtdCompra > (*ptrProdutos)->estoque || qtdCompra < 0)
                        {
                            flagQuantidadeCompra = 0;
                            if((*ptrProdutos)->estoque == 0)
                            {
                                printf("\nProduto não possui estoque!");
                                break;
                            }
                            else
                            {
                                printf("\nQuantidade desejada inválida!");
                            }
                        }
                        else
                        {
//fechamento da validacao de estoque
                            flagQuantidadeCompra = 1;

                            (*ptrProdutos)->qtdCompra = (*ptrProdutos)->qtdCompra + qtdCompra;

                            (*ptrProdutos)->qtdVendida = (*ptrProdutos)->qtdVendida + qtdCompra;
                            (*ptrProdutos)->estoque = (*ptrProdutos)->estoque - qtdCompra;
                            (*ptrProdutos)->subtotal = (*ptrProdutos)->subtotal + (qtdCompra * (*ptrProdutos)->preco);
                            (*ptrProdutos)->valorVendido = (*ptrProdutos)->valorVendido + (*ptrProdutos)->subtotal;

//calculo do subtotal da compra
                            subtotal = subtotal + (*ptrProdutos)->subtotal;
                            printf("\nValor do subtotal da compra é: R$ %.2f", subtotal);
                            break;
                        }
                    }
                    while(flagQuantidadeCompra == 0);

                    printf("\n\nDeseja realizar outra compra? Digite 3 para NÃO ou qualquer outro número para SIM: ");
                    scanf("%i", &encerrarCompra);
                    getchar();

                    *ptrProdutos = auxHead;
                }

                system("cls");

                cadastro_produtos *auxCarrinho = (cadastro_produtos*) calloc(1,sizeof(cadastro_produtos));

                auxCarrinho = *ptrProdutos;

                printf("\n\n=====\t\t||\t\t CARRINDO DE COMPRAS \t\t||\t\t=====\n\n");
                printf("\t ID       \t Produto           \t Estoque      \t Quantidade vendida    \t Valor vendido   \t\n\n");

                while(auxCarrinho != NULL)
                {
                    if(auxCarrinho->id > 0 )
                    {
                        printf("\t %ld      \t %s              \t\t %i           \t %i                    \t R$ %.2f         \t\n",
                               auxCarrinho->id,
                               auxCarrinho->nome,
                               auxCarrinho->estoque,
                               auxCarrinho->qtdCompra,
                               auxCarrinho->subtotal);
                    }
                    auxCarrinho = auxCarrinho->next;
                }

                cadastro_produtos * auxSubtotal = (cadastro_produtos*) calloc(1, sizeof(cadastro_produtos));
                auxSubtotal = *ptrProdutos;

                while(auxSubtotal != NULL)
                {
                    subtotalFinal = subtotalFinal + auxSubtotal->subtotal;
                    auxSubtotal = auxSubtotal->next;
                }

                printf("\nValor total de sua compra: R$ %0.2f.", subtotalFinal);

                printf("\n\n=====\t\t||\t\t ESCOLHA DA FORMA DE PAGAMENTO \t\t||\t\t=====\n\n");

                int i = 0, flagPagamento = 1, flag2, formaDePagamento, quantidadeDeParcelas, precisaDeTroco;
                float  valorEntreguePeloCliente, troco, valorDaParcela;
                char sair;

                printf("\nAgora escolha a forma de pagamento. Temos o pagamento A VISTA e o pagamento A PRAZO.\n\nNo pagamento A VISTA, em compras de ate R\$ 50.00, damos 5 porcento de desconto, em compras de R\$ 50.00 a R\$ 99.99 oferecemos 10 porcento de desconto e em compras acima de R\$ 99.99 promovemos 18 porcento de desconto.\n\nNo pagamento A PRAZO, em compras parceladas em ate 3x temos um acrescimo de 5 porcento e, em compras com parcelas acima de 3x, um acrescimo de 8 porcento");

                printf("\n\nDigite 1 para pagamento A VISTA e 2 para pagamento A PRAZO: ");
                scanf("%i", &formaDePagamento);
                getchar();

                while(flagPagamento == 1)
                {

                    switch(formaDePagamento)
                    {

                    case 1:
                        flagPagamento = 0;
                        if(subtotalFinal <= 50)
                        {
                            subtotalFinal = subtotalFinal - (subtotalFinal * 0.05);
                        }
                        else if((subtotalFinal > 50)&&(subtotalFinal < 100))
                        {
                            subtotalFinal = subtotalFinal - (subtotalFinal* 0.1);
                        }
                        else
                        {
                            subtotalFinal = subtotalFinal - (subtotalFinal* 0.18);
                        }

                        break;

                    case 2:
                        flagPagamento = 0;
                        printf("\n\nPor favor, nos diga a quantidade de parcelas: ");
                        scanf("%i", &quantidadeDeParcelas);
                        getchar();

                        while(quantidadeDeParcelas<1)
                        {
                            printf("\nNúmero de parcelas inválido, digite um valor igual ou acima de 1: ");
                            scanf("%i", &quantidadeDeParcelas);
                            getchar();
                        }

                        if(quantidadeDeParcelas <= 3)
                        {
                            subtotalFinal= subtotalFinal+ (subtotalFinal* 0.05);
                        }
                        else
                        {
                            subtotalFinal = subtotalFinal + (subtotalFinal * 0.08);
                        }

                        break;

                    default:
                        flagPagamento = 1;
                        printf("\nOpção de pagamento inválida, digite 1 para pagamento A VISTA e 2 para A PRAZO: ");
                        scanf("%i", &formaDePagamento);
                        getchar();

                    }
                }

                printf("\nTotal da compra: R$%.2f\n", subtotalFinal);

                if(formaDePagamento == 1)
                {
                    printf("\nVocê precisa de troco? Digite 1 para SIM ou qualquer outra tecla para NÃO: ");
                    scanf("%i", &precisaDeTroco);
                    getchar();

                    printf("\nPor favor, nos diga o valor que voce ira entregar: ");
                    scanf("%f", &valorEntreguePeloCliente);
                    getchar();

                    if(precisaDeTroco != 1)
                    {
                        while(valorEntreguePeloCliente != subtotalFinal)
                        {
                            printf("\nValor inválido, sua compra tem um total de: R$%f. Por favor, nos entregue o mesmo valor: ", subtotalFinal);
                            scanf("%f", &valorEntreguePeloCliente);
                            getchar();
                        }
                    }

                    while (valorEntreguePeloCliente<subtotalFinal)
                    {
                        printf("\nValor insuficiente, sua compra tem um total de: R$%.2f. Digite um valor válido: ", subtotalFinal);
                        scanf("%f", &valorEntreguePeloCliente);
                        getchar();
                    }
                    troco = valorEntreguePeloCliente - subtotalFinal;
                    if(precisaDeTroco == 1)
                    {
                        printf("\nAqui esta seu troco: R$%.2f\n", troco);

                    }
                }
                else
                {
                    valorDaParcela = subtotalFinal / quantidadeDeParcelas;
                    printf("\nO valor de suas parcelas ficou em: R$%.2f\n", valorDaParcela);
                }

                printf("\nMuito obrigado pela sua compra, volte sempre!\n");

                char nomeArquivo[40];

                struct tm *timenow;

                time_t now = time(NULL);
                timenow = gmtime(&now);

                strftime(nomeArquivo, sizeof(nomeArquivo), "%Y-%m-%d_%H-%M-%S.txt", timenow);

                FILE *arquivo = fopen(nomeArquivo, "w");

                if(nomeArquivo == NULL)
                {
                    printf("ERRO NA ABERTURA DO ARQUIVO");
                    exit(1);
                }

                cadastro_produtos *auxNf = (cadastro_produtos*) calloc(1, sizeof(cadastro_produtos));
                auxNf = *ptrProdutos;

                while(auxNf != NULL)
                {
                    fprintf(arquivo, "\nID: %ld", auxNf->id);
                    fprintf(arquivo, "\nProduto: %s", auxNf->nome);
                    fprintf(arquivo, "\nQuantidade vendida: %d", auxNf->qtdCompra);
                    fprintf(arquivo, "\nValor vendido: %.2f", auxNf->subtotal);

                    auxNf = auxNf->next;
                }

                fclose(arquivo);
                printf("\nNota fiscal salva com sucesso!");



                while(*ptrProdutos != NULL)
                {
                    (*ptrProdutos)->subtotal = 0;
                    (*ptrProdutos)->qtdCompra = 0;

                    *ptrProdutos = (*ptrProdutos)->next;
                }

                *ptrProdutos = auxHead;
                break;

            case 2:
                flag = 0;

                system("cls");

                cadastro_produtos *auxRelatorio = (cadastro_produtos*) calloc(1,sizeof(cadastro_produtos));

                auxRelatorio = *ptrProdutos;

                printf("\n\n=====\t\t||\t\t RELATÓRIO DE VENDAS \t\t||\t\t=====\n\n");
                printf("\t ID       \t Produto           \t Estoque      \t Quantidade vendida    \t Valor vendido   \t\n\n");

                while(auxRelatorio != NULL)
                {
                    if(auxRelatorio->id > 0 )
                    {
                        printf("\t %ld      \t %s              \t\t %i           \t %i                    \t R$ %.2f         \t\n",
                               auxRelatorio->id,
                               auxRelatorio->nome,
                               auxRelatorio->estoque,
                               auxRelatorio->qtdVendida,
                               auxRelatorio->valorVendido);
                    }
                    auxRelatorio = auxRelatorio->next;
                }


                break;

            case 3:
                flag = 0;

                printf("\nVocê será redirecinado ao menu principal. Aperte qualquer tecla para continuar.");
                scanf("%c", &voltar);

                system("cls");

                break;

            default:
                flag = 1;

                printf("\n\aCódigo inválido! Digite qualquer tecla para retornar ao menu de vendas.");
                scanf("%c", &voltar);

                system("cls");

                break;
            }
            if(codigo != 3)
            {
                printf("\n\nVocê será redirecinado ao menu de vendas. Aperte qualquer tecla para continuar.");
                scanf("%c", &voltar);
            }
        }
    }
}

void compras(cadastro_produtos *ptrProdutos,
             int tamanhoVetorProdts)
{
    long int iddesejado,
         indice;

    int encerrarCompra = 1,
        codigo = 1,
        i = 0;

    char voltar;

    float subtotalFinal = 0,
          subtotal = 0;

    while(encerrarCompra != 3)
    {
//validacao se o id existe
        system("cls");
        exibirProdutos(ptrProdutos);
        do
        {
            printf("\n\nDigite a ID do produto desejado: ");
            scanf("%ld",&iddesejado);

            indice = procuraProduto(ptrProdutos, iddesejado);

            if(indice == -1)
            {
                printf("\n\aProduto não existente!");
            }
        }
        while(indice==-1);
//fechamento da validacao do id

//validacao de estoque
        do
        {
            printf("\nDigite a quantidade desejada: ");
            scanf("%d",&ptrProdutos[indice].qtdCompra);

            if(ptrProdutos[indice].qtdCompra > ptrProdutos[indice].estoque)
            {
                if(ptrProdutos[indice].estoque == 0)
                {
                    printf("\nProduto não possui estoque!");
                    break;
                }
                else
                {
                    printf("\nQuantidade desejada inválida!");
                }
            }
            else
            {
//fechamento da validacao de estoque

                ptrProdutos[indice].qtdVendida = ptrProdutos[indice].qtdVendida + ptrProdutos[indice].qtdCompra;
                ptrProdutos[indice].estoque = ptrProdutos[indice].estoque - ptrProdutos[indice].qtdCompra;
                ptrProdutos[indice].subtotal = ptrProdutos[indice].subtotal + (ptrProdutos[indice].qtdCompra * ptrProdutos[indice].preco);
                ptrProdutos[indice].valorVendido = ptrProdutos[indice].valorVendido + ptrProdutos[indice].subtotal;

//calculo do subtotal da compra
                subtotal = subtotal + ptrProdutos[indice].subtotal;
                printf("\nValor do subtotal da compra é: R$ %.2f", subtotal);
                break;
            }
        }
        while(ptrProdutos[indice].qtdCompra > ptrProdutos[indice].estoque);

        printf("\n\nDeseja realizar outra compra? Digite 3 para NÃO ou qualquer outro número para SIM: ");
        scanf("%i", &encerrarCompra);
        getchar();
    }

    relatorioDeVendasOuCarrinho(ptrProdutos,
                                tamanhoVetorProdts,
                                codigo);

    for(i = 0; i<tamanhoVetorProdts; i++)
    {
        subtotalFinal = subtotalFinal + ptrProdutos[i].subtotal;
    }

    printf("\nValor total de sua compra: R$ %0.2f.", subtotalFinal);

    formaDePagamento (subtotalFinal);
    salvarVenda(ptrProdutos,
                tamanhoVetorProdts);


}

// Caso o switch case seja 1 a função mostrará um carrinho de compras
// caso seja 2, mostrará o relatório de vendas
void relatorioDeVendasOuCarrinho(cadastro_produtos *ptrProdutos,
                                 int tamanhoVetorProdts,
                                 int codigo)
{
    int i,
        j,         // Indices a serem percorridos
        troca;     // Variável para inidicar se houve alguma troca

    cadastro_produtos aux;

    for(i=0; i < tamanhoVetorProdts; i++)
    {
        troca = 0;
        for(j=0; j < tamanhoVetorProdts; j++)
        {
            // Se o conteúdo do vetor na posição j é menor do que o conteúdo do vetor na próxima posição (j+1):
            // Então troque os conteúdos de lugar
            if(ptrProdutos[j].valorVendido < ptrProdutos[j+1].valorVendido)
            {
                aux = ptrProdutos[j];
                ptrProdutos[j] = ptrProdutos[j+1];
                ptrProdutos[j+1] = aux;
            }
        }
        // Se não houve nenhuma troca, o vetor já está ordenado
        if(troca == 0)
        {
            break;
        }
    }

    if(codigo == 1)
    {
        system("cls");
        printf("\n\n=====\t\t||\t\t CARRINHO DE COMPRAS \t\t||\t\t=====\n\n");
        printf("\tID         \tProduto              \tEstoque       \tQuantidade vendida    \tValor vendido   \t\n");

        for(int i = 0; i<tamanhoVetorProdts; i++)
        {
            if(ptrProdutos[i].id > 0 && ptrProdutos[i].qtdCompra > 0)
            {
                printf("\t%ld        \t%s                   \t%i            \t%i                    \tR$ %.2f         \t\n",
                       ptrProdutos[i].id,
                       ptrProdutos[i].nome,
                       ptrProdutos[i].estoque,
                       ptrProdutos[i].qtdCompra,
                       ptrProdutos[i].subtotal);
            }
        }
    }
    else
    {
        printf("\n\n=====\t\t||\t\t RELATÓRIO DE VENDAS \t\t||\t\t=====\n\n");
        printf("\t ID       \t Produto           \t Estoque      \t Quantidade vendida    \t Valor vendido   \t\n\n");

        for(int i = 0; i<tamanhoVetorProdts; i++)
        {
            if(ptrProdutos[i].id > 0)
            {
                printf("\t %ld      \t %s              \t\t %i           \t %i                    \t R$ %.2f         \t\n",

                       ptrProdutos[i].id,
                       ptrProdutos[i].nome,
                       ptrProdutos[i].estoque,
                       ptrProdutos[i].qtdVendida,
                       ptrProdutos[i].valorVendido);
            }
        }
    }


}

void formaDePagamento(float subtotalFinal )

{
    // flistaDeCompras();

    printf("\n\n=====\t\t||\t\t ESCOLHA DA FORMA DE PAGAMENTO \t\t||\t\t=====\n\n");

    int i = 0, flag = 1, flag2, formaDePagamento, quantidadeDeParcelas, precisaDeTroco;
    float  valorEntreguePeloCliente, troco, valorDaParcela;
    char sair;



    printf("\nAgora escolha a forma de pagamento. Temos o pagamento A VISTA e o pagamento A PRAZO.\n\nNo pagamento A VISTA, em compras de ate R\$ 50.00, damos 5 porcento de desconto, em compras de R\$ 50.00 a R\$ 99.99 oferecemos 10 porcento de desconto e em compras acima de R\$ 99.99 promovemos 18 porcento de desconto.\n\nNo pagamento A PRAZO, em compras parceladas em ate 3x temos um acrescimo de 5 porcento e, em compras com parcelas acima de 3x, um acrescimo de 8 porcento");

    printf("\n\nDigite 1 para pagamento A VISTA e 2 para pagamento A PRAZO: ");
    scanf("%i", &formaDePagamento);
    getchar();

    while(flag == 1)
    {


        switch(formaDePagamento)
        {

        case 1:
            flag = 0;
            if(subtotalFinal <= 50)
            {
                subtotalFinal = subtotalFinal - (subtotalFinal * 0.05);
            }
            else if((subtotalFinal > 50)&&(subtotalFinal < 100))
            {
                subtotalFinal = subtotalFinal - (subtotalFinal* 0.1);
            }
            else
            {
                subtotalFinal = subtotalFinal - (subtotalFinal* 0.18);
            }

            break;

        case 2:
            flag = 0;
            printf("\n\nPor favor, nos diga a quantidade de parcelas: ");
            scanf("%i", &quantidadeDeParcelas);
            getchar();

            while(quantidadeDeParcelas<1)
            {
                printf("\nNúmero de parcelas inválido, digite um valor igual ou acima de 1: ");
                scanf("%i", &quantidadeDeParcelas);
                getchar();
            }

            if(quantidadeDeParcelas <= 3)
            {
                subtotalFinal= subtotalFinal+ (subtotalFinal* 0.05);
            }
            else
            {
                subtotalFinal = subtotalFinal + (subtotalFinal * 0.08);
            }

            break;

        default:
            flag = 1;
            printf("\nOpção de pagamento inválida, digite 1 para pagamento A VISTA e 2 para A PRAZO: ");
            scanf("%i", &formaDePagamento);
            getchar();

        }
    }

    printf("\nTotal da compra: R$%.2f\n", subtotalFinal);

    if(formaDePagamento==1)
    {
        printf("\nVocê precisa de troco? Digite 1 para SIM ou qualquer outra tecla para NÃO: ");
        scanf("%i", &precisaDeTroco);
        getchar();

        printf("\nPor favor, nos diga o valor que voce ira entregar: ");
        scanf("%f", &valorEntreguePeloCliente);
        getchar();

        if(precisaDeTroco != 1)
        {
            while(valorEntreguePeloCliente != subtotalFinal)
            {
                printf("\nValor inválido, sua compra tem um total de: R$%f. Por favor, nos entregue o mesmo valor: ", subtotalFinal);
                scanf("%f", &valorEntreguePeloCliente);
                getchar();
            }
        }

        while (valorEntreguePeloCliente<subtotalFinal)
        {
            printf("\nValor insuficiente, sua compra tem um total de: R$%.2f. Digite um valor válido: ", subtotalFinal);
            scanf("%f", &valorEntreguePeloCliente);
            getchar();
        }
        troco = valorEntreguePeloCliente - subtotalFinal;
        if(precisaDeTroco == 1)
        {
            printf("\nAqui esta seu troco: R$%.2f\n", troco);

        }
    }
    else
    {
        valorDaParcela = subtotalFinal / quantidadeDeParcelas;
        printf("\nO valor de suas parcelas ficou em: R$%.2f\n", valorDaParcela);
    }

    printf("\nMuito obrigado pela sua compra, volte sempre!\n");

    return 0;
}

void salvarVenda(cadastro_produtos *ptrProdutos,
                 int tamanhoVetorProdts)
{
    int i = 0;
    char nomeArquivo[40];

    struct tm *timenow;

    time_t now = time(NULL);
    timenow = gmtime(&now);

    strftime(nomeArquivo, sizeof(nomeArquivo), "%Y-%m-%d_%H-%M-%S.txt", timenow);

    FILE *arquivo = fopen(nomeArquivo, "w");

    if(nomeArquivo == NULL)
    {
        printf("ERRO NA ABERTURA DO ARQUIVO");
        exit(1);
    }

    for(i = 0; i < tamanhoVetorProdts; i++)
    {
        fprintf(arquivo, "\nID: %ld", ptrProdutos[i].id);
        fprintf(arquivo, "\nProduto: %s", ptrProdutos[i].nome);
        fprintf(arquivo, "\nQuantidade vendida: %d", ptrProdutos[i].qtdCompra);
        fprintf(arquivo, "\nValor vendido: %.2f", ptrProdutos[i].subtotal);
    }

    fclose(arquivo);
    printf("\nNota fiscal salva com sucesso!");
}
