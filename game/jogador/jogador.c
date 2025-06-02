//
// Created by lucas on 02/06/2025.
//

#include "jogador.h"

#include "processarEntrada.h"
#include "../nucleo/definicoes.h"
#include "raylib.h"

void moveJogador(Jogador* jogador, Mapa* mapa, int direcaoX, int direcaoY) {
    int proximaPosicaoX = jogador->pos.x + direcaoX;
    int proximaPosicaoY = jogador->pos.y + direcaoY;

    if (PosicaoValida(mapa, proximaPosicaoX, proximaPosicaoY)) { //Testa a colisão
        jogador->pos.x = proximaPosicaoX;
        jogador->pos.y = proximaPosicaoY;
    }
}

void pegaEspada(Jogador* jogador, Mapa* mapa) {
    if (jogador->pos.x == mapa->posInicialEspada.x && jogador->pos.y == mapa->posInicialEspada.y) {
        jogador->temEspada = 1;
        mapa->espadaPegada = 1;

    }
}

void pegaVida(Jogador* jogador, Mapa* mapa) {
    for (int i = 0; i < 5; i++) {
        if (mapa->vidasPegadas[i] == 0 && jogador->pos.x == mapa->vidasExtras[i].x && jogador->pos.y == mapa->vidasExtras[i].y) {
            jogador->vidas += 1;
            mapa->vidasPegadas[i] = 1;
        }
    }
}

