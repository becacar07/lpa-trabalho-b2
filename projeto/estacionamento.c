#include <stdlib.h>
#include <string.h>

#include "estacionamento.h"

void exibir_vagas (int matriz[FILEIRAS][COLUNAS]){
    for (int i = 0; i < FILEIRAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            printf ("[%d]  ", matriz[i][j]);
        }
    printf ("\n");
    }
}

void zerar_mapa(int mapa[FILEIRAS][COLUNAS])
{
    int i, j;

    for (i = 0; i < FILEIRAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            mapa[i][j] = VAGA_LIVRE;
        }
    }
}

int normalizar_identificador(const char *entrada, char destino[TAM_IDENTIFICADOR + 1])
{
    char temporario[TAM_IDENTIFICADOR + 1];
    int i;

    if (entrada == NULL || destino == NULL) {
        return 0;
    }

    if (strlen(entrada) != TAM_IDENTIFICADOR) {
        return 0;
    }

    for (i = 0; i < TAM_IDENTIFICADOR; i++) {
        char c = entrada[i];

        if (c >= 'a' && c <= 'z') {
            temporario[i] = (char)(c - 'a' + 'A');
        } else if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            temporario[i] = c;
        } else {
            return 0;
        }
    }
    temporario[TAM_IDENTIFICADOR] = '\0';

    strcpy(destino, temporario);
    return 1;
}

int descricao_valida(const char *descricao)
{
    size_t tamanho;

    if (descricao == NULL) {
        return 0;
    }

    tamanho = strlen(descricao);
    return tamanho >= 1 && tamanho <= TAM_DESCRICAO;
}

int categoria_valida(int categoria)
{
    return categoria == CATEGORIA_CARRO || categoria == CATEGORIA_MOTO;
}

int inicializar_colecao(Colecao *colecao)
{
    if (colecao == NULL) {
        return 0;
    }

    colecao->quantidade = 0;
    colecao->itens = malloc(CAPACIDADE_INICIAL * sizeof(Veiculo));

    if (colecao->itens == NULL) {
        colecao->capacidade = 0;
        return 0;
    }

    colecao->capacidade = CAPACIDADE_INICIAL;
    return 1;
}

int ampliar_colecao(Colecao *colecao)
{
    Veiculo *novo_bloco;
    int nova_capacidade;

    if (colecao == NULL || colecao->itens == NULL || colecao->capacidade <= 0) {
        return 0;
    }

    nova_capacidade = colecao->capacidade * 2;
    novo_bloco = realloc(colecao->itens, (size_t)nova_capacidade * sizeof(Veiculo));

    if (novo_bloco == NULL) {
        return 0;
    }

    colecao->itens = novo_bloco;
    colecao->capacidade = nova_capacidade;
    return 1;
}