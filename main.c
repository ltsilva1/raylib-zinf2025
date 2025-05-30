#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"
#include "nucleo/definicoes.h"
#include "nucleo/startup.h"
#include "graficos/render.h"
#include "input/processarEntrada.h"
#include "nucleo/logica.h"

int main() {
	Jogo ZINF;

	InitWindow(LARGURA, ALTURA, "Morde & Assopra"); //Inicializa janela, com certo tamanho e titulo
	SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

	Inicializar(&ZINF);

	//Este laco repete enquanto a janela nao for fechada
	//Utilizamos ele para atualizar o estado do programa / jogo
		while (!WindowShouldClose()) {
			BeginDrawing(); //Inicia o ambiente de desenho na tela

			processarEntrada(&ZINF);

			processarLogica(&ZINF);

			desenhaJogo(&ZINF);

			EndDrawing(); //Finaliza o ambiente de desenho na tela
		}

		CloseWindow(); // Fecha a janela
		return 0;
	}
