#include <string.h>
#include <stdlib.h>
#include "raylib.h"

#define LARGURA 1200
#define ALTURA 800
#define CASA 50
//pinto

int main() {
    Rectangle jogador = { 300, 300, CASA, CASA }; // x, y, width, height
    Rectangle parede = { 600, 600, CASA, CASA }; // x, y, width, height
    Rectangle inimigo = { 150, 150, CASA, CASA }; // x, y, width, height
        char mapa[16][24];
        mapa[0][0] = 'P';
        mapa[0][1] = 'P';       mapa[1][1] = 'P';



    InitWindow(LARGURA, ALTURA, "Teclas"); //Inicializa janela, com certo tamanho e titulo
    SetWindowTitle("Quadrado"); // Define o título da janela
    SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

    //Este laco repete enquanto a janela nao for fechada
    //Utilizamos ele para atualizar o estado do programa / jogo
    while (!WindowShouldClose()) {
            Rectangle proximaPosJogador = jogador;

        // Processamento de entrada
        if (IsKeyPressed(KEY_RIGHT)) { //Mexe o quadrado para direita quando a seta direita for pressionada
                proximaPosJogador.x += CASA;
                if (!CheckCollisionRecs(proximaPosJogador, parede))
                        jogador.x += CASA;
                proximaPosJogador.x = jogador.x;
        }

        if (IsKeyPressed(KEY_LEFT)) { //Mexe o quadrado para esquerda quando a seta esquerda for pressionada
                proximaPosJogador.x -= CASA;
                if (!CheckCollisionRecs(proximaPosJogador, parede))
                        jogador.x -= CASA;
                proximaPosJogador.x = jogador.x;
        }

        if (IsKeyPressed(KEY_UP)) { //Mexe o quadrado para cima quando a seta para cima for pressionada
                proximaPosJogador.y -= CASA;
                if (!CheckCollisionRecs(proximaPosJogador, parede))
                        jogador.y -= CASA;
                proximaPosJogador.y = jogador.y;
        }

        if (IsKeyPressed(KEY_DOWN)) { //Mexe o quadrado para baixo quando a seta para baixo for pressionada
                proximaPosJogador.y += CASA;
                if (!CheckCollisionRecs(proximaPosJogador, parede))
                        jogador.y += CASA;
                proximaPosJogador.y = jogador.y;
        }

    	// Atualiza o que eh mostrado na tela a partir do estado do jogo
    	BeginDrawing(); //Inicia o ambiente de desenho na tela
    	ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo
            for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 24; j++) {
                            if (mapa[j][i] == 'P') {
                                    parede.x = i*CASA;
                                    parede.y = j*CASA;

                            }
                            if (mapa[j][i] == 'J')
                                    DrawRectangleRec(jogador, GREEN);
                            if (mapa[j][i] == 'I') {

                            }

                    }
            }
            DrawRectangleRec(jogador, GREEN);
            DrawRectangleRec(inimigo, RED);
            DrawRectangleRec(parede, BROWN);
	EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
    }
