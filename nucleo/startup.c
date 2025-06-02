//
// Created by lucas on 26/05/2025.
//

#include "../nucleo/startup.h"
#include "../game/mapa/mapa.h"
#include <stdlib.h>
#include <time.h>

void inicializarJogador(Jogo *jogo);

void Inicializar(Jogo *jogo) {
    srand(time(NULL));
    jogo->estado = MENU;
    jogo->nivelAtual = 1;
    jogo->seletorMenu = 0;

    carregaMapa(jogo);
    inicializarJogador(jogo);

}
void inicializarJogador(Jogo *jogo) {
    jogo->jogador.pos.x = 1;
    jogo->jogador.pos.y = 1; // BOTAR O PosIncialJogador aqui dps
    jogo->jogador.vidas = 3;
    jogo->jogador.pontuacaoTotal = 0;
    jogo->jogador.temEspada = 0;


}