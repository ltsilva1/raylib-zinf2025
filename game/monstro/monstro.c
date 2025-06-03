//
// Created by Panerai on 30/05/2025.
//
#include <time.h>
#include <stdlib.h>

#include "../game/monstro/monstro.h"
#include "../../nucleo/definicoes.h"
#include "../../input/processarEntrada.h"

void moveMonstro(Monstro monstro[], int qtd_monstros, Mapa* mapa) {
    for (int i = 0; i < qtd_monstros; i++) {
        int novaDirRand = rand() % 4; // 0:N, 1:S, 2:L, 3:O
        int deltaX = 0, deltaY = 0;

        switch (novaDirRand) {
            case 0: deltaY = -1; monstro[i].dir = CIMA; break;
            case 1: deltaY = 1; monstro[i].dir = BAIXO; break;
            case 2: deltaX = 1; monstro[i].dir = DIREITA; break;
            case 3: deltaX = -1; monstro[i].dir = ESQUERDA; break;
        }

        int proximoX = monstro[i].pos.x + deltaX;
        int proximoY = monstro[i].pos.y + deltaY;

        if (PosicaoValida(mapa, proximoX, proximoY)) { //Testa a colisão
            monstro[i].pos.x = proximoX;
            monstro[i].pos.y = proximoY;
        }



    }


}