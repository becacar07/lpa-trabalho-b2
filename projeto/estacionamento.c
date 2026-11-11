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