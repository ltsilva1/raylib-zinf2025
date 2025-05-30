//
// Created by lucas on 26/05/2025.
//

#include "processarEntrada.h"

#include "raylib.h"
#include "external/miniaudio.h"

void moveJogador(Jogador* jogador, Mapa* mapa, int direcaoX, int direcaoY);
int PosicaoValida(Mapa* mapa, int x, int y);

void processarEntrada(Jogo *jogo) {
    switch (jogo->estado) {
        case JOGANDO:
            if (IsKeyPressed(KEY_LEFT)) {moveJogador(&jogo->jogador, &jogo->mapa, -1, 0);}
            if (IsKeyPressed(KEY_RIGHT)) {moveJogador(&jogo->jogador, &jogo->mapa, 1, 0);}
            if (IsKeyPressed(KEY_UP)) {moveJogador(&jogo->jogador, &jogo->mapa, 0, -1);}
            if (IsKeyPressed(KEY_DOWN)) {moveJogador(&jogo->jogador, &jogo->mapa, 0, 1);}
            break;

        case MENU:
            if (IsKeyPressed(KEY_DOWN))
                jogo->seletorMenu += 1;

            if (IsKeyPressed(KEY_UP))
                jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) {
                switch (jogo->seletorMenu) {
                    case 0:
                        jogo->estado = JOGANDO;
                        break;
                    case 1:
                        //Carregar jogo
                        break;
                    case 2:
                        //Carregar scoreboard
                        break;
                    case 3:
                        CloseWindow();
                        break;
                }
            }
    }
}
void moveJogador(Jogador* jogador, Mapa* mapa, int direcaoX, int direcaoY) {
    int proximaPosicaoX = jogador->pos.x + direcaoX;
    int proximaPosicaoY = jogador->pos.y + direcaoY;

    if (PosicaoValida(mapa, proximaPosicaoX, proximaPosicaoY)) { //Testa a colisão
        jogador->pos.x = proximaPosicaoX;
        jogador->pos.y = proximaPosicaoY;
    }

}

int PosicaoValida(Mapa* mapa, int x, int y) { //Se a posição for inválida returna 0, se for válida, retorna 1.
    if ((x < 0 || x > 24) || (y < 0 || y > 16))
        return 0;
    if (mapa->mapa[y][x] == 'P')
        return 0;
    return 1;
}

