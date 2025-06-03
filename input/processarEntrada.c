#include "processarEntrada.h"
#include "raylib.h"
#include "external/miniaudio.h"
#include "../nucleo/definicoes.h"


void processarEntrada(Jogo *jogo) {
    switch (jogo->estado) {
        case JOGANDO:
            if (IsKeyPressed(KEY_LEFT)) {moveJogador(&jogo->jogador, &jogo->mapa, -1, 0); jogo->jogador.dir = ESQUERDA;}
            if (IsKeyPressed(KEY_RIGHT)) {moveJogador(&jogo->jogador, &jogo->mapa, 1, 0); jogo->jogador.dir = DIREITA;}
            if (IsKeyPressed(KEY_UP)) {moveJogador(&jogo->jogador, &jogo->mapa, 0, -1); jogo->jogador.dir = CIMA;}
            if (IsKeyPressed(KEY_DOWN)) {moveJogador(&jogo->jogador, &jogo->mapa, 0, 1); jogo->jogador.dir = BAIXO;}
            break;

        case MENU:
            if (IsKeyPressed(KEY_DOWN))
                if (jogo->seletorMenu < 3)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP))
                if (jogo->seletorMenu > 0)
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

int PosicaoValida(Mapa* mapa, int x, int y) { //Se a posição for inválida returna 0, se for válida, retorna 1.
    if ((x < 0 || x > 24) || (y < 0 || y > 16))
        return 0;
    if (mapa->mapa[y][x] == 'P')
        return 0;
    return 1;
}

