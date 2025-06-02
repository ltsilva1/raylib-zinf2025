#include "../graficos/render.h"
#include "raylib.h"
#include "../nucleo/definicoes.h"
#include "../ui/ui.h"
#include <stdio.h>



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
                DrawRectangle(j * CASA, i * CASA, CASA, CASA, DARKBROWN);
            else DrawRectangle(j * CASA, i * CASA, CASA, CASA, RAYWHITE);
}

void desenhaMonstro(Jogo* jogo) {
    for (int i = 0; i < 10; i++) { // Ou o número real de monstros no nível
            DrawRectangle(jogo->monstro[i].pos.x * CASA, // Aqui você usaria DrawTextureRec para o sprite do monstro
                          jogo->monstro[i].pos.y * CASA,
                          CASA, CASA, RED); // Cor temporária
        }
    }

void desenhaJogador(Jogo* jogo) {
    DrawRectangle(jogo->jogador.pos.x * CASA, // Aqui você usaria DrawTextureRec para o sprite do monstro
                  jogo->jogador.pos.y * CASA,
                   CASA, CASA, GREEN); // Cor temporária
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



