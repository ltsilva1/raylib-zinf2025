//
// Created by Panerai on 30/05/2025.
//
#include <time.h>
#include <stdlib.h>

#include "../game/monstro/monstro.h"
#include "../../nucleo/definicoes.h"
#include "../../input/processarEntrada.h"

const PosicaoGrade vetoresDirecao[4] = {
    {0, -1}, // CIMA (x=0, y=-1)
    {0, 1},  // BAIXO (x=0, y=1)
    {1, 0},  // DIREITA (x=1, y=0)
    {-1, 0}  // ESQUERDA (x=-1, y=0)
};


void moveMonstro(Jogador* jogador, Monstro monstro[], int qtd_monstros, Mapa* mapa) {
    for (int i = 0; i < qtd_monstros; i++) {

        if (monstro[i].vivo == 1) {
            int deltaY = 0, deltaX = 0;
            bool tentarMovimentarEsteTurno = false; // Flag para controlar se o movimento será tentado

            if (monstro[i].passosRestantes > 0) {
                // monstro está continuando uma sequência de movimentos
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
                // caso o monstro nao esteja em uma sequencia, inicia uma nova
                int movimentaOuNao = rand() % 30;
                if (movimentaOuNao == 2) {
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
            }

            // Se o monstro deve tentar se mover (seja continuando ou começando uma nova sequência)
            int movimentaOuNao = rand() % 15;
            if (tentarMovimentarEsteTurno && movimentaOuNao == 5) {
                int proximoX = monstro[i].pos.x + deltaX;
                int proximoY = monstro[i].pos.y + deltaY;

                if (PosicaoValida(mapa, proximoX, proximoY)) {
                    monstro[i].pos.x = proximoX;
                    monstro[i].pos.y = proximoY;
                    monstro[i].passosRestantes--; // Só decrementa se o movimento foi bem-sucedido
                } else {
                    // se a posicao nao for valida, zera os passos restante
                    // para sortear uma nova direção
                    monstro[i].passosRestantes = 0;
                }
            }
            // se tentarMovimentarEsteTurno for false, o monstro não faz nada neste turno
            // e monstro[i].passosRestantes (que já seria <= 0) continua assim.
        }
    }
}

