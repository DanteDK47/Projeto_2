#include <stdio.h>
#include <string.h>

typedef enum { 
    Acougue, 
    Padaria, 
    Mercado 
} Secao;

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
    Secao secao;
} Produto;

void cadastrarProduto(Produto *produtos, int *totalProdutos) {
    printf("Nome do produto: ");
    scanf("%s", produtos[*totalProdutos].nome);
    getchar();

    printf("Preço do produto: ");
    scanf("%f", &produtos[*totalProdutos].preco);
    getchar();

    printf("Quantidade: ");
    scanf("%d", &produtos[*totalProdutos].quantidade);
    getchar();

    int secao;
    printf("Escolha a seção do produto (0 - Açougue, 1 - Padaria, 2 - Mercado): ");
    scanf("%d", &secao);
    getchar();
    produtos[*totalProdutos].secao = (Secao)secao;

    produtos[*totalProdutos].codigo = *totalProdutos + 1;
    (*totalProdutos)++;
}

void listarProdutosPorSecao(Produto *produtos, int totalProdutos, Secao secao) {
    printf("Produtos na seção %s:\n", secao == Acougue ? "Açougue" : secao == Padaria ? "Padaria" : "Mercado");

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].secao == secao) {
            printf("Código: %d | Nome: %s | Preço: %.2f | Quantidade: %d\n", 
                   produtos[i].codigo, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
        }
    }
}
void realizarVenda(Produto *produtos, int totalProdutos) {
    int codigoProduto, quantidade;
    printf("Informe o código do produto: ");
    scanf("%d", &codigoProduto);
    getchar();

    printf("Quantidade desejada: ");
    scanf("%d", &quantidade);
    getchar();

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigoProduto) {
            if (produtos[i].quantidade >= quantidade) {
                produtos[i].quantidade -= quantidade;
                printf("Venda realizada: %d unidade(s) de %s.\n", quantidade, produtos[i].nome);

                FILE *vendas = fopen("vendas.txt", "a");
                fprintf(vendas, "Produto: %s | Quantidade: %d | Total: R$%.2f | Seção: %s\n", 
                        produtos[i].nome, quantidade, produtos[i].preco * quantidade, 
                        produtos[i].secao == Acougue ? "Açougue" : produtos[i].secao == Padaria ? "Padaria" : "Mercado");
                fclose(vendas);

                return;
            } else {
                printf("Quantidade insuficiente em estoque.\n");
                return;
            }
        }
    }
    printf("Produto não encontrado.\n");
}

void gerarRelatorioPorSecao(Secao secao) {
    printf("Relatório de vendas da seção %s:\n", secao == Acougue ? "Açougue" : secao == Padaria ? "Padaria" : "Mercado");

    FILE *vendas = fopen("vendas.txt", "r");
    if (vendas == NULL) {
        printf("Nenhuma venda registrada até o momento.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), vendas)) {
        if (strstr(linha, secao == Acougue ? "Açougue" : secao == Padaria ? "Padaria" : "Mercado")) {
            printf("%s", linha);
        }
    }
    fclose(vendas);
}

int main() {
    Produto produtos[100];
    int totalProdutos = 0;
    int opcao;

    do {
        printf("\n==== Sistema de Vendas do Mercado ====\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos por seção\n");
        printf("3. Realizar venda\n");
        printf("4. Gerar relatório de vendas por seção\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &totalProdutos);
                break;
            case 2: {
                int secao;
                printf("Escolha a seção (0 - Açougue, 1 - Padaria, 2 - Mercado): ");
                scanf("%d", &secao);
                getchar();
                listarProdutosPorSecao(produtos, totalProdutos, (Secao)secao);
                break;
            }
            case 3:
                realizarVenda(produtos, totalProdutos);
                break;
            case 4: {
                int secao;
                printf("Escolha a seção (0 - Açougue, 1 - Padaria, 2 - Mercado): ");
                scanf("%d", &secao);
                getchar();
                gerarRelatorioPorSecao((Secao)secao);
                break;
            }
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
