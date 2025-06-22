//
// Created by lucas on 30/05/2025.
//

#ifndef UI_H
#define UI_H
#include "../nucleo/definicoes.h"

void DesenhaMenuPrincipal(Jogo* jogo);
void desenhaHUD(Jogo* jogo);
void DesenhaGameOver (Jogo* jogo);
void DesenhaPause(Jogo* jogo);
void DesenhaVitoria(Jogo* jogo);
void DesenhaTelaEntradaNome(Jogo* jogo);
void DesenhaPlacar(Jogo* jogo);

#endif //UI_H
