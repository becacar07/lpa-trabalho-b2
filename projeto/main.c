#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "estacionamento.h"

#define TAM_LINHA 100

void ler_texto(char *texto, int tamanho)
{
    if (fgets(texto, tamanho, stdin) == NULL) {
        texto[0] = '\0';
        return;
    }

    int len = strlen(texto);

    if (len > 0 && texto[len - 1] == '\n') {
        texto[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

int ler_inteiro(void)
{
    char linha[TAM_LINHA];
    int numero;
    char sobra;

    ler_texto(linha, TAM_LINHA);

    if (sscanf(linha, "%d %c", &numero, &sobra) != 1) {
        return -1;
    }
    return numero;
}

void cadastrar_veiculo(Colecao *colecao, int mapa[FILEIRAS][COLUNAS])
{
    Veiculo novo;
    char linha[TAM_LINHA];
    int capacidade_antes;
    ResultadoInsercao resultado;

    if (colecao->quantidade >= TOTAL_VAGAS) {
        printf("Estacionamento lotado! Cadastro recusado.\n");
        return;
    }

    printf("Identificador (7 letras ou números): ");
    ler_texto(linha, TAM_LINHA);
    if (!normalizar_identificador(linha, novo.identificador)) {
        printf("Identificador inválido! Use 7 caracteres, só letras e números.\n");
        return;
    }
    if (buscar_veiculo(colecao, novo.identificador) != -1) {
        printf("Já existe um veículo com o identificador %s.\n", novo.identificador);
        return;
    }

    printf("Descrição: ");
    ler_texto(linha, TAM_LINHA);
    if (!descricao_valida(linha)) {
        printf("Descrição inválida! Não pode ser vazia nem passar de 60 caracteres.\n");
        return;
    }
    strcpy(novo.descricao, linha);

    printf("Categoria (1 - carro, 2 - moto): ");
    novo.categoria = ler_inteiro();
    if (!categoria_valida(novo.categoria)) {
        printf("Categoria inválida!\n");
        return;
    }

    printf("Fileira (1 a 4): ");
    novo.fileira = ler_inteiro();
    printf("Coluna (1 a 5): ");
    novo.coluna = ler_inteiro();
    if (!posicao_valida(novo.fileira, novo.coluna)) {
        printf("Posição inválida!\n");
        return;
    }

    capacidade_antes = colecao->capacidade;
    resultado = inserir_veiculo(colecao, mapa, &novo);

    if (resultado == INSERCAO_OK) {
        printf("Veículo %s cadastrado na vaga F%d/C%d.\n", novo.identificador, novo.fileira, novo.coluna);
        if (colecao->capacidade > capacidade_antes) {
            printf("Capacidade da lista aumentou de %d para %d.\n", capacidade_antes, colecao->capacidade);
        }
    } else if (resultado == INSERCAO_VAGA_OCUPADA) {
        printf("A vaga F%d/C%d já está ocupada!\n", novo.fileira, novo.coluna);
    } else if (resultado == INSERCAO_FALHA_MEMORIA) {
        printf("Erro de memória! O veículo não foi cadastrado.\n");
    } else {
        printf("Não foi possível cadastrar o veículo.\n");
    }
}

void exibir_menu(void)
{
    printf("\n===== ESTACIONAMENTO =====\n");
    printf("1 - Cadastrar veículo\n");
    printf("2 - Consultar veículo por identificador\n");
    printf("3 - Atualizar descrição ou categoria\n");
    printf("4 - Mover veículo para outra vaga\n");
    printf("5 - Remover veículo\n");
    printf("6 - Listar veículos cadastrados\n");
    printf("7 - Exibir mapa de vagas\n");
    printf("8 - Exibir relatório da ocupação\n");
    printf("0 - Encerrar\n");
}

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif
    setlocale(LC_ALL, "Portuguese");

    int vagas[FILEIRAS][COLUNAS];
    Colecao colecao;
    int opcao;

    zerar_mapa(vagas);

    if (!inicializar_colecao(&colecao)) {
        printf("Erro ao reservar memória.\n");
        return 1;
    }

    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        opcao = ler_inteiro();

        switch (opcao) {
            case 1:
                cadastrar_veiculo(&colecao, vagas);
                break;
            case 2: case 3: case 4: case 5: case 6: case 7: case 8:
                printf("Opção em construção.\n");
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    liberar_colecao(&colecao);
    printf("Memória liberada. Até mais!\n");
    return 0;
}