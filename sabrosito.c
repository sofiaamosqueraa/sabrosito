#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    char nome[50];
    int quantidade;
    float preco;
    int vendas;
} Produto;

Produto estoque[MAX_PRODUTOS];
int total_produtos = 0;

void limpar(char *linha) {
    linha[strcspn(linha, "\n")] = 0;
}

void adicionar_produto(char *nome, int quantidade, float preco) {
    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            estoque[i].quantidade += quantidade;
            return;
        }
    }
    strcpy(estoque[total_produtos].nome, nome);
    estoque[total_produtos].quantidade = quantidade;
    estoque[total_produtos].preco = preco;
    estoque[total_produtos].vendas = 0;
    total_produtos++;
}

void vender_produto(char *nome, int quantidade) {
    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            if (estoque[i].quantidade >= quantidade) {
                estoque[i].quantidade -= quantidade;
                estoque[i].vendas += quantidade;
                printf("Venda realizada: %d %s(s) vendidos. Estoque restante: %d.\n", quantidade, nome, estoque[i].quantidade);
            } else {
                printf("Estoque insuficiente para vender %d %s(s).\n", quantidade, nome);
            }
            return;
        }
    }
    printf("Produto não encontrado: %s.\n", nome);
}

void consultar_estoque() {
    printf("\nEstoque atual:\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("%s: %d disponível(s), Preço unitário: R$%.2f\n", estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
    }
    printf("\n");
}

void consultar_preco(char *nome) {
    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            printf("Preço de %s: R$%.2f\n", nome, estoque[i].preco);
            return;
        }
    }
    printf("Produto não encontrado: %s.\n", nome);
}

void alterar_preco(char *nome, float novo_preco) {
    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            estoque[i].preco = novo_preco;
            printf("Preço de %s alterado para: R$%.2f\n", nome, novo_preco);
            return;
        }
    }
    printf("Produto não encontrado: %s.\n", nome);
}

void alterar_quantidade(char *nome, int nova_quantidade) {
    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            estoque[i].quantidade = nova_quantidade;
            printf("Quantidade de %s alterada para: %d\n", nome, nova_quantidade);
            return;
        }
    }
    printf("Produto não encontrado: %s.\n", nome);
}

void remover_produto(char *nome) {
    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            for (int j = i; j < total_produtos - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            total_produtos--;
            printf("Produto %s removido do estoque.\n", nome);
            return;
        }
    }
    printf("Produto não encontrado: %s.\n", nome);
}

void relatorio_vendas() {
    printf("\nRelatório de Vendas:\n");
    for (int i = 0; i < total_produtos; i++) {
        printf("%s: %d unidade(s) vendida(s).\n", estoque[i].nome, estoque[i].vendas);
    }
    printf("\n");
}

void interpretar(char *linha) {
    if (strlen(linha) == 0) return;

    if (strncmp(linha, "arepa", 5) == 0) {
        char nome[50];
        int quantidade;
        float preco;
        if (sscanf(linha, "arepa %s %d %f", nome, &quantidade, &preco) == 3) {
            adicionar_produto(nome, quantidade, preco);
            printf("Produto adicionado: %s, Quantidade: %d, Preço: %.2f\n", nome, quantidade, preco);
        }
        return;
    }

    if (strncmp(linha, "empanada", 8) == 0) {
        char nome[50];
        int quantidade;
        if (sscanf(linha, "empanada %s %d", nome, &quantidade) == 2) {
            vender_produto(nome, quantidade);
        }
        return;
    }

    if (strncmp(linha, "buñuelo", 7) == 0) {
        consultar_estoque();
        return;
    }

    if (strncmp(linha, "pandebono", 9) == 0) {
        char nome[50];
        if (sscanf(linha, "pandebono %s", nome) == 1) {
            consultar_preco(nome);
        }
        return;
    }

    if (strncmp(linha, "bandeja_paisa", 13) == 0) {
        char nome[50];
        float preco;
        if (sscanf(linha, "bandeja_paisa %s %f", nome, &preco) == 2) {
            alterar_preco(nome, preco);
        }
        return;
    }

    if (strncmp(linha, "empanadita", 11) == 0) {
        char nome[50];
        int quantidade;
        if (sscanf(linha, "empanadita %s %d", nome, &quantidade) == 2) {
            alterar_quantidade(nome, quantidade);
        }
        return;
    }

    if (strncmp(linha, "arepita", 7) == 0) {
        char nome[50];
        if (sscanf(linha, "arepita %s", nome) == 1) {
            remover_produto(nome);
        }
        return;
    }

    if (strncmp(linha, "sancocho", 8) == 0) {
        relatorio_vendas();
        return;
    }

    printf("Comando não reconhecido: %s\n", linha);
}

int main() {
    char linha[256];
    printf("Bem-vindo ao Sabrosito - Sistema de Vendas e Estoque!\n");

    while (1) {
        printf("\nDigite um comando (ou 'sair' para encerrar): ");
        fgets(linha, sizeof(linha), stdin);
        limpar(linha);

        if (strcmp(linha, "sair") == 0) {
            printf("Saindo do sistema...\n");
            break;
        }

        interpretar(linha);
    }

    return 0;
}
