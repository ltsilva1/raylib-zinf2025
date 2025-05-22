#include <string.h>
#include <stdlib.h>
#include "raylib.h"

#define LARGURA 1200
#define ALTURA 860
#define CASA 50


int main() {
    Rectangle jogador = { 300, 300, CASA, CASA }; // x, y, width, height
    Rectangle parede = { 600, 600, CASA, CASA }; // x, y, width, height

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
        DrawRectangleRec(jogador, GREEN); // Desenha o retângulo na posição atual
        DrawRectangleRec(parede, RED); // Desenha outro quadrado
	EndDrawing(); //Finaliza o ambiente de desenho na tela
    }

    CloseWindow(); // Fecha a janela
    return 0;
    }
