#ifndef CARREGAR_H
#define CARREGAR_H
#include "definicoes.h"

void salvaPlacar (Jogo* jogo);
void lePlacar (Jogo* jogo);
void ordenaPlacar(Score placar[]);
void atualizaPlacar (Jogo* jogo);
int EhNovoRecorde(const Jogo* jogo);

#endif //CARREGAR_H
