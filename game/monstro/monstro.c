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
const float intervaloMovimento = 0.3f;

void moveMonstro(Jogador* jogador, Monstro monstro[], int qtd_monstros, Mapa* mapa, float deltaTime) {
    for (int i = 0; i < qtd_monstros; i++) {
        if (monstro[i].vivo == 0) {
            continue; // Pula monstros mortos
        }

        monstro[i].tempoParaMover -= deltaTime;//subtrai um pequeno pedaço do temporizador de cada monstro

        //esse if faz com que o monstro se se mova quando o seu temporizador for igual a zero
        if (monstro[i].vivo == 1 && monstro[i].tempoParaMover <= 0.0f) {
            monstro[i].tempoParaMover = intervaloMovimento;//reseta o temporizador para 0.3 segundos novamente
            int deltaY = 0, deltaX = 0;
            bool tentarMovimentarEsteTurno = false; //flag para controlar se o movimento será tentado

            if (monstro[i].passosRestantes > 0) {
                //monstro está continuando uma sequência de movimentos
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
                //caso o monstro nao esteja em uma sequencia, inicia uma nova
                //int movimentaOuNao = rand() % 30;
                //if (monstro[i].tempoParaMover > 0 ) {
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
                    monstro[i].passosRestantes = 3; //inicia uma nova sequência de 3 passos
                //}
            }

            //se o monstro deve tentar se mover (seja continuando ou começando uma nova sequência)
            //int movimentaOuNao = rand() % 15;
            if (tentarMovimentarEsteTurno ) {
                int proximoX = monstro[i].pos.x + deltaX;
                int proximoY = monstro[i].pos.y + deltaY;

                if (PosicaoValida(mapa, proximoX, proximoY)) {
                    monstro[i].pos.x = proximoX;
                    monstro[i].pos.y = proximoY;
                    monstro[i].passosRestantes--; //só decrementa se o movimento foi bem-sucedido
                } else {
                    //se a posicao nao for valida, zera os passos restante
                    //para sortear uma nova direção
                    monstro[i].passosRestantes = 0;
                }
            }
            //se tentarMovimentarEsteTurno for false, o monstro não faz nada neste turno
            //e monstro[i].passosRestantes (que já seria <= 0) continua assim.
        }
    }
}

