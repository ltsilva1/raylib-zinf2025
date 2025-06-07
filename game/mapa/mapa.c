#include <stdio.h>
#include <stdlib.h>

#include "../../nucleo/definicoes.h"

int carregaMapa (Jogo* meuJogo) {
    FILE* f;
    char nomeArquivo[20];
    sprintf(nomeArquivo, "mapa%02d.txt", meuJogo->nivelAtual);

    f = fopen(nomeArquivo, "r");
    if (f == NULL) {
        return 0;
    }

    for (int i = 0; i < 16; i++) {
        fgets(meuJogo->mapa.mapa[i], 24+2, f);  // lê até 24 caracteres + '\n' + '\0'
    }
    fclose(f);

    //Testa processamento do mapa
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            char c = meuJogo->mapa.mapa[i][j];
            if (c == '\n' || c == '\0')
                break;
            printf("%c", c);
        }
        printf("\n");
    }


    // Repassa a localização dos monstros no mapa para a estrutura do jogo
    meuJogo->mapa.numMonstros = 0;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'M') {
                if (meuJogo->mapa.numMonstros<10) {
                    meuJogo->mapa.monstro[meuJogo->mapa.numMonstros].pos.x = j;
                    meuJogo->mapa.monstro[meuJogo->mapa.numMonstros].pos.y = i;
                    meuJogo->mapa.numMonstros++;
                    meuJogo->mapa.mapa[i][j] = ' ';
                }
            }
        }
    }

    // Repassa a localização do jogador no mapa para a estrutura do jogo
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'J') {
                meuJogo->mapa.posInicialJogador.x = j;
                meuJogo->mapa.posInicialJogador.y = i;
            }
        }
    }

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

    // Repassa a localização das vidas extras no mapa para a estrutura do jogo
    int contaVidasExtras = 0;
    for (int i = 0; i < 5; ++i)
        meuJogo->mapa.vidasPegadas[i] = 0;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'V') {
                if (contaVidasExtras<5) {
                    meuJogo->mapa.vidasExtras[contaVidasExtras].x = j;
                    meuJogo->mapa.vidasExtras[contaVidasExtras].y = i;
                    contaVidasExtras++;
                    meuJogo->mapa.mapa[i][j] = ' ';
                }
            }
        }
    }
    return 1;
}