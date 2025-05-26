#include "desenha_prot.h"
#include "raylib.h"
#include "definicoes.h"

void desenhaJogo(Jogo* meuJogo) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            switch (meuJogo->mapa.mapa[i][j]) {
                    case 'P':
                    DrawRectangle(j * CASA, i * CASA, CASA, CASA, DARKBROWN);
                    break;

                    case 'V':
                    DrawRectangle(j * CASA, i * CASA, CASA, CASA, PINK);
                    break;

                    case 'E':
                    DrawRectangle(j * CASA, i * CASA, CASA, CASA, GRAY);
                    break;

                    case 'M':
                    DrawRectangle(j * CASA, i * CASA, CASA, CASA, RED);
                    break;

                    //case ' ':
                    //DrawRectangle(j * CASA, i * CASA, CASA, CASA, BLACK);
                    //break;
            }
        }
    }
    DrawRectangle(meuJogo->jogador.pos.y * CASA, meuJogo->jogador.pos.x * CASA, CASA, CASA, GREEN);
}


