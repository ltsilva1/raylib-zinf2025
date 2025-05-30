//
// Created by lucas on 30/05/2025.
//

#include "ui.h"
#include "definicoes.h"
#include "raylib.h"

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
    }

