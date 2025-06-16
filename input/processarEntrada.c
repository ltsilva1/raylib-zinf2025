#include "processarEntrada.h"

#include <stdio.h>
#include <string.h>

#include "placar.h"
#include "raylib.h"
#include "startup.h"
#include "external/miniaudio.h"
#include "../nucleo/definicoes.h"


void processarEntrada(Jogo *jogo) {
    if (IsKeyPressed(KEY_P)) { // Ativa ou desativa o modo de depuração
        if (jogo->modoDebug == false) {
            jogo->modoDebug = true;
        } else {jogo->modoDebug = false;}
    }
    float deltaTime = 0.0f;
    deltaTime = GetFrameTime();
    const float intervaloMovimento = 0.12f;

    switch (jogo->estado) {
        case JOGANDO:
            jogo->jogador.tempoParaJogadorMover -= deltaTime;
            if (jogo->jogador.tempoParaJogadorMover <= 0.0f) {
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                    moveJogador(&jogo->jogador, &jogo->mapa, -1, 0);
                    jogo->jogador.dir = ESQUERDA;
                    jogo->jogador.tempoParaJogadorMover = intervaloMovimento;
                }
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                    moveJogador(&jogo->jogador, &jogo->mapa, 1, 0);
                    jogo->jogador.dir = DIREITA;
                    jogo->jogador.tempoParaJogadorMover = intervaloMovimento;
                }
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
                    moveJogador(&jogo->jogador, &jogo->mapa, 0, -1);
                    jogo->jogador.dir = CIMA;
                    jogo->jogador.tempoParaJogadorMover = intervaloMovimento;
                }
                if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
                    moveJogador(&jogo->jogador, &jogo->mapa, 0, 1);
                    jogo->jogador.dir = BAIXO;
                    jogo->jogador.tempoParaJogadorMover = intervaloMovimento;
                }
            }
                if (IsKeyPressed(KEY_J)) {jogo->jogador.instantesEspada = 0.5f;}
                if (IsKeyPressed(KEY_ENTER)) {jogo->estado = PAUSADO;}

            break;

        case MENU:
            if (IsKeyPressed(KEY_DOWN))
                if (jogo->seletorMenu < 3)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP))
                if (jogo->seletorMenu > 0)
                    jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) {
                switch (jogo->seletorMenu) {
                    case 0:
                        jogo->estado = JOGANDO;
                        break;
                    case 1:
                        //Carregar jogo
                        break;
                    case 2:
                        jogo->estado = SCOREBOARDS_TABELA;
                        break;
                    case 3:
                        CloseWindow();
                        break;
                }
            }
            break;

        case FIM_DE_JOGO:
            if (IsKeyPressed(KEY_DOWN))
                if (jogo->seletorMenu < 2)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP))
                if (jogo->seletorMenu > 0)
                    jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) {
                switch (jogo->seletorMenu) {
                    case 0:
                        // Carregar jogo
                        break;
                    case 1:
                        Inicializar(jogo);
                        jogo->estado = JOGANDO;
                        break;
                    case 2:
                        Inicializar(jogo);
                        break;
                }
            }
            break;
        case SCOREBOARDS_TABELA:
            if (IsKeyPressed(KEY_ENTER)) {jogo->estado = MENU;}
            break;

        case PAUSADO:
            if (IsKeyPressed(KEY_ENTER)) {jogo->estado = JOGANDO;}
            break;

        case ENTRANDO_NOME_RANKING:
            int tecla = GetCharPressed();

            // Processa todas as teclas na fila da Raylib
            while (tecla > 0) {
                // Aceita apenas caracteres imprimíveis e se houver espaço no buffer
                if ((tecla >= 32) && (tecla <= 125) && (jogo->contadorNome < MAX_NOME_JOGADOR)) {
                    jogo->nomeBuffer[jogo->contadorNome] = (char)tecla;
                    jogo->contadorNome++;
                    jogo->nomeBuffer[jogo->contadorNome] = '\0'; // Mantém a string terminada
                }
                tecla = GetCharPressed(); // Pega a próxima tecla na fila
            }

            // Verifica a tecla BACKSPACE para apagar
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (jogo->contadorNome > 0) {
                    jogo->contadorNome--;
                    jogo->nomeBuffer[jogo->contadorNome] = '\0';
                }
            }

            // Verifica a tecla ENTER para confirmar
            if (IsKeyPressed(KEY_ENTER)) {
                if (jogo->contadorNome == 0) { // Se não digitou nada, usa um nome padrão
                    snprintf(jogo->nomeBuffer, MAX_NOME_JOGADOR, "Anonimo");
                }
                // Agora sim, atualizamos e salvamos o placar
                snprintf(jogo->score[5 - 1].nome, MAX_NOME_JOGADOR, "%s", jogo->nomeBuffer);
                jogo->score[5 - 1].score = jogo->jogador.pontuacaoTotal;

                ordenaPlacar(jogo->score);
                salvaPlacar(jogo);

                // Muda para a tela de placar ou de game over para mostrar o resultado
                jogo->estado = SCOREBOARDS_TABELA;
            }
            break;

        case VITORIA:
            if (IsKeyPressed(KEY_DOWN))
                if (jogo->seletorMenu < 2)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP))
                if (jogo->seletorMenu > 0)
                    jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) {
                switch (jogo->seletorMenu) {
                    case 0:
                        jogo->estado = MENU;
                        jogo->seletorMenu = 0;
                        break;
                    case 1:
                        jogo->estado = MENU;
                        jogo->seletorMenu = 0;
                        Inicializar(jogo);
                        break;
                }
            }
    }
}

int PosicaoValida(Mapa* mapa, int x, int y) { //Se a posição for inválida returna 0, se for válida, retorna 1.
    if ((x < 0 || x > 24) || (y < 0 || y > 16))
        return 0;
    if (mapa->mapa[y][x] == 'P')
        return 0;
    return 1;
}

