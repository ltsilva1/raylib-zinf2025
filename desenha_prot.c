#include "desenha_prot.h"
#include "raylib.h"
#include "definicoes.h"
#include "ui.h"


void desenhaJogo(Jogo* meuJogo) {
    switch (meuJogo->estado) {
        case JOGANDO:
            ClearBackground(RAYWHITE);
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
        DrawRectangle(meuJogo->jogador.pos.x * CASA, meuJogo->jogador.pos.y * CASA, CASA, CASA, GREEN);
        //for (int i = 0; i < 10; i++)
        //DrawRectangle(meuJogo->monstro[i].pos.x * CASA, meuJogo->monstro[i].pos.y * CASA, CASA, CASA, RED);
        //DrawRectangle( 0, 0, 100, 100, RED
            break;
        case MENU:
            DesenhaMenuPrincipal(meuJogo);
            break;

    }
}


