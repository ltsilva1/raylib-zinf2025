//
// Created by lucas on 30/05/2025.
//

#include "../ui/ui.h"
#include "../nucleo/definicoes.h"
#include "raylib.h"
#include <stdio.h>

void DesenhaMenuPrincipal(Jogo* jogo) {
        ClearBackground(BLACK);
        // Título do Jogo
        const char* titulo = "Morde & Assopra"; //TROCAR PRA NÃO FICAR DESCARADO!!!!!!
        int larguraTitulo = MeasureText(titulo, 60); // Mede a largura do texto para centralizar
        DrawText(titulo, 1200 / 2 - larguraTitulo / 2, 800 / 6 - 30, 60, YELLOW);

        // Opções do Menu
        // Você pode definir um array de strings para as opções para facilitar
        const char* opcoesTexto[4] = {
            "Novo Jogo",
            "Carregar Jogo",
            "Scoreboard",
            "Sair"
        };

        int tamanhoFonteOpcao = 30;
        int espacamentoOpcao = 45; // Espaço vertical entre as opções

        for (int i = 0; i < 4; i++) {
            Color cor = WHITE;
            if (i == jogo->seletorMenu) {
                cor = GOLD; // Cor de destaque para a opção selecionada
            }

            // Desenha uma seta simples ou marcador para a opção selecionada (opcional)
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

        // Instrução
        DrawText("Use as SETAS e ENTER para selecionar",
                 1200 / 2 - MeasureText("Use as SETAS e ENTER para selecionar", 20) / 2,
                 800 - 60, 20, LIGHTGRAY);

        if (jogo->modoDebug == true)
            TesteMapaDebug(jogo);
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

void DesenhaPause(Jogo* jogo) {
    char pause[10];
    sprintf(pause, "PAUSADO");
    int larguraTitulo = MeasureText(pause, 60); // Mede a largura do texto para centralizar

    DrawText(pause, 1200 / 2 - larguraTitulo / 2, ALTURA / 2, 60, MAROON);
}

void DesenhaGameOver (Jogo* jogo) {
    ClearBackground(BLACK);
    // Opções do Menu
    // Você pode definir um array de strings para as opções para facilitar
    const char* opcoesTexto[3] = {
        "Carregar Jogo",
        "Reiniciar Jogo",
        "Voltar ao Menu"
    };

    int tamanhoFonteOpcao = 30;
    int espacamentoOpcao = 45; // Espaço vertical entre as opções

    for (int i = 0; i < 3; i++) {
        Color cor = WHITE;
        if (i == jogo->seletorMenu) {
            cor = GOLD; // Cor de destaque para a opção selecionada
        }

        // Desenha uma seta simples ou marcador para a opção selecionada (opcional)
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

#include <stdio.h> // Para snprintf

// Função de debug para desenhar a matriz do mapa como texto na tela
void TesteMapaDebug(Jogo* jogo) {
    int posXInicial = 50;  // Posição X inicial na tela para começar a desenhar
    int posYInicial = 70;  // Posição Y inicial (abaixo da HUD)
    int tamanhoFonte = 12; // Tamanho da fonte para os caracteres
    int espacamentoX = 10; // Espaçamento horizontal entre os caracteres
    int espacamentoY = 15; // Espaçamento vertical entre as linhas

    // Título para o debug visual
    DrawText("DEBUG: Matriz do Mapa Carregada", posXInicial, posYInicial - 20, 20, RED);

    // 1. Loop para percorrer cada linha do mapa
    for (int i = 0; i < 16; i++) {
        // 2. Loop para percorrer cada coluna da linha atual
        for (int j = 0; j < 24; j++) {
            char c = jogo->mapa.mapa[i][j];
            // Se o caractere for nulo, não desenha nada (fim da linha lida pelo fgets)
            if (c == '\0') {
                break;
            }
            // 3. Prepara o caractere para ser desenhado pelo DrawText
            // DrawText precisa de uma string, então criamos uma string temporária de 2 caracteres:
            // [caractere][caractere nulo '\0']
            char bufferDeCaractere[2];
            snprintf(bufferDeCaractere, sizeof(bufferDeCaractere), "%c", c);

            // 4. Calcula a posição do caractere na tela
            int posX = posXInicial + (j * espacamentoX);
            int posY = posYInicial + (i * espacamentoY);

            // 5. Desenha o caractere na tela
            DrawText(bufferDeCaractere, posX, posY, tamanhoFonte, WHITE);
        }
    }
}

