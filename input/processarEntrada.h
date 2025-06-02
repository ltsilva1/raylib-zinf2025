#ifndef PROCESSARENTRADA_H
#define PROCESSARENTRADA_H
#include "../nucleo/definicoes.h"

void processarEntrada(Jogo *jogo);
void moveJogador(Jogador* jogador, Mapa* mapa, int direcaoX, int direcaoY);
int PosicaoValida(Mapa* mapa, int x, int y);

#endif //PROCESSARENTRADA_H