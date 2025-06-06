//
// Created by lucas on 26/05/2025.
//

#include "../nucleo/startup.h"
#include "../game/mapa/mapa.h"
#include <stdlib.h>
#include <time.h>

void Inicializar(Jogo *jogo) {
    srand(time(NULL));
    jogo->estado = MENU;
    jogo->nivelAtual = 1;
    jogo->seletorMenu = 0;

    carregarTexturas(jogo);
    carregaMapa(jogo);
    inicializarJogador(jogo);
    inicializarMonstrons(jogo);

}
void inicializarJogador(Jogo *jogo) {
    jogo->jogador.dir = BAIXO;
    jogo->jogador.pos.x = 1;
    jogo->jogador.pos.y = 1; // BOTAR O PosIncialJogador aqui dps
    jogo->jogador.vidas = 3;
    jogo->jogador.pontuacaoTotal = 0;
    jogo->jogador.temEspada = 0;


}

void carregarTexturas(Jogo* jogo) {
    jogo->jogador.tex.sul = LoadTexture(".recursos/jogador/jogador_baixo.png");
    jogo->jogador.tex.norte = LoadTexture(".recursos/jogador/jogador_cima.png");
    jogo->jogador.tex.leste = LoadTexture(".recursos/jogador/jogador_direita.png");
    jogo->jogador.tex.oeste = LoadTexture(".recursos/jogador/jogador_esquerda.png");

    jogo->mapa.tex.sul = LoadTexture(".recursos/paredes/parede.png");
    jogo->mapa.chao = LoadTexture(".recursos/chao/chao_placeholder.png");

    jogo->vidaTex = LoadTexture(".recursos/items/vida.png");
    jogo->espadaTex = LoadTexture(".recursos/items/espada.png");

}

void inicializarMonstrons(Jogo* jogo) {
    for (int i = 0; i < 10; ++i) {
        jogo->monstro[i].vivo = 1;
        jogo->monstro[i].tex.norte = LoadTexture(".recursos/inimigos/inimigo_cima.png");
        jogo->monstro[i].tex.sul = LoadTexture(".recursos/inimigos/inimigo_baixo.png");
        jogo->monstro[i].tex.oeste = LoadTexture(".recursos/inimigos/inimigo_direita.png");
        jogo->monstro[i].tex.leste = LoadTexture(".recursos/inimigos/inimigo_esquerda.png");
    }



}