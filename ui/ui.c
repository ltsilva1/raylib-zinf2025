//
// Created by lucas on 30/05/2025.
//

#include "../ui/ui.h"

#include <math.h>

#include "../nucleo/definicoes.h"
#include "raylib.h"
#include <stdio.h>

void DesenhaMenuPrincipal(Jogo* jogo) {
    ClearBackground(BLACK);

    DrawTexture(jogo->menuTex.fundoinical, 0, 0, WHITE);

    // Opções do Menu
    const char* opcoesTexto[3] = {
        "Novo Jogo",
        "Scoreboard",
        "Sair"
    };

    DrawRectangle(40, 560, 320, 180, Fade(BLACK, 0.6f)); // Fundo para as opções

    int tamanhoFonteOpcao = 30; // Tamanho da fonte atual
    int espacamentoOpcao = 45; // Espaço vertical entre as opções

    for (int i = 0; i < 3; i++) {
        Color cor = WHITE;
        if (i == jogo->seletorMenu) {
            cor = GOLD; // Cor de destaque para a opção selecionada
        }

        // Desenha uma seta simples ou marcador para a opção selecionada
        if (i == jogo->seletorMenu) {
            DrawText(">", 60,
            600 + i * espacamentoOpcao - (tamanhoFonteOpcao/2), tamanhoFonteOpcao, GOLD);
        }

        DrawText(opcoesTexto[i],
        100,
        600 + i * espacamentoOpcao - (tamanhoFonteOpcao/2), // Ajusta para centralizar verticalmente
        tamanhoFonteOpcao,
        cor);
    }
}

