//
// Created by Panerai on 30/05/2025.
//
#include <time.h>
#include <stdlib.h>

#include "../game/monstro/monstro.h"
#include "../../nucleo/definicoes.h"
#include "../../input/processarEntrada.h"

void moveMonstro(Jogador* jogador, Monstro monstro[], int qtd_monstros, Mapa* mapa) {
    for (int i = 0; i < qtd_monstros; i++) {
        //int novaDirRand = rand() % 4; // 0:N, 1:S, 2:L, 3:O
        int movimentaOuNao = rand() % 50;

        int diffX = jogador->pos.x - monstro[i].pos.x;
        int diffY = jogador->pos.y - monstro[i].pos.y;

        int passoX = 0;
        if (diffX > 0) passoX = 1;
        else if (diffX < 0) passoX = -1;

        int passoY = 0;
        if (diffY > 0) passoY = 1;
        else if (diffY < 0) passoY = -1;

        int ProximoX = monstro[i].pos.x + passoX;
        int ProximoY = monstro[i].pos.y + passoY;

        if (PosicaoValida(mapa, ProximoX, ProximoY)) { //Testa a colisão
            monstro[i].pos.x = ProximoX;
            monstro[i].pos.y = ProximoY;
        }
    }
}