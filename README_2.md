# Sistema de Gestão de Estacionamento

**Disciplina:** Lógica de Programação e Algoritmos — 2026/2
**Trabalho:** Trabalho do 2º Bimestre (B2)

| Integrante | GitHub |
|---|---|
| Rebeca Carvalho Santana Pires | [@becacar07](https://github.com/becacar07) |
| Vinícius Monteiro de Moraes | [@vinimonteuro](https://github.com/vinimonteuro) |

## Cenário e escopo

Programa de terminal em C11 que controla um estacionamento fictício com 4 fileiras e 5 colunas (20 vagas). O programa começa vazio, recebe as operações pelo menu e guarda os dados só enquanto está aberto (não há gravação em arquivo). Os identificadores e descrições usados nos testes são fictícios.

## Funcionalidades (menu)

```
1 - Cadastrar veículo
2 - Consultar veículo por identificador
3 - Atualizar descrição ou categoria
4 - Mover veículo para outra vaga
5 - Remover veículo
6 - Listar veículos cadastrados
7 - Exibir mapa de vagas
8 - Exibir relatório da ocupação
0 - Encerrar (libera a memória)
```

## Estruturas utilizadas

- **Matriz `int vagas[4][5]`** (criada no `main`): `0` = vaga livre e `1` = vaga ocupada. O usuário digita fileira de 1 a 4 e coluna de 1 a 5; dentro do programa usamos `fileira - 1` e `coluna - 1`. A posição é conferida com `posicao_valida()` antes de qualquer acesso à matriz.
- **`struct Veiculo`**: `identificador[8]` (7 caracteres + `'\0'`), `descricao[61]` (até 60 caracteres + `'\0'`), `categoria` (1 = carro, 2 = moto), `fileira` e `coluna`.
- **`struct Colecao`**: vetor dinâmico de `Veiculo` com `quantidade` (veículos cadastrados) e `capacidade` (espaço reservado na memória). Começa com capacidade 2 usando `malloc` e dobra com `realloc` quando enche (2 → 4 → 8 → 16 → 32). O resultado do `realloc` fica num ponteiro auxiliar e só substitui o original se não for `NULL`. Ao escolher 0, a memória é liberada com `free`.
- **Consistência:** a quantidade de veículos na lista é sempre igual ao número de vagas com 1 na matriz. O relatório (opção 8) mostra essa conferência.

## Modularização

| Arquivo | Funções |
|---|---|
| `projeto/estacionamento.h` | Constantes, `struct Veiculo`, `struct Colecao`, `enum ResultadoInsercao` e os protótipos |
| `projeto/estacionamento.c` | Validações (`normalizar_identificador`, `descricao_valida`, `categoria_valida`, `posicao_valida`), coleção dinâmica (`inicializar_colecao`, `ampliar_colecao`, `liberar_colecao`), `buscar_veiculo`, `inserir_veiculo`, `exibir_veiculo`, `listar_veiculos`, `mover_veiculo`, `remover_veiculo`, `zerar_mapa`, `exibir_vagas`, `contar_vagas_ocupadas`, `exibir_relatorio` |
| `projeto/main.c` | Leitura das entradas com `fgets` (`ler_texto`, `ler_inteiro`), menu (`exibir_menu`) e uma função para cada opção: `cadastrar_veiculo`, `consultar_veiculo`, `atualizar_veiculo`, `trocar_vaga`, `retirar_veiculo` (todas usam `procurar_veiculo` para achar o veículo pelo identificador) |

## Compilação e execução

Na pasta raiz do repositório:

```bash
gcc -std=c11 -Wall -Wextra -pedantic projeto/main.c projeto/estacionamento.c -o estacionamento
./estacionamento          # Linux / Codespaces
estacionamento.exe        # Windows (cmd)
```

### Testes com entrada pronta

A pasta `testes/` tem arquivos com as respostas digitadas em ordem, uma por linha:

```bash
./estacionamento < testes/cenario_7_1.txt    # cenário completo da seção 7.1 do roteiro
./estacionamento < testes/t09_lotacao.txt    # 20 cadastros + 21ª tentativa
```

No Windows (cmd): `estacionamento.exe < testes\cenario_7_1.txt`

## Casos de teste

| Teste | Entrada / operação | Resultado esperado | Resultado observado | Situação |
|---|---|---|---|---|
| T01 – Estacionamento vazio | Início → opções 7, 8 e 6 | Mapa todo livre, 0,00%, lista vazia | Mapa só com `.`, "Ocupação: 0.00%", "Nenhum veículo cadastrado." | Aprovado |
| T02 – Cadastro válido | 1: ABC1D23, "Carro azul", 1, fileira 1, coluna 1 → opções 2 e 6 | Aparece na consulta e na listagem; F1/C1 ocupada | "Veículo ABC1D23 cadastrado na vaga F1/C1."; consulta e listagem mostram o veículo | Aprovado |
| T03 – Duplicidade sem distinção de maiúsculas | 1: abc1d23 com ABC1D23 já cadastrado | Cadastro recusado | "Já existe um veículo com o identificador ABC1D23." | Aprovado |
| T04 – Vaga ocupada / posição inválida | 1 em F1/C1 já ocupada; 1 com fileira 5 | Recusa sem alterar nada | "A vaga F1/C1 já está ocupada!" / "Posição inválida!"; relatório continua com 1 vaga ocupada | Aprovado |
| T05 – Crescimento dinâmico | 3º cadastro (LPA2026, F4/C5) | Capacidade passa de 2 para 4 | "Capacidade da lista aumentou de 2 para 4." | Aprovado |
| T06 – Atualização | 3: ABC1D23 → "Moto vermelha", categoria 2 | Dados mudam sem criar outro registro | Listagem continua com 1 veículo, com os dados novos | Aprovado |
| T07 – Movimentação | 4: ABC1D23 → F1/C2 (ocupada) e depois → F2/C3 | 1ª recusada; na 2ª, F1/C1 fica livre e F2/C3 ocupada | "A vaga F1/C2 está ocupada!" e depois "movido para a vaga F2/C3"; o mapa confere | Aprovado |
| T08 – Remoção | 5: xyz9k87 | Some da lista e a vaga é liberada | "Veículo XYZ9K87 removido."; listagem sem ele; mapa com F1/C2 livre | Aprovado |
| T09 – Lotação | `testes/t09_lotacao.txt` | 21ª inclusão recusada | "Estacionamento lotado! Cadastro recusado."; "Ocupação: 100.00%" | Aprovado |
| T10 – Encerramento | 0 | Memória da coleção liberada | "Memória liberada. Até mais!"; Valgrind: "All heap blocks were freed" | Aprovado |

O cenário completo da seção 7.1 (`testes/cenario_7_1.txt`) termina com: 20 vagas, 2 ocupadas, 18 livres, 10,00%, 2 carros, 0 motos — igual à tabela do roteiro.

## Responsabilidades

- **Vinícius (@vinimonteuro):** constantes e `struct`s, coleção dinâmica (`malloc`, `realloc` e `free`), validações de identificador, descrição e categoria, busca e inserção de veículos, primeira versão da exibição da matriz.
- **Rebeca (@becacar07):** menu e leitura das entradas com `fgets`, cadastro pelo menu, consulta, listagem, atualização, movimentação, remoção, mapa com legenda, relatório com conferência de consistência, `.gitignore`, arquivos de teste e README.

## Integração das branches

- Os primeiros commits (struct, coleção dinâmica, validações, busca e inserção) foram feitos direto na `main`.
- `feature/menu-cadastro` → PR #1: correção do include, `.gitignore`, menu com leitura segura, correção da leitura de opção (`1abc`) e cadastro.
- `feature/operacoes-veiculo` → PR #2: consulta, listagem, atualização, movimentação e remoção.
- `feature/mapa-relatorio` → PR #3: mapa com legenda, relatório e ligação do relatório à opção 8 (o primeiro commit do relatório entrou sem o `.h` e o `main.c`; foi completado num commit seguinte antes do merge).
- `docs/readme-testes` → PR #4: README e arquivos de teste.
- Não houve conflitos de merge. Antes de cada nova branch, a `main` era atualizada com `git pull`.

## Limitações conhecidas

- O limite de 60 caracteres da descrição é contado em bytes (`strlen`); letras com acento ocupam 2 bytes.
- Na atualização, Enter vazio mantém a descrição atual e 0 mantém a categoria atual.
- Com o estacionamento lotado, o cadastro é recusado antes de pedir os dados.

## Declarações individuais de autoria e uso de IA

### Rebeca (@becacar07)

- **(a) Funcionalidades em que atuei:** menu e leitura das entradas, cadastro pelo menu, consulta, listagem, atualização, movimentação, remoção, mapa, relatório, `.gitignore`, testes e README; também corrigi o include de `stdio.h` no arquivo do parceiro.
- **(b) Usei IA generativa?** Sim.
- **(c) Ferramentas, para quê e sugestões incorporadas:**
  - **Ferramenta:** Claude (Anthropic), usado como tutor e revisor de código durante o desenvolvimento das minhas partes. O código foi escrito por mim e testado no meu ambiente; a IA explicou conceitos, revisou trechos que eu enviei e sugeriu correções, compilando e testando alguns desses trechos para conferir.
  - **`.gitignore`:** pedi ajuda para ignorar o conteúdo de `projeto/output/` mantendo a pasta no repositório. Incorporei a sugestão de usar um `.gitignore` dentro da pasta (`*` e `!.gitignore`) e de tirar o `main.exe` do índice com `git rm --cached`.
  - **Leitura com `fgets`:** perguntei como ler a descrição sem `gets` e como tirar o `\n` do final. A IA explicou a troca do `\n` por `'\0'`, a limpeza do buffer quando o texto passa do tamanho e o `\n` que o `scanf` deixa para trás. Usei isso na `ler_texto`.
  - **Leitura da opção do menu:** perguntei por que o menu entrava em loop ao digitar uma letra. A IA explicou que o `scanf("%d")` falha e não consome a letra, e sugeriu ler a linha com `fgets` e converter com `sscanf(linha, "%d %c", ...)`, para recusar letras e entradas como `1abc`. Incorporei na `ler_inteiro`.
  - **Revisão do menu:** a IA apontou o bug `while (opcao = 0)` (atribuição no lugar de comparação, que encerrava o menu na primeira volta) e a falta do `#include <stdio.h>` no `estacionamento.c`. Corrigi os dois.
  - **Revisão do cadastro:** a IA testou a `cadastrar_veiculo` com entradas válidas e inválidas e apontou que faltava o protótipo de `posicao_valida` no `.h`. Adicionei.
  - **Movimentação e remoção:** pedi só a explicação teórica. A IA explicou que mapa e veículo precisam ser atualizados juntos, que a posição antiga deve ser guardada antes de alterar o registro, o deslocamento dos itens para remover do meio do vetor sem deixar buraco e a diferença entre remoção lógica (`quantidade--`) e liberação do bloco (`free` só no final). Escrevi as funções com base nessa explicação.
  - **README:** usei a IA para deixar o README completo e o mais formal possível.
- **(d) Adaptação de código externo:** não adaptei código de outras fontes além das sugestões das ferramentas acima. Consultei a documentação de `fgets`, `sscanf` e `realloc` (cppreference.com).

### Vinícius (@vinimonteuro)

- **(a) Funcionalidades em que atuei:** 
Definição das constantes e estruturas (structs) utilizadas no projeto.
Implementação da coleção dinâmica de veículos, utilizando malloc, realloc e free.
Implementação das validações de identificador, descrição e categoria dos veículos.
Desenvolvimento das funcionalidades de busca e inserção de veículos.
Desenvolvimento da primeira versão da exibição da matriz de vagas no terminal.

- **(b) Usei IA generativa?** 
Sim.

- **(c) Ferramentas, para quê e sugestões incorporadas:**
Utilizei o ChatGPT para compreender o funcionamento de determinadas funções e conceitos, principalmente relacionados à alocação e realocação dinâmica de memória, como malloc e realloc.
Durante as interações, o ChatGPT apresentava pequenos exemplos de código que serviam como referência para compreender a lógica de implementação. A partir desses exemplos, eu adaptava algumas ideias ao meu próprio código.
Além disso, utilizei o ChatGPT como apoio para estruturar e organizar o README, auxiliando na elaboração e organização das informações sobre o projeto e as responsabilidades individuais.
- **(d) Adaptação de código externo:**
Não utilizei trechos de código provenientes de sites, vídeos, livros ou repositórios externos. Os códigos foram desenvolvidos por mim, com auxílio pontual do ChatGPT para esclarecimento de dúvidas e compreensão de conceitos.
