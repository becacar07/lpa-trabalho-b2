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

#define CAPACIDADE_INICIAL 2

typedef struct {
    char identificador[TAM_IDENTIFICADOR + 1];
    char descricao[TAM_DESCRICAO + 1];
    int categoria;
    int fileira;
    int coluna;
} Veiculo;

typedef struct {
    Veiculo *itens;
    int quantidade;
    int capacidade;
} Colecao;

typedef enum {
    INSERCAO_OK = 0,
    INSERCAO_DADOS_INVALIDOS,
    INSERCAO_DUPLICADO,
    INSERCAO_POSICAO_INVALIDA,
    INSERCAO_VAGA_OCUPADA,
    INSERCAO_LOTADO,
    INSERCAO_FALHA_MEMORIA
} ResultadoInsercao;

void exibir_vagas (int matriz [FILEIRAS][COLUNAS]);

int normalizar_identificador(const char *entrada, char destino[TAM_IDENTIFICADOR + 1]);
void zerar_mapa(int mapa[FILEIRAS][COLUNAS]);
int descricao_valida(const char *descricao);
int categoria_valida(int categoria);
int posicao_valida(int fileira, int coluna);
int inicializar_colecao(Colecao *colecao);
int ampliar_colecao(Colecao *colecao);
int buscar_veiculo(const Colecao *colecao, const char *identificador);
ResultadoInsercao inserir_veiculo(Colecao *colecao, int mapa[FILEIRAS][COLUNAS],
const Veiculo *novo);
void liberar_colecao(Colecao *colecao);

void exibir_veiculo(const Veiculo *veiculo);
void listar_veiculos(const Colecao *colecao);
void mover_veiculo(Veiculo *veiculo, int mapa[FILEIRAS][COLUNAS], int fileira, int coluna);

#endif