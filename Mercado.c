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

int main() {
    Produto produtos[100];
    int totalProdutos = 0;
    int opcao;

    do {
        printf("\n Sistema de Vendas do Mercado \n");
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
