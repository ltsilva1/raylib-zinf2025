#include "../graficos/render.h"
#include "raylib.h"
#include "../nucleo/definicoes.h"
#include "../ui/ui.h"
#include <stdio.h>
#include "definicoes.h"



void desenhaJogo(Jogo* meuJogo) {
    switch (meuJogo->estado) {
        case JOGANDO:
            ClearBackground(RAYWHITE);
            desenhaCenario(meuJogo);
            desenhaMonstro(meuJogo);
            desenhaEspada(meuJogo);
            desenhaJogador(meuJogo);
            desenhaVida(meuJogo);
            printf("%d", meuJogo->jogador.vidas);
            //printf("%d", meuJogo->jogador.temEspada);
            break;
        case MENU:
            DesenhaMenuPrincipal(meuJogo);
            break;

    }
}

void desenhaCenario(Jogo* jogo) {
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 24; ++j) //revisar o 24 ou 25
            if (jogo->mapa.mapa[i][j] == 'P')
                DrawTexture(jogo->mapa.tex.sul, j * CASA, i * CASA, WHITE);
            else DrawTexture(jogo->mapa.chao, j * CASA, i * CASA, WHITE);
}

void desenhaMonstro(Jogo* jogo) {
    for (int i = 0; i < 10; ++i) {
        Texture2D texturaAtual;

        Vector2 posicaoMonstro = { // Vetor necessário pra utilizar a função de desenhar textura
            jogo->monstro[i].pos.x * CASA + 1,
            jogo->monstro[i].pos.y * CASA + 1
        };

        switch (jogo->monstro[i].dir) { // As texturas tão sendo carregadas toda hora, precisa mudar isso aqui
            case CIMA:
                texturaAtual = jogo->monstro[i].tex.norte; // endereço textura pra cima;
                break;
            case BAIXO:
                texturaAtual = jogo->monstro[i].tex.sul;
                break;;
            case ESQUERDA:
                texturaAtual = jogo->monstro[i].tex.leste;
                break;
            case DIREITA:
                texturaAtual = jogo->monstro[i].tex.oeste;
                break;
        }
        DrawTextureV(texturaAtual, posicaoMonstro, WHITE);
    }
}

void desenhaJogador(Jogo* jogo) {
    Texture2D texturaAtual;

    Vector2 posicaoJogador = { // Vetor necessário pra utilizar a função de desenhar textura
        jogo->jogador.pos.x * CASA + 1,
        jogo->jogador.pos.y * CASA + 1
    };

    switch (jogo->jogador.dir) { // As texturas tão sendo carregadas toda hora, precisa mudar isso aqui
        case CIMA:
            texturaAtual = jogo->jogador.tex.norte; // endereço textura pra cima;
            break;
        case BAIXO:
            texturaAtual = jogo->jogador.tex.sul;
            break;;
        case ESQUERDA:
            texturaAtual = jogo->jogador.tex.oeste;
            break;
        case DIREITA:
            texturaAtual = jogo->jogador.tex.leste;
            break;
    }
    DrawTextureV(texturaAtual, posicaoJogador, WHITE);
}

void desenhaEspada(Jogo* jogo) {
    if (jogo->mapa.espadaPegada == 0)
        DrawRectangle(jogo->mapa.posInicialEspada.x * CASA, // Aqui você usaria DrawTextureRec para o sprite do monstro
                  jogo->mapa.posInicialEspada.y * CASA,
                  CASA, CASA, YELLOW); // Cor temporária

}

void desenhaVida(Jogo* jogo) {
    for (int i = 0; i < 5; ++i)
        if (jogo->mapa.vidasPegadas[i] == 0)
            DrawRectangle(jogo->mapa.vidasExtras[i].x * CASA, // Aqui você usaria DrawTextureRec para o sprite do monstro
                      jogo->mapa.vidasExtras[i].y * CASA,
                      CASA, CASA, PINK); // Cor temporária

}



