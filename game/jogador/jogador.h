//
// Created by lucas on 02/06/2025.
//

#ifndef DESENHAJOGADOR_H
#define DESENHAJOGADOR_H
#include "definicoes.h"

void moveJogador(Jogador* jogador, Mapa* mapa, int direcaoX, int direcaoY);
void atualizarAnimacaoJogador(Jogador* jogador, float deltaTime);
void pegaEspada(Jogador* jogador, Mapa* mapa);
void pegaVida(Jogador* jogador, Mapa* mapa);
void danoJogador(Jogador* jogador, Monstro monstro[]);


#endif //DESENHAJOGADOR_H
