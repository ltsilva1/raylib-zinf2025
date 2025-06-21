//
// Created by lucas on 26/05/2025.
//

#include "../nucleo/startup.h"
#include "../game/mapa/mapa.h"
#include "../nucleo/placar.h"
#include <stdlib.h>
#include <time.h>

void Inicializar(Jogo *jogo) {
    carregarTexturas(jogo);
    srand(time(NULL));
    jogo->jogador.pontuacaoTotal = 0;
    jogo->estado = MENU;
    jogo->nivelAtual = 1;
    jogo->seletorMenu = 0;
    jogo->modoDebug = false;
    lePlacar(jogo);
    carregaMapa(jogo);
    inicializarMonstrons(jogo);
    inicializarJogador(jogo);

}
void inicializarJogador(Jogo *jogo) {
    jogo->jogador.vidas = 3;
    jogo->jogador.dir = BAIXO;
    jogo->jogador.pos.x = jogo->mapa.posInicialJogador.x;
    jogo->jogador.pos.y = jogo->mapa.posInicialJogador.y;
    for (int i = 0; i < 3; ++i) {
        jogo->jogador.tilesAtaque[i].x = -1;
        jogo->jogador.tilesAtaque[i].y = -1;
    }
    jogo->jogador.temEspada = 0;
    jogo->jogador.instantesEspada = 0;
    jogo->jogador.instantesInvencibilidade = 0;
    jogo->jogador.tempoParaJogadorMover = 0.0f;
}

void carregarTexturas(Jogo* jogo) {
    jogo->menuTex.fundoinical = LoadTexture(".recursos/menu/fundoinicial.png");

    jogo->jogador.tex.sul = LoadTexture(".recursos/jogador/jogador_baixo.png");
    jogo->jogador.tex.norte = LoadTexture(".recursos/jogador/jogador_cima.png");
    jogo->jogador.tex.leste = LoadTexture(".recursos/jogador/jogador_direita.png");
    jogo->jogador.tex.oeste = LoadTexture(".recursos/jogador/jogador_esquerda.png");

    jogo->mapa.tex.sul = LoadTexture(".recursos/paredes/parede.png");

    jogo->mapa.chao[0] = LoadTexture(".recursos/chao/chao_placeholder.png");
    jogo->mapa.chao[1] = LoadTexture(".recursos/chao/chao_semmato.png");

    jogo->vidaTex = LoadTexture(".recursos/items/vida.png");
    jogo->espadaTex = LoadTexture(".recursos/items/espada.png");

}

void inicializarMonstrons(Jogo* jogo) {
    for (int i = 0; i < jogo->mapa.numMonstrosInicial; ++i) {
        jogo->mapa.monstro[i].pontuacao = rand() % 100 + 1;
        jogo->mapa.monstro[i].vivo = 1;
        jogo->mapa.monstro[i].dir = (rand() % 4);
        jogo->mapa.monstro[i].tex.norte = LoadTexture(".recursos/inimigos/inimigo_cima.png");
        jogo->mapa.monstro[i].tex.sul = LoadTexture(".recursos/inimigos/inimigo_baixo.png");
        jogo->mapa.monstro[i].tex.oeste = LoadTexture(".recursos/inimigos/inimigo_direita.png");
        jogo->mapa.monstro[i].tex.leste = LoadTexture(".recursos/inimigos/inimigo_esquerda.png");

        // --- A CORREÇÃO CRÍTICA ESTÁ AQUI ---
        // Garante que o monstro não está no meio de uma sequência de passos quando começa
        jogo->mapa.monstro[i].passosRestantes = 0;

        // Define um tempo inicial pequeno e aleatório (entre 0.0s e 1.0s)
        // para que os monstros comecem a se mover em momentos diferentes.
        jogo->mapa.monstro[i].tempoParaMover = (float) (rand() % 101) / 100.0f;

    }

    for (int i = jogo->mapa.numMonstrosInicial; i < 10; ++i)
        jogo->mapa.monstro[i].vivo = 0;
}

