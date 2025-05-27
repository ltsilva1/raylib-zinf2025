#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"
#include "definicoes.h"
#include "startup.h"
#include "desenha_prot.h"
#include "processarEntrada.h"
#include "logica.h"

int main() {
	Jogo ZINF;

	InitWindow(LARGURA, ALTURA, "Morde & Assopra"); //Inicializa janela, com certo tamanho e titulo
	SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

	Inicializar(&ZINF);

	//Este laco repete enquanto a janela nao for fechada
	//Utilizamos ele para atualizar o estado do programa / jogo
		while (!WindowShouldClose()) {
			BeginDrawing(); //Inicia o ambiente de desenho na tela
			ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo

			processarEntrada(&ZINF);

			//processarLogica(&meuJogo);

			desenhaJogo(&ZINF);

			EndDrawing(); //Finaliza o ambiente de desenho na tela
		}

		CloseWindow(); // Fecha a janela
		return 0;
	}
