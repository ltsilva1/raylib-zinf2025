#include <stdio.h>
#include <stdlib.h>

#include "../../nucleo/definicoes.h"

void carregaMapa (Jogo* meuJogo) {
    FILE* f;

    f = fopen("mapa01.txt", "r");
    if (f == NULL) {
        exit(1);
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
    int contaMonstro = 0;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'M') {
                if (contaMonstro<10) {
                    meuJogo->monstro[contaMonstro].pos.x = j;
                    meuJogo->monstro[contaMonstro].pos.y = i;
                    contaMonstro++;
                    meuJogo->mapa.mapa[i][j] = ' ';
                }
            }
        }
    }

    // Repassa a localização do jogador no mapa para a estrutura do jogo
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (meuJogo->mapa.mapa[i][j] == 'J') {
                meuJogo->jogador.pos.x = j;
                meuJogo->jogador.pos.y = i;
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

}