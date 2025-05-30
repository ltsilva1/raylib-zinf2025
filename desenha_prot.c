#include "desenha_prot.h"
#include "raylib.h"
#include "definicoes.h"

void desenhaJogo(Jogo* meuJogo) {
    BeginDrawing(); //Inicia o ambiente de desenho na tela
    ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
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
    //DrawRectangle(meuJogo->monstro[0].pos.x * CASA, meuJogo->monstro[0].pos.y * CASA, CASA, CASA, RED);
    EndDrawing(); //Finaliza o ambiente de desenho na tela
    //DrawRectangle( 0, 0, 100, 100, RED
}


