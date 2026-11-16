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
        printf("Erro ao reservar memoria.\n");
        return 1;
    }
    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        opcao = ler_inteiro();

        switch (opcao) {
            case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
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