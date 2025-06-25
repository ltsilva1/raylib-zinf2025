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
        return;                 // Retorna, caso já esteja

        int proximaPosicaoX = jogador->pos.x + direcaoX;
        int proximaPosicaoY = jogador->pos.y + direcaoY;

        if (PosicaoValida(mapa, proximaPosicaoX, proximaPosicaoY)) { // Começa a animação
            jogador->estaSeMovendo = true;                           // Marca que está em movimento
            jogador->posOrigem = jogador->pos;                       // Guarda de onde saiu
            jogador->posDestino.x = proximaPosicaoX;                 // Define para onde vai em x
            jogador->posDestino.y = proximaPosicaoY;                 // Define para onde vai em y
            jogador->progressoMovimento = 0.0f;                      // Zera o timer da animação
        }
    }

void atualizarAnimacaoJogador(Jogador* jogador, float deltaTime) {
    if (!jogador->estaSeMovendo) { // Se o jogador não está se movendo, não faz nada
        return;
    }

    // Incrementa o progresso da animação com o tempo que passou
    jogador->progressoMovimento += deltaTime;

    // Calcula qual frame do sprite deve ser mostrado a partir do progresso
    float percentualProgresso = jogador->progressoMovimento / DURACAO_MOVIMENTO;
    jogador->frameAtual = (int)(percentualProgresso * JOGADOR_NUM_FRAMES) % JOGADOR_NUM_FRAMES;

    // Parada da animação
    if (jogador->progressoMovimento >= DURACAO_MOVIMENTO) { // (Maior igual por conta da imprecisão do float)
        jogador->estaSeMovendo = false;       // Marca que parou de se mover
        jogador->pos = jogador->posDestino;   // "Trava" a posição lógica na casa de destino
        jogador->frameAtual = 0;              // Volta para o frame de "parado"
    }

}

void pegaEspada(Jogador* jogador, Mapa* mapa) { // Pega a espada e tira do mapa
    if (jogador->pos.x == mapa->posInicialEspada.x && jogador->pos.y == mapa->posInicialEspada.y) {
        jogador->temEspada = true;
        mapa->espadaPegada = true;

    }
}

void pegaVida(Jogador* jogador, Mapa* mapa) { // Pega a vida e tira do mapa
    for (int i = 0; i < mapa->numVidasExtras; i++) { // Loop até a quantidade de vidas no mapa
        if (mapa->vidasPegadas[i] == 0 && jogador->pos.x == mapa->vidasExtras[i].x && jogador->pos.y == mapa->vidasExtras[i].y) {
            jogador->vidas += 1;
            mapa->vidasPegadas[i] = 1; // 1 = Vida pegada; 2 = Vida no chão
        }
    }
}

void danoJogador(Jogador* jogador, Monstro monstro[]) {
    int numMonstroMax = 10; // Não pega lixo de memória, pois os monstros que não serão utilizados já foram limpos

    if (jogador->instantesInvencibilidade > 0)
        return;

    for (int i = 0; i < numMonstroMax; ++i) {
            if (monstro[i].vivo == 1 && (jogador->pos.x == monstro[i].pos.x && jogador->pos.y == monstro[i].pos.y)) {
                --jogador->vidas;
                jogador->instantesInvencibilidade = 1.5f; // Deixa o jogador invencível por um curto período ao tomar dano
                break;
            }
    }
}
