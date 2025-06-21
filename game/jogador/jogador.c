//
// Created by lucas on 02/06/2025.
//

#include "jogador.h"

#include "processarEntrada.h"
#include "../nucleo/definicoes.h"
#include "raylib.h"
#include <stdio.h>

void moveJogador(Jogador* jogador, Mapa* mapa, int direcaoX, int direcaoY) {
    if (jogador->estaSeMovendo) // Só permite um novo movimento se o jogador não estiver se movendo
        return;                        // Retorna, caso já esteja

        int proximaPosicaoX = jogador->pos.x + direcaoX;
        int proximaPosicaoY = jogador->pos.y + direcaoY;

        if (PosicaoValida(mapa, proximaPosicaoX, proximaPosicaoY)) { //Testa a colisão
            // Começa a animação
            jogador->estaSeMovendo = true;                // 1. Marca que está em movimento
            jogador->posOrigem = jogador->pos;            // 2. Guarda de onde saiu
            jogador->posDestino.x = proximaPosicaoX;      // 3. Define para onde vai
            jogador->posDestino.y = proximaPosicaoY;
            jogador->progressoMovimento = 0.0f;           // 4. Zera o timer da animação
        }
    }

void atualizarAnimacaoJogador(Jogador* jogador, float deltaTime) {
    // Se o jogador não está se movendo, não há nada a fazer
    if (!jogador->estaSeMovendo) {
        return;
    }

    // Incrementa o progresso da animação com o tempo que passou
    jogador->progressoMovimento += deltaTime;

    // Calcula qual frame do sprite deve ser mostrado a partir do progresso
    float percentualProgresso = jogador->progressoMovimento / DURACAO_MOVIMENTO;
    jogador->frameAtual = (int)(percentualProgresso * JOGADOR_NUM_FRAMES) % JOGADOR_NUM_FRAMES;

    // Verifica se a animação terminou
    if (jogador->progressoMovimento >= DURACAO_MOVIMENTO) {
        jogador->estaSeMovendo = false;       // Marca que parou de se mover
        jogador->pos = jogador->posDestino; // "Trava" a posição lógica na casa de destino
        jogador->frameAtual = 0; // Volta para o frame de "parado"
    }



}

void pegaEspada(Jogador* jogador, Mapa* mapa) {
    if (jogador->pos.x == mapa->posInicialEspada.x && jogador->pos.y == mapa->posInicialEspada.y) {
        jogador->temEspada = true;
        mapa->espadaPegada = 1;

    }
}

void pegaVida(Jogador* jogador, Mapa* mapa) {
    for (int i = 0; i < mapa->numVidasExtras; i++) {
        if (mapa->vidasPegadas[i] == 0 && jogador->pos.x == mapa->vidasExtras[i].x && jogador->pos.y == mapa->vidasExtras[i].y) {
            jogador->vidas += 1;
            mapa->vidasPegadas[i] = 1;
        }
    }
}

void danoJogador(Jogador* jogador, Monstro monstro[]) {
    int numMonstro = 10; // TEMPORÁRIO

    if (jogador->instantesInvencibilidade > 0)
        return;

    for (int i = 0; i < numMonstro; ++i) {
            if (monstro[i].vivo == 1 && (jogador->pos.x == monstro[i].pos.x && jogador->pos.y == monstro[i].pos.y)) {
                --jogador->vidas;
                jogador->instantesInvencibilidade = 1.5f;
                break;
            }
    }
}
