#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#define FILEIRAS 4
#define COLUNAS 5
#define TOTAL_VAGAS (FILEIRAS * COLUNAS)

#define VAGA_LIVRE 0
#define VAGA_OCUPADA 1

void exibir_vagas (int matriz [FILEIRAS][COLUNAS]);

#endif