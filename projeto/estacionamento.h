#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#define FILEIRAS 4
#define COLUNAS 5
#define TOTAL_VAGAS (FILEIRAS * COLUNAS)

#define VAGA_LIVRE 0
#define VAGA_OCUPADA 1

#define TAM_IDENTIFICADOR 7
#define TAM_DESCRICAO 60

#define CATEGORIA_CARRO 1
#define CATEGORIA_MOTO 2

typedef struct {
    char identificador[TAM_IDENTIFICADOR + 1];
    char descricao[TAM_DESCRICAO + 1];
    int categoria;
    int fileira;
    int coluna;
} Veiculo;

void exibir_vagas (int matriz [FILEIRAS][COLUNAS]);

int normalizar_identificador(const char *entrada, char destino[TAM_IDENTIFICADOR + 1]);

#endif