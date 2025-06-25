//
// Created by Panerai on 30/05/2025.
//
#include <time.h>
#include <stdlib.h>

#include "../game/monstro/monstro.h"
#include "../../nucleo/definicoes.h"
#include "../../input/processarEntrada.h"

void moveMonstro(Monstro monstro[], int qtd_monstros, Mapa* mapa, float deltaTime) {
    const float intervaloMovimento = 0.3f;

    for (int i = 0; i < qtd_monstros; i++) {
        if (monstro[i].vivo == 0) {
            continue; // Pula monstros mortos
        }

        monstro[i].tempoParaMover -= deltaTime; // Subtrai um pequeno pedaço do temporizador de cada monstro

        // Esse if faz com que o monstro se se mova quando o seu temporizador for igual a zero
        if (monstro[i].vivo == 1 && monstro[i].tempoParaMover <= 0.0f) {
            monstro[i].tempoParaMover = intervaloMovimento;// Reseta o temporizador para 0.3 segundos novamente
            int deltaY = 0, deltaX = 0;
            bool tentarMovimentarEsteTurno = false; // Flag para controlar se o movimento será tentado

            if (monstro[i].passosRestantes > 0) {
                // Monstro está continuando uma sequência de movimentos
                tentarMovimentarEsteTurno = true;
                switch (monstro[i].dir) {
                    case CIMA:
                        deltaY = -1;
                        break;
                    case BAIXO:
                        deltaY = 1;
                        break;
                    case DIREITA:
                        deltaX = 1;
                        break;
                    case ESQUERDA:
                        deltaX = -1;
                        break;
                }
            } else {
                // Caso o monstro não esteja em uma sequência, inicia uma nova
                    tentarMovimentarEsteTurno = true;
                    int novaDirRand = rand() % 4; // 0:N, 1:S, 2:L, 3:O
                    switch (novaDirRand) {
                        case 0:
                            deltaY = -1;
                            monstro[i].dir = CIMA;
                            break;
                        case 1:
                            deltaY = 1;
                            monstro[i].dir = BAIXO;
                            break;
                        case 2:
                            deltaX = 1;
                            monstro[i].dir = DIREITA;
                            break;
                        case 3:
                            deltaX = -1;
                            monstro[i].dir = ESQUERDA;
                            break;
                    }
                    monstro[i].passosRestantes = 3; // Inicia uma nova sequência de 3 passos
            }

            // Se o monstro deve tentar se mover (seja continuando ou começando uma nova sequência)
            if (tentarMovimentarEsteTurno ) {
                int proximoX = monstro[i].pos.x + deltaX;
                int proximoY = monstro[i].pos.y + deltaY;

                if (PosicaoValida(mapa, proximoX, proximoY)) {
                    monstro[i].pos.x = proximoX;
                    monstro[i].pos.y = proximoY;
                    monstro[i].passosRestantes--; // Só decrementa se o movimento foi bem-sucedido
                } else {
                    // Se a posição for inválida, zera os passos restantes para sortear uma nova direção
                    monstro[i].passosRestantes = 0;
                }
            }
            // Se tentarMovimentarEsteTurno for false, o monstro não faz nada neste turno e monstro[i].passosRestantes (que já seria <= 0) continua assim.
        }
    }
}