void desenhaHUD(Jogo* jogo) {
    switch (jogo->modoDebug) { // HUD ESPECIAL PARA A DEPURAÇÃO
        case false:
            DrawRectangle(0, 0, LARGURA, ALTURA_HUD, BLACK);

            char vidas[20];
            sprintf(vidas, "Vidas: %d", jogo->jogador.vidas);

            char pontos[20];
            sprintf(pontos, "Pontos: %d", jogo->jogador.pontuacaoTotal);

            char nivelAtual[20];
            sprintf(nivelAtual, "Nivel: %d", jogo->nivelAtual);

            int tamanhoFonte = 35;
            // Coordenada Y que centraliza o texto verticalmente na HUD de 60px
            int posY = (ALTURA_HUD - tamanhoFonte) / 2;

            // obs: (LARGURA / 3 / 2) é para encontrar o ponto central do primeiro terço
            DrawText(vidas,(LARGURA / 3 / 2) - (MeasureText(vidas, tamanhoFonte) / 2), posY, tamanhoFonte, WHITE);

            DrawText(pontos,(LARGURA / 2) - (MeasureText(pontos, tamanhoFonte) / 2),posY,tamanhoFonte,WHITE);

            DrawText(nivelAtual,(LARGURA / 3 * 2) + (LARGURA / 3 / 2) - (MeasureText(nivelAtual, tamanhoFonte) / 2),posY,tamanhoFonte,WHITE);

            break;

        case true: // HUD padrão
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

void DesenhaPause(Jogo* jogo) {
    // Desenhar uma caixa/painel para o menu em si
    float larguraMenu = 500;
    float alturaMenu = 300;
    float posXMenu = (LARGURA - larguraMenu) / 2; // Centraliza horizontalmente
    float posYMenu = (ALTURA - alturaMenu) / 2; // Centraliza verticalmente
    DrawRectangle(posXMenu, posYMenu, larguraMenu, alturaMenu, Fade(BLACK, 0.2f));
    DrawRectangleLines(posXMenu, posYMenu, larguraMenu, alturaMenu, LIGHTGRAY);

    //  O Título do menu
    int larguraTitulo = MeasureText("< PAUSADO >", 50);
    DrawText("< PAUSADO >", LARGURA / 2 - larguraTitulo / 2, posYMenu + 30, 50, WHITE);

    // As Opções do Menu
    char* opcoesTexto[3] = {
        "Continuar",
        "Voltar ao Menu",
        "Sair do Jogo"
    };

    int tamanhoFonteOpcao = 30; // Tamanho da fonte atual
    int espacamentoOpcao = 50; // Espaço vertical entre as opções
    float yInicialTexto = posYMenu + 120; // Posição Y inicial para a primeira opção

    for (int i = 0; i < 3; i++) {
        Color cor = WHITE;
        if (i == jogo->seletorMenu) {
            cor = GOLD; // Cor de destaque para a opção selecionada
        }

        float larguraTexto = MeasureText(opcoesTexto[i], tamanhoFonteOpcao); // Mede a largura do texto para centralizar
        float posXTexto = LARGURA / 2 - larguraTexto / 2; // Centraliza o texto
        float posYTexto = yInicialTexto + i * espacamentoOpcao; // Posição vertical com espaçamento entre elas

        DrawText(opcoesTexto[i], posXTexto, posYTexto, tamanhoFonteOpcao, cor);
    }
}
void DesenhaGameOver (Jogo* jogo) {
    ClearBackground(BLACK);

    DrawTexture(jogo->menuTex.fundobasico, 0, 0, WHITE);

    //  O Título do menu
    int larguraTitulo = MeasureText("< Fim de Jogo >", 120); // Mede a largura do texto para centralizar
    DrawText("< Fim de Jogo >", 1200 / 2 - larguraTitulo / 2, 800 / 6 - 30, 120, YELLOW);

    // Opções do Menu
    const char* opcoesTexto[2] = {
        "Reiniciar Jogo",
        "Voltar ao Menu"
    };

    int tamanhoFonteOpcao = 30;
    int espacamentoOpcao = 45; // Espaço vertical entre as opções

    for (int i = 0; i < 2; i++) {
        Color cor = WHITE;
        if (i == jogo->seletorMenu) {
            cor = GOLD; // Cor de destaque para a opção selecionada
        }

        // Desenha uma seta simples ou marcador para a opção selecionada
        if (i == jogo->seletorMenu) {
            DrawText(">", 60,
                     800 / 2 + i * espacamentoOpcao - (tamanhoFonteOpcao/2), tamanhoFonteOpcao, GOLD);
        }

        DrawText(opcoesTexto[i],
                 100,
                 800 / 2 + i * espacamentoOpcao - (tamanhoFonteOpcao/2), // Ajusta para centralizar verticalmente
                 tamanhoFonteOpcao,
                 cor);
    }

}

void DesenhaVitoria(Jogo* jogo) {
    ClearBackground(BLACK);

    DrawTexture(jogo->menuTex.fundobasico, 0, 0, WHITE);

    // Opções do Menu
    const char* opcoesTexto[2] = {
        "Reiniciar Jogo",
        "Voltar ao Menu"
    };

    //  O Título do menu
    int larguraTitulo = MeasureText("VITORIA!", 120); // Mede a largura do texto para centralizar
    DrawText("VITORIA!", 1200 / 2 - larguraTitulo / 2, 800 / 6 - 30, 120, YELLOW);


    int tamanhoFonteOpcao = 30;
    int espacamentoOpcao = 45; // Espaço vertical entre as opções

    float posXPainel = (LARGURA - 500) / 2.0f;
    float posYPainel = (ALTURA / 2.0f) - (200 / 2.0f) + 70;
    float yInicialTexto = posYPainel + (200 - (2 * tamanhoFonteOpcao + espacamentoOpcao * (2 - 1))) / 2 + (tamanhoFonteOpcao/2);


    // Desenha o retângulo preto com opacidade
    DrawRectangle(posXPainel, posYPainel + 20, 500, 150, Fade(BLACK, 0.6f));
    // Desenha uma borda para o painel
    DrawRectangleLines(posXPainel, posYPainel + 20, 500, 150, GRAY);

    for (int i = 0; i < 2; i++) {
        Color cor = WHITE;
        if (i == jogo->seletorMenu) {
            cor = GOLD; // Cor de destaque para a opção selecionada
        }

        float larguraTexto = MeasureText(opcoesTexto[i], tamanhoFonteOpcao);
        float posXTexto = LARGURA / 2 - larguraTexto / 2; // Calcula a posição X para que o centro do texto se alinhe com o centro da janela

        float posYTexto = yInicialTexto + (i * espacamentoOpcao);

        // Desenha o texto da opção na posição centralizada
        DrawText(opcoesTexto[i], posXTexto, posYTexto, tamanhoFonteOpcao, cor);

        // Desenha a seta indicadora relativa à posição do texto
        if (i == jogo->seletorMenu) {
            DrawText(">", posXTexto - 40, posYTexto, tamanhoFonteOpcao, GOLD);
        }
    }
}

void DesenhaTelaEntradaNome(Jogo* jogo) {
    ClearBackground(BLACK);

    int larguraTitulo = MeasureText("< VITORIA >", 120); // Mede a largura do texto para centralizar

    if (jogo->jogador.vivo == true)
        DrawText("< VITORIA >", 1200 / 2 - larguraTitulo / 2, 100, 120, YELLOW);
    // Caso o jogador tenha obtido um novo recorde, mas não tenha vencido, o título de vitória não será desenhado

    DrawText("NOVO RECORDE!", 1200 / 2 - MeasureText("NOVO RECORDE!", 40) / 2, 250 + 50, 40, GOLD);

    char textoScore[50];
    snprintf(textoScore, 50, "Sua pontuacao: %d", jogo->jogador.pontuacaoTotal);
    DrawText(textoScore, 1200 / 2 - MeasureText(textoScore, 20) / 2, 300 + 50, 20, LIGHTGRAY);

    DrawText("Digite seu nome:", 1200 / 2 - MeasureText("Digite seu nome:", 20) / 2, 350 + 100, 20, WHITE);

    // Caixa de texto
    DrawRectangle(1200 / 2 - 200, 400 +100, 400, 50, BLACK);
    DrawRectangleLines(1200 / 2 - 200, 400+100, 400, 50, LIGHTGRAY);

    // Texto digitado
    DrawText(jogo->nomeBuffer, 1200 / 2 - 190, 410 + 100, 40, GOLD);

    // A condição será verdadeira por meio segundo e falsa por meio segundo, fazendo o cursor piscar.
    if (fmodf(GetTime(), 1.0f) < 0.5f) {
        // Desenha o cursor no final do texto digitado
        DrawText("_", 1200 / 2 - 190 + MeasureText(jogo->nomeBuffer, 40), 415 + 100, 40, GOLD);
    }

    DrawText("Pressione Enter para confirmar", 1200 / 2 - MeasureText("Pressione Enter para confirmar", 20) / 2, 500+100, 20, GRAY);

}

void DesenhaPlacar(Jogo* jogo) {
    ClearBackground(BLACK);

    DrawTexture(jogo->menuTex.fundobasico, 0, 0, WHITE);

    // Painel
    float larguraPainel = 800; // Largura do painel
    float alturaPainel = 750; // Altura do painel
    float posXPainel = (LARGURA - larguraPainel) / 2.0f; // Centraliza na horizontal
    float posYPainel = (ALTURA - alturaPainel) / 2.0f; // Centraliza na vertical

    // Desenha o painel preto com 75% de opacidade para um efeito translúcido
    DrawRectangleRec((Rectangle){posXPainel, posYPainel, larguraPainel, alturaPainel}, Fade(BLACK, 0.75f));

    // Desenha uma borda para o painel
    DrawRectangleLinesEx((Rectangle){posXPainel, posYPainel, larguraPainel, alturaPainel}, 2, DARKGRAY);

    int larguraTitulo = MeasureText("Placar:", 60); // Mede a largura do texto para centralizar
    DrawText("Placar:", 1200 / 2 - larguraTitulo / 2, 800 / 6 - 30, 60, YELLOW);

    char pos1[100];
    sprintf(pos1, "Jogador: %s, Pontuacao: %d", jogo->score[0].nome, jogo->score[0].score);

    char pos2[100];
    sprintf(pos2, "Jogador: %s, Pontuacao: %d", jogo->score[1].nome, jogo->score[1].score);

    char pos3[100];
    sprintf(pos3, "Jogador: %s, Pontuacao: %d", jogo->score[2].nome, jogo->score[2].score);

    char pos4[100];
    sprintf(pos4, "Jogador: %s, Pontuacao: %d", jogo->score[3].nome, jogo->score[3].score);

    char pos5[100];
    sprintf(pos5, "Jogador: %s, Pontuacao: %d", jogo->score[4].nome, jogo->score[4].score);

    DrawText(pos1, 300, 200, 35, WHITE);
    DrawText(pos2, 300, 300, 35, WHITE);
    DrawText(pos3, 300,400, 35, WHITE);
    DrawText(pos4, 300, 500, 35, WHITE);
    DrawText(pos5, 300,600, 35, WHITE);

    // Instrução
    DrawText("Use Enter para voltar ao menu",
             1200 / 2 - MeasureText("Use Enter para voltar ao menu", 20) / 2,
             800 - 60, 20, LIGHTGRAY);

}

