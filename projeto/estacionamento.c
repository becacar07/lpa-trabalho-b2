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