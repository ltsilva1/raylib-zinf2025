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
    jogo->modoDebug = false;
    carregarTexturas(jogo);
    carregaMapa(jogo);
    inicializarMonstrons(jogo);
    inicializarJogador(jogo);

}
void inicializarJogador(Jogo *jogo) {
    jogo->jogador.pontuacaoTotal = 0;
    jogo->jogador.dir = BAIXO;
    jogo->jogador.pos.x = jogo->mapa.posInicialJogador.x;
    jogo->jogador.pos.y = jogo->mapa.posInicialJogador.y;
    jogo->jogador.vidas = 3;
    jogo->jogador.pontuacaoTotal = 0;
    jogo->jogador.temEspada = 0;
    jogo->jogador.instantesInvencibilidade = 0;


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
        jogo->mapa.monstro[i].pontuacao = rand() % 100 + 1;
        jogo->mapa.monstro[i].vivo = 1;
        jogo->mapa.monstro[i].tex.norte = LoadTexture(".recursos/inimigos/inimigo_cima.png");
        jogo->mapa.monstro[i].tex.sul = LoadTexture(".recursos/inimigos/inimigo_baixo.png");
        jogo->mapa.monstro[i].tex.oeste = LoadTexture(".recursos/inimigos/inimigo_direita.png");
        jogo->mapa.monstro[i].tex.leste = LoadTexture(".recursos/inimigos/inimigo_esquerda.png");
    }

    for (int i = jogo->mapa.numMonstros; i < 10; ++i)
        jogo->mapa.monstro[i].vivo = 0;
}

void inicializarMapa(Jogo* jogo) {


}