#include "processarEntrada.h"
#include "raylib.h"
#include "external/miniaudio.h"
#include "../nucleo/definicoes.h"


void processarEntrada(Jogo *jogo) {
    if (IsKeyPressed(KEY_P)) { // Ativa ou desativa o modo de depuração
        if (jogo->modoDebug == false) {
            jogo->modoDebug = true;
        } else {jogo->modoDebug = false;}
    }

    switch (jogo->estado) {
        case JOGANDO:
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {moveJogador(&jogo->jogador, &jogo->mapa, -1, 0); jogo->jogador.dir = ESQUERDA;}
            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {moveJogador(&jogo->jogador, &jogo->mapa, 1, 0); jogo->jogador.dir = DIREITA;}
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {moveJogador(&jogo->jogador, &jogo->mapa, 0, -1); jogo->jogador.dir = CIMA;}
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {moveJogador(&jogo->jogador, &jogo->mapa, 0, 1); jogo->jogador.dir = BAIXO;}
            if (IsKeyPressed(KEY_J)) {jogo->jogador.instantesEspada = 0.5f;}
            if (IsKeyPressed(KEY_ENTER)) {jogo->estado = PAUSADO;}
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
            break;

        case FIM_DE_JOGO:
            if (IsKeyPressed(KEY_DOWN))
                if (jogo->seletorMenu < 2)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP))
                if (jogo->seletorMenu > 0)
                    jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) {
                switch (jogo->seletorMenu) {
                    case 0:
                        // Carregar jogo
                        break;
                    case 1:
                        jogo->estado = JOGANDO;
                        jogo->seletorMenu = 0;
                        break;
                    case 2:
                        jogo->estado = MENU;
                        jogo->seletorMenu = 0;
                        break;
                }
            }
        case PAUSADO:
            if (IsKeyPressed(KEY_ENTER)) {jogo->estado = JOGANDO;}
            break;
    }
}

int PosicaoValida(Mapa* mapa, int x, int y) { //Se a posição for inválida returna 0, se for válida, retorna 1.
    if ((x < 0 || x > 24) || (y < 0 || y > 16))
        return 0;
    if (mapa->mapa[y][x] == 'P')
        return 0;
    return 1;
}

