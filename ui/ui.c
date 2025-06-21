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
                         600 + i * espacamentoOpcao - (tamanhoFonteOpcao/2), tamanhoFonteOpcao, GOLD);
            }

            DrawText(opcoesTexto[i],
                     100,
                     600 + i * espacamentoOpcao - (tamanhoFonteOpcao/2), // Ajusta para centralizar verticalmente
                     tamanhoFonteOpcao,
                     cor);
        }

        // Instrução
        DrawText("Use as SETAS e ENTER para selecionar",
                 1200 / 2 - MeasureText("Use as SETAS e ENTER para selecionar", 20) / 2,
                 770, 20, LIGHTGRAY);

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
    // Desenhar uma caixa/painel para o menu em si
    float larguraMenu = 500;
    float alturaMenu = 300;
    float posXMenu = (LARGURA - larguraMenu) / 2; // Centraliza horizontalmente
    float posYMenu = (ALTURA - alturaMenu) / 2; // Centraliza verticalmente
    DrawRectangle(posXMenu, posYMenu, larguraMenu, alturaMenu, Fade(BLACK, 0.2f));
    DrawRectangleLines(posXMenu, posYMenu, larguraMenu, alturaMenu, LIGHTGRAY);

    // --- 2. O Título ---
    const char* titulo = "< PAUSADO >";
    int larguraTitulo = MeasureText(titulo, 50);
    DrawText(titulo, LARGURA / 2 - larguraTitulo / 2, posYMenu + 30, 50, WHITE);

    // --- 3. As Opções do Menu (parecido com o seu DesenhaGameOver) ---
    // Conforme o PDF do projeto, as opções são "Continuar", "Voltar ao Menu", "Sair".
    const char* opcoesTexto[3] = {
        "Continuar",
        "Voltar ao Menu",
        "Sair do Jogo"
    };

    int tamanhoFonteOpcao = 30;
    int espacamentoOpcao = 50;
    float yInicialTexto = posYMenu + 120; // Posição Y inicial para a primeira opção

    for (int i = 0; i < 3; i++) {
        // Usa uma variável de seletor específica para o menu de pausa para não conflitar
        // com o menu principal ou de game over. Você precisará adicionar 'seletorMenuPausa' na struct Jogo.
        Color cor = WHITE;
        if (i == jogo->seletorMenu) {
            cor = GOLD; // Cor de destaque para a opção selecionada
        }

        float larguraTexto = MeasureText(opcoesTexto[i], tamanhoFonteOpcao);
        float posXTexto = LARGURA / 2 - larguraTexto / 2; // Centraliza o texto
        float posYTexto = yInicialTexto + i * espacamentoOpcao;

        DrawText(opcoesTexto[i], posXTexto, posYTexto, tamanhoFonteOpcao, cor);
    }
}
void DesenhaGameOver (Jogo* jogo) {
    ClearBackground(BLACK);
    // Opções do Menu
    // Você pode definir um array de strings para as opções para facilitar
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

void DesenhaVitoria(Jogo* jogo) {
    ClearBackground(BLACK);
    // Opções do Menu
    // Você pode definir um array de strings para as opções para facilitar
    const char* opcoesTexto[2] = {
        "Reiniciar Jogo",
        "Voltar ao Menu"
    };

    const char* titulo = "VITORIA!"; //TROCAR PRA NÃO FICAR DESCARADO!!!!!!
    int larguraTitulo = MeasureText(titulo, 120); // Mede a largura do texto para centralizar
    DrawText(titulo, 1200 / 2 - larguraTitulo / 2, 800 / 6 - 30, 120, YELLOW);


    int tamanhoFonteOpcao = 30;
    int espacamentoOpcao = 45; // Espaço vertical entre as opções

    for (int i = 0; i < 2; i++) {
        Color cor = WHITE;
        if (i == jogo->seletorMenu) {
            cor = GOLD; // Cor de destaque para a opção selecionada
        }

        // Desenha uma seta simples ou marcador para a opção selecionada (opcional)
        if (i == jogo->seletorMenu) {
            DrawText(">", 500 - 40,
                     800 / 2 + i * espacamentoOpcao - (tamanhoFonteOpcao/2), tamanhoFonteOpcao, GOLD);
        }

        DrawText(opcoesTexto[i],
                 500,
                 800 / 2 + i * espacamentoOpcao - (tamanhoFonteOpcao/2), // Ajusta para centralizar verticalmente
                 tamanhoFonteOpcao,
                 cor);
    }
}

void DesenhaTelaEntradaNome(Jogo* jogo) {
    ClearBackground(BLACK);

    const char* titulo = "< VITORIA >"; //TROCAR PRA NÃO FICAR DESCARADO!!!!!!
    int larguraTitulo = MeasureText(titulo, 120); // Mede a largura do texto para centralizar


    DrawText(titulo, 1200 / 2 - larguraTitulo / 2, 100, 120, YELLOW);


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

    // Cursor piscando
    // fmodf(GetTime(), 1.0f) retorna um valor que varia de 0.0 a 1.0 a cada segundo.
    // A condição será verdadeira por meio segundo e falsa por meio segundo, fazendo o cursor piscar.
    if (fmodf(GetTime(), 1.0f) < 0.5f) {
        // Desenha o cursor no final do texto digitado
        DrawText("_", 1200 / 2 - 190 + MeasureText(jogo->nomeBuffer, 40), 415 + 100, 40, GOLD);
    }

    DrawText("Pressione ENTER para confirmar", 1200 / 2 - MeasureText("Pressione ENTER para confirmar", 20) / 2, 500+100, 20, GRAY);

}

void DesenhaPlacar(Jogo* jogo) {
    ClearBackground(BLACK);

    const char* titulo = "Placar:"; //TROCAR PRA NÃO FICAR DESCARADO!!!!!!
    int larguraTitulo = MeasureText(titulo, 60); // Mede a largura do texto para centralizar
    DrawText(titulo, 1200 / 2 - larguraTitulo / 2, 800 / 6 - 30, 60, YELLOW);

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
    DrawText("Use ENTER para voltar ao menu",
             1200 / 2 - MeasureText("Use ENTER para voltar ao menu", 20) / 2,
             800 - 60, 20, LIGHTGRAY);

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

