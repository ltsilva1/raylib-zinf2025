#include "../graficos/render.h"
#include "raylib.h"
#include "../nucleo/definicoes.h"
#include "../ui/ui.h"
#include <stdio.h>
#include <math.h>
#include "definicoes.h"



void desenhaJogo(Jogo* meuJogo) {
    switch (meuJogo->estado) {
        case JOGANDO:
            ClearBackground(RAYWHITE);
            desenhaHUD(meuJogo);
            desenhaCenario(meuJogo);
            desenhaEspada(meuJogo);
            desenhaJogador(meuJogo);
            desenhaVida(meuJogo);
            desenhaMonstro(meuJogo);
            break;
        case MENU:
            DesenhaMenuPrincipal(meuJogo);
            break;
        case FIM_DE_JOGO:
            DesenhaGameOver(meuJogo);
            break;

    }
}

void desenhaCenario(Jogo* jogo) {
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 24; ++j) //revisar o 24 ou 25
            if (jogo->mapa.mapa[i][j] == 'P')
                DrawTexture(jogo->mapa.tex.sul, j * CASA, i * CASA + ALTURA_HUD, WHITE);
            else DrawTexture(jogo->mapa.chao, j * CASA, i * CASA + ALTURA_HUD, WHITE);
}

void desenhaMonstro(Jogo* jogo) {
    for (int i = 0; i < 10; ++i) {
        if (jogo->mapa.monstro[i].vivo == 1) {
            Texture2D texturaAtual;

            Vector2 posicaoMonstro = { // Vetor necessário pra utilizar a função de desenhar textura
                jogo->mapa.monstro[i].pos.x * CASA + 1,
                jogo->mapa.monstro[i].pos.y * CASA + 1 + ALTURA_HUD
            };

            switch (jogo->mapa.monstro[i].dir) { // As texturas tão sendo carregadas toda hora, precisa mudar isso aqui
                case CIMA:
                    texturaAtual = jogo->mapa.monstro[i].tex.norte; // endereço textura pra cima;
                    break;
                case BAIXO:
                    texturaAtual = jogo->mapa.monstro[i].tex.sul;
                    break;;
                case ESQUERDA:
                    texturaAtual = jogo->mapa.monstro[i].tex.leste;
                    break;
                case DIREITA:
                    texturaAtual = jogo->mapa.monstro[i].tex.oeste;
                    break;
            }
            DrawTextureV(texturaAtual, posicaoMonstro, WHITE);
        }
    }
}

void desenhaJogador(Jogo* jogo) {
    Texture2D texturaAtual;

    Vector2 posicaoJogador = { // Vetor necessário pra utilizar a função de desenhar textura {TALVEZ MUDAR APARA POSICAOGRADE}
        jogo->jogador.pos.x * CASA + 1,
        jogo->jogador.pos.y * CASA + 1 + ALTURA_HUD
    };

    if (jogo->jogador.instantesInvencibilidade> 0) {
        if (fmodf(jogo->jogador.instantesInvencibilidade, 0.2f) < 0.1f) {
            return; // Pula o desenho do jogador neste quadro, fazendo-o "desaparecer"
        }
    }

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
        DrawTexture(jogo->espadaTex, jogo->mapa.posInicialEspada.x * CASA,
                  jogo->mapa.posInicialEspada.y * CASA + ALTURA_HUD, WHITE);
    for (int k = 0; k < 3; ++k)
        DrawRectangle(jogo->jogador.tilesAtaque[k].x * CASA, jogo->jogador.tilesAtaque[k].y * CASA + ALTURA_HUD, CASA, CASA, YELLOW);
}

void desenhaVida(Jogo* jogo) {
    for (int i = 0; i < 5; ++i)
        if (jogo->mapa.vidasPegadas[i] == 0)
            DrawTexture(jogo->vidaTex, jogo->mapa.vidasExtras[i].x * CASA,
                jogo->mapa.vidasExtras[i].y * CASA + ALTURA_HUD, WHITE);

}

void desenhaHUD(Jogo* jogo) {
    switch (jogo->modoDebug) {
        case false:
            DrawRectangle(0, 0, LARGURA, ALTURA_HUD, BLACK);

            char vidas[20];
            sprintf(vidas, "Vidas: %d", jogo->jogador.vidas);

            char pontos[20];
            sprintf(pontos, "Pontos: %d", jogo->jogador.pontuacaoTotal);

            char nivelAtual[20];
            sprintf(nivelAtual, "Nivel: %d", jogo->nivelAtual);

            DrawText(vidas, 20, 15, 35, WHITE);
            DrawText(pontos, 400, 15, 35, WHITE);
            DrawText(nivelAtual, 800, 15, 35, WHITE);
            break;

        case true:
            DrawRectangle(0, 0, LARGURA, ALTURA_HUD, DARKBLUE);

            char posJogador[50];
            sprintf(posJogador, "X: %d, Y: %d", jogo->jogador.pos.x, jogo->jogador.pos.y);

            char temEspada[20];
            if (jogo->jogador.temEspada == true)
                sprintf(temEspada, "Espada?: Sim");
            else sprintf(temEspada, "Espada?: Nao");

            char numMonstro[20];
            sprintf(numMonstro, "Monstros vivos: %d", jogo->mapa.numMonstros);

            DrawText(posJogador, 20, 15, 35, YELLOW);
            DrawText(temEspada, 400, 15, 35, YELLOW);
            DrawText(numMonstro, 800, 15, 35, YELLOW);
            break;
    }
}



