#include <stdio.h>
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

int posicao_valida(int fileira, int coluna)
{
    return fileira >= 1 && fileira <= FILEIRAS &&
           coluna >= 1 && coluna <= COLUNAS;
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

int buscar_veiculo(const Colecao *colecao, const char *identificador)
{
    int i;

    if (colecao == NULL || identificador == NULL) {
        return -1;
    }

    for (i = 0; i < colecao->quantidade; i++) {
        if (strcmp(colecao->itens[i].identificador, identificador) == 0) {
            return i;
        }
    }

    return -1;
}

ResultadoInsercao inserir_veiculo(Colecao *colecao, int mapa[FILEIRAS][COLUNAS],
                                  const Veiculo *novo)
{
    Veiculo registro;

    if (colecao == NULL || colecao->itens == NULL || mapa == NULL || novo == NULL) {
        return INSERCAO_DADOS_INVALIDOS;
    }

    if (colecao->quantidade >= TOTAL_VAGAS) {
        return INSERCAO_LOTADO;
    }

    if (!normalizar_identificador(novo->identificador, registro.identificador) ||
        !descricao_valida(novo->descricao) ||
        !categoria_valida(novo->categoria)) {
        return INSERCAO_DADOS_INVALIDOS;
    }

    if (buscar_veiculo(colecao, registro.identificador) != -1) {
        return INSERCAO_DUPLICADO;
    }

    if (!posicao_valida(novo->fileira, novo->coluna)) {
        return INSERCAO_POSICAO_INVALIDA;
    }

    if (mapa[novo->fileira - 1][novo->coluna - 1] != VAGA_LIVRE) {
        return INSERCAO_VAGA_OCUPADA;
    }

    if (colecao->quantidade == colecao->capacidade) {
        if (!ampliar_colecao(colecao)) {
            return INSERCAO_FALHA_MEMORIA;
        }
    }

    strcpy(registro.descricao, novo->descricao);
    registro.categoria = novo->categoria;
    registro.fileira = novo->fileira;
    registro.coluna = novo->coluna;

    colecao->itens[colecao->quantidade] = registro;
    colecao->quantidade++;
    mapa[registro.fileira - 1][registro.coluna - 1] = VAGA_OCUPADA;

    return INSERCAO_OK;
}

void liberar_colecao(Colecao *colecao)
{
    if (colecao == NULL) {
        return;
    }

    free(colecao->itens);
    colecao->itens = NULL;
    colecao->quantidade = 0;
    colecao->capacidade = 0;
}

void exibir_veiculo(const Veiculo *veiculo)
{
    printf("ID: %s | Descrição: %s | Categoria: %s | Vaga: F%d/C%d\n",
           veiculo->identificador, veiculo->descricao,
           veiculo->categoria == CATEGORIA_CARRO ? "Carro" : "Moto",
           veiculo->fileira, veiculo->coluna);
}

void listar_veiculos(const Colecao *colecao)
{
    int i;

    if (colecao->quantidade == 0) {
        printf("Nenhum veículo cadastrado.\n");
        return;
    }

    printf("Veículos cadastrados: %d\n", colecao->quantidade);
    for (i = 0; i < colecao->quantidade; i++) {
        exibir_veiculo(&colecao->itens[i]);
    }
}