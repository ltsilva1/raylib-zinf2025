#include "../graficos/render.h"
#include "raylib.h"
#include "raymath.h"
#include "../nucleo/definicoes.h"
#include "../ui/ui.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
        case PAUSADO:
            DesenhaPause(meuJogo);
            break;
        case VITORIA:
            DesenhaVitoria(meuJogo);
            break;
        case SCOREBOARDS_TABELA:
            DesenhaPlacar(meuJogo);
            break;
        case ENTRANDO_NOME_RANKING:
            DesenhaTelaEntradaNome(meuJogo);
            break;

    }
}

void desenhaCenario(Jogo* jogo) {
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 24; ++j) //revisar o 24 ou 25
            if (jogo->mapa.mapa[i][j] == 'P')
                DrawTexture(jogo->mapa.tex.sul, j * CASA, i * CASA + ALTURA_HUD, WHITE);
            else {
                int mato = jogo->mapa.chaoVariacao[i][j];

                if (mato == 0)
                DrawTexture(jogo->mapa.chao[0], j * CASA, i * CASA + ALTURA_HUD, WHITE);
                else DrawTexture(jogo->mapa.chao[1], j * CASA, i * CASA + ALTURA_HUD, WHITE);
            }
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

/*switch (jogo->jogador.dir) {
    case CIMA:    texturaParaUsar = jogo->jogador.animtex.movTexNorte; break;
    case BAIXO:   texturaParaUsar = jogo->jogador.animtex.movTexSul;   break;
    case ESQUERDA:texturaParaUsar = jogo->jogador.animtex.movTexOeste;  break;
    case DIREITA: texturaParaUsar = jogo->jogador.animtex.movTexLeste;  break;
    default:      texturaParaUsar = jogo->jogador.animtex.movTexSul;
}

// Seleciona o SPRITE ESTÁTICO correto baseado na direção
switch (jogo->jogador.dir) {
    case CIMA:    texturaParaUsar = jogo->jogador.tex.norte; break;
    case BAIXO:   texturaParaUsar = jogo->jogador.tex.sul;   break;
    case ESQUERDA:texturaParaUsar = jogo->jogador.tex.oeste;  break;
    case DIREITA: texturaParaUsar = jogo->jogador.tex.leste;  break;
    default:      texturaParaUsar = jogo->jogador.tex.sul;
} */

// Em render.c
void desenhaJogador(Jogo* jogo) {
    // Pisca quando invencível
    if (jogo->jogador.instantesInvencibilidade > 0) {
        if (fmodf(GetTime(), 0.2f) < 0.1f) {
            return;
        }
    }

    Texture2D texturaParaUsar;
    Rectangle sourceRec;
    float offsetX = 0.0f;
    float offsetY = 0.0f;

    // Decide qual textura, "source" e offset usar
    if (jogo->jogador.estaSeMovendo) {
        // Caso o jogador esteja no meio do movimento

        switch (jogo->jogador.dir) {
            case CIMA:    texturaParaUsar = jogo->jogador.animtex.movTexNorte; break;
            case BAIXO:   texturaParaUsar = jogo->jogador.animtex.movTexSul;   break;
            case ESQUERDA:texturaParaUsar = jogo->jogador.animtex.movTexOeste;  break;
            case DIREITA: texturaParaUsar = jogo->jogador.animtex.movTexLeste;  break;
            default:      texturaParaUsar = jogo->jogador.animtex.movTexSul;
        }

        const int LARGURA_SPRITE_ANDANDO = 32;
        const int ALTURA_SPRITE_ANDANDO = 42;
        const int ESPACAMENTO = 1; // Cada sprite de animação tem espaço de 1 pixel

        sourceRec.x = (float)jogo->jogador.frameAtual * (LARGURA_SPRITE_ANDANDO + ESPACAMENTO);
        sourceRec.y = 0;
        sourceRec.width = (float)LARGURA_SPRITE_ANDANDO;
        sourceRec.height = (float)ALTURA_SPRITE_ANDANDO;

        // Define o offset para o sprite de 32x42 ( Spritesheet de animação tem 230x48 )
        offsetX = (CASA - LARGURA_SPRITE_ANDANDO) / 2.0f;
        offsetY = (CASA - ALTURA_SPRITE_ANDANDO) / 2.0f;

    } else {
        // Caso o jogador esteja parado:
        switch (jogo->jogador.dir) {
            case CIMA:    texturaParaUsar = jogo->jogador.tex.norte; break;
            case BAIXO:   texturaParaUsar = jogo->jogador.tex.sul;   break;
            case ESQUERDA:texturaParaUsar = jogo->jogador.tex.oeste;  break;
            case DIREITA: texturaParaUsar = jogo->jogador.tex.leste;  break;
            default:      texturaParaUsar = jogo->jogador.tex.sul;
        }

        sourceRec = (Rectangle){ 0.0f, 0.0f, (float)texturaParaUsar.width, (float)texturaParaUsar.height };

        // Define o offset para o sprite parado (48x48)
        offsetX = (CASA - 48) / 2.0f; // = 1
        offsetY = (CASA - 48) / 2.0f; // = 1
    }

    // Lógica de cálculo da posição da casa
    Vector2 posicaoVisualEmPixels;
    if (jogo->jogador.estaSeMovendo) {
        Vector2 posOrigemPx = { (float)jogo->jogador.posOrigem.x * CASA, (float)jogo->jogador.posOrigem.y * CASA };
        Vector2 posDestinoPx = { (float)jogo->jogador.posDestino.x * CASA, (float)jogo->jogador.posDestino.y * CASA };
        float percentualCompleto = jogo->jogador.progressoMovimento / DURACAO_MOVIMENTO;
        if (percentualCompleto > 1.0f) percentualCompleto = 1.0f;
        posicaoVisualEmPixels = Vector2Lerp(posOrigemPx, posDestinoPx, percentualCompleto);
    } else {
        posicaoVisualEmPixels.x = (float)jogo->jogador.pos.x * CASA;
        posicaoVisualEmPixels.y = (float)jogo->jogador.pos.y * CASA;
    }

    // Adiciona os offsets corretos mais o da HUD
    posicaoVisualEmPixels.x += offsetX;
    posicaoVisualEmPixels.y += offsetY + ALTURA_HUD;

    // Desenha a textura
    DrawTextureRec(texturaParaUsar, sourceRec, posicaoVisualEmPixels, WHITE);
}

void desenhaEspada(Jogo* jogo) {
    if (jogo->mapa.espadaPegada == 0)
        DrawTexture(jogo->espadaTex, jogo->mapa.posInicialEspada.x * CASA,
                  jogo->mapa.posInicialEspada.y * CASA + ALTURA_HUD, WHITE);
    if (jogo->jogador.instantesEspada > 0) {

        Texture2D texturaAtaqueParaUsar;

        // Escolhe qual dos 4 sprites de ataque usar com base na direção do jogador
        switch (jogo->jogador.dir) {
            case CIMA:    texturaAtaqueParaUsar = jogo->jogador.texEsp.ataqueTexNorte;  break;
            case BAIXO:   texturaAtaqueParaUsar = jogo->jogador.texEsp.ataqueTexSul;    break;
            case ESQUERDA:texturaAtaqueParaUsar = jogo->jogador.texEsp.ataqueTexOeste;  break;
            case DIREITA: texturaAtaqueParaUsar = jogo->jogador.texEsp.ataqueTexLeste;  break;
            default:      texturaAtaqueParaUsar = jogo->jogador.texEsp.ataqueTexSul;
        }

        for (int k = 0; k < 3; ++k) {
                // Calcula a posição em pixels para cada tile de ataque
                int posX = jogo->jogador.tilesAtaque[k].x * CASA;
                int posY = jogo->jogador.tilesAtaque[k].y * CASA + ALTURA_HUD;

                // Desenha o sprite do ataque na posição calculada
                // Dica: Use Fade(WHITE, 0.7f) para um efeito semi-transparente!
                DrawTexture(texturaAtaqueParaUsar, posX, posY, WHITE);
        }
    }
}

void desenhaVida(Jogo* jogo) {
    for (int i = 0; i < jogo->mapa.numVidasExtras; ++i)
        if (jogo->mapa.vidasPegadas[i] == 0)
            DrawTexture(jogo->vidaTex, jogo->mapa.vidasExtras[i].x * CASA,
                jogo->mapa.vidasExtras[i].y * CASA + ALTURA_HUD, WHITE);

}



