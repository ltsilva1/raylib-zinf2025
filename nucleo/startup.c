//
// Created by lucas on 26/05/2025.
//

#include "../nucleo/startup.h"
#include "../game/mapa/mapa.h"

void inicializarJogador(Jogo *jogo);

void Inicializar(Jogo *jogo) {
    jogo->estado = MENU;
    jogo->nivelAtual = 1;
    jogo->seletorMenu = 0;

    carregaMapa(jogo);
    inicializarJogador(jogo);

}
void inicializarJogador(Jogo *jogo) {
    jogo->jogador.pos.x = 1;
    jogo->jogador.pos.y = 1;

}