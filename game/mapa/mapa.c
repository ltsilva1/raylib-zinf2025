#include <stdio.h>
#include <stdlib.h>

#include "../../nucleo/definicoes.h"

int carregaMapa (Jogo* meuJogo) {
    FILE* f;
    char nomeArquivo[20];
    sprintf(nomeArquivo, "mapa%02d.txt", meuJogo->nivelAtual); // Define o arquivo alvo a ser carregado

    f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        return 0;
    }

    for (int i = 0; i < 16; i++) { // Loop para as 16 linhas
        for (int j = 0; j < 24; j++) { // Loop para as 24 colunas
            char caractereConsumido;

            do {
                caractereConsumido = fgetc(f); // Pega o caractere atual, testa e sai do loop se for válido
            } while (caractereConsumido == '\n');

            meuJogo->mapa.mapa[i][j] = caractereConsumido; // Armazena o caractere válido matriz do mapa
        }
    }

    fclose(f); // Fecha o arquivo após copiar seu conteúdo para a matriz

    // Decide quais texturas serão utilizadas para as paredes e chão
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            meuJogo->mapa.chaoVariacao[i][j] = rand() % 2; // Salva 0 ou 1 (chão com ou sem mato)
            meuJogo->mapa.paredeVariacao[i][j] = rand() % 2; // Salva 0 ou 1 (parede com arbusto verde ou amarelo)
        }
    }

     /* =============== MONSTROS =============== */
    meuJogo->mapa.numMonstrosInicial = 0;

    // Repassa a localização dos monstros no mapa para a estrutura do jogo
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'M') {
                if (meuJogo->mapa.numMonstrosInicial<10) {
                    meuJogo->mapa.monstro[meuJogo->mapa.numMonstrosInicial].pos.x = j;
                    meuJogo->mapa.monstro[meuJogo->mapa.numMonstrosInicial].pos.y = i;
                    meuJogo->mapa.numMonstrosInicial++;
                    meuJogo->mapa.mapa[i][j] = ' '; // Remove o monstro da matriz para evitar possíveis duplicações (precaução)
                }
            }
        }
    }

    meuJogo->mapa.numMonstros = meuJogo->mapa.numMonstrosInicial;

    /* =============== JOGADOR =============== */
    // Repassa a localização do jogador no mapa para a estrutura do jogo
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'J') {
                meuJogo->mapa.posInicialJogador.x = j;
                meuJogo->mapa.posInicialJogador.y = i;
            }
        }
    }

    /* =============== ESPADA =============== */
    meuJogo->mapa.espadaPegada = 0;

    // Repassa a localização da espada no mapa para a estrutura do jogo
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'E') {
                meuJogo->mapa.posInicialEspada.x = j;
                meuJogo->mapa.posInicialEspada.y = i;
            }
        }
    }

    /* =============== VIDAS EXTRAS =============== */
    int contaVidasExtras = 0;

    for (int i = 0; i < 5; ++i)
        meuJogo->mapa.vidasPegadas[i] = 0;

    // Repassa a localização das vidas extras no mapa para a estrutura do jogo
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'V') {
                if (contaVidasExtras<5) {
                    meuJogo->mapa.vidasExtras[contaVidasExtras].x = j;
                    meuJogo->mapa.vidasExtras[contaVidasExtras].y = i;
                    contaVidasExtras++;
                    meuJogo->mapa.mapa[i][j] = ' '; // Remove a vida extra da matriz para evitar possíveis duplicações (precaução)
                }
            }
        }
    }

    meuJogo->mapa.numVidasExtras = contaVidasExtras;
    /* ============================================ */

    return 1;
}