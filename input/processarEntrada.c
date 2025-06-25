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

    switch (jogo->estado) {
        case JOGANDO:
            // Só processa o movimento se o jogador não estiver no meio de uma animação
            if (jogo->jogador.estaSeMovendo == false) {
                Vector2 movimentoDesejado = { 0.0f, 0.0f }; // Vetor para o buffer de inputs

                // Acumula os inputs no vetor
                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) movimentoDesejado.x += 1.0f;
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))  movimentoDesejado.x -= 1.0f;
                if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))  movimentoDesejado.y += 1.0f;
                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))    movimentoDesejado.y -= 1.0f;

                //  Decide qual movimento fazer
                if (movimentoDesejado.x != 0.0f || movimentoDesejado.y != 0.0f) {
                    if (jogo->jogador.ultimoEixoMovido == 1) { // Se o último movimento foi vertical, tenta o horizontal primeiro
                        if (movimentoDesejado.x != 0.0f) {
                            jogo->jogador.dir = (movimentoDesejado.x > 0) ? DIREITA : ESQUERDA;
                            moveJogador(&jogo->jogador, &jogo->mapa, (int)movimentoDesejado.x, 0);
                            jogo->jogador.ultimoEixoMovido = 0; // Registra que o último movimento foi horizontal
                        } else if (movimentoDesejado.y != 0.0f) {
                            jogo->jogador.dir = (movimentoDesejado.y > 0) ? BAIXO : CIMA;
                            moveJogador(&jogo->jogador, &jogo->mapa, 0, (int)movimentoDesejado.y);
                            jogo->jogador.ultimoEixoMovido = 1; // Registra que o último movimento foi vertical
                        }
                    } else { // Se o último movimento foi horizontal, tenta o vertical primeiro
                        if (movimentoDesejado.y != 0.0f) {
                            jogo->jogador.dir = (movimentoDesejado.y > 0) ? BAIXO : CIMA;
                            moveJogador(&jogo->jogador, &jogo->mapa, 0, (int)movimentoDesejado.y);
                            jogo->jogador.ultimoEixoMovido = 1; // Registra que o último movimento foi vertical
                        } else if (movimentoDesejado.x != 0.0f) {
                            jogo->jogador.dir = (movimentoDesejado.x > 0) ? DIREITA : ESQUERDA;
                            moveJogador(&jogo->jogador, &jogo->mapa, (int)movimentoDesejado.x, 0);
                            jogo->jogador.ultimoEixoMovido = 0; // Registra que o último movimento foi horizontal
                        }
                    }
                }
            }

                if (IsKeyPressed(KEY_J)) // Ataque da espada
                    if (jogo->jogador.temEspada == true)
                        jogo->jogador.instantesEspada = 0.5f;
                if (IsKeyPressed(KEY_TAB)) {jogo->estado = PAUSADO;} // Pausar o jogo
            break;

        case MENU:
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) // Guarda de navegação do menu
                if (jogo->seletorMenu < 2)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
                if (jogo->seletorMenu > 0)
                    jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) { // Seleção do menu principal
                switch (jogo->seletorMenu) {
                    case 0: // Novo Jogo
                        Inicializar(jogo);
                        jogo->estado = JOGANDO;
                        break;
                    case 1: // Scoreboard
                        jogo->estado = SCOREBOARDS_TABELA;
                        break;
                    case 2: // Sair do Jogo
                        CloseWindow();
                        break;
                }
            }
            break;

        case FIM_DE_JOGO:
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) // Guarda de navegação do menu
                if (jogo->seletorMenu < 1)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
                if (jogo->seletorMenu > 0)
                    jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) { // Seleção da tela de fim de jogo
                switch (jogo->seletorMenu) {
                    case 0: // Reiniciar Jogo
                        Inicializar(jogo);
                        jogo->estado = JOGANDO;
                        break;
                    case 1: // Voltar ao Menu
                        Inicializar(jogo);
                        break;
                }
            }
            break;

        case SCOREBOARDS_TABELA:
            if (IsKeyPressed(KEY_ENTER)) {jogo->estado = MENU;} // Voltar ao Menu
            break;

        case PAUSADO:
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) // Guarda de navegação do menu
                if (jogo->seletorMenu < 2)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
                if (jogo->seletorMenu > 0)
                    jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) {
                switch (jogo->seletorMenu) {
                    case 0:
                        jogo->estado = JOGANDO; // Continuar Jogo
                        break;
                    case 1:
                        Inicializar(jogo); // Voltar ao Menu
                        break;
                    case 2:
                        CloseWindow(); // Sair do jogo
                        break;
                }
            }

            if (IsKeyPressed((KEY_C))) {jogo->estado = JOGANDO;}
            if (IsKeyPressed((KEY_V))) {Inicializar(jogo);}
            if (IsKeyPressed((KEY_F))) {CloseWindow();}
            break;

        case ENTRANDO_NOME_RANKING:
            int tecla = GetCharPressed(); // Inteiro para comportar qualquer caractere

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

            // Verifica a tecla Backspace para apagar
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (jogo->contadorNome > 0) {
                    jogo->contadorNome--;
                    jogo->nomeBuffer[jogo->contadorNome] = '\0';
                }
            }

            // Verifica a tecla Enter para confirmar
            if (IsKeyPressed(KEY_ENTER)) {
                if (jogo->contadorNome == 0) { // Se não digitou nada, usa um nome padrão
                    snprintf(jogo->nomeBuffer, MAX_NOME_JOGADOR, "Anonimo");
                }
                //Atualiza e salva o placar
                snprintf(jogo->score[5 - 1].nome, MAX_NOME_JOGADOR, "%s", jogo->nomeBuffer);
                jogo->score[5 - 1].score = jogo->jogador.pontuacaoTotal;

                ordenaPlacar(jogo->score);
                salvaPlacar(jogo);

                // Muda para a tela de placar para mostrar o resultado
                jogo->estado = SCOREBOARDS_TABELA;
            }
            break;

        case VITORIA:
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) // Guarda de navegação do menu
                if (jogo->seletorMenu < 1)
                    jogo->seletorMenu += 1;
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
                if (jogo->seletorMenu > 0)
                    jogo->seletorMenu -= 1;

            if (IsKeyPressed((KEY_ENTER))) {
                switch (jogo->seletorMenu) {
                    case 0: // Reiniciar Jogo
                        Inicializar(jogo);
                        jogo->estado = JOGANDO;
                        break;
                    case 1: // Voltar ao Menu
                        Inicializar(jogo);
                        break;
                }
            }
    }
}

int PosicaoValida(Mapa* mapa, int x, int y) { // Se a posição for inválida returna 0, se for válida, retorna 1.
    if ((x < 0 || x > 24) || (y < 0 || y > 16)) // Testa se está fora do mapa
        return 0;
    if (mapa->mapa[y][x] == 'P') // Testa se é uma parede
        return 0;
    return 1;
}

