#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"
#include "definicoes.h"
#include "mapa.h"
#include "desenha_prot.h"
#include "processarEntrada.h"

int main() {
	Jogo meuJogo;

	InitWindow(LARGURA, ALTURA, "Teclas"); //Inicializa janela, com certo tamanho e titulo
	SetWindowTitle("Quadrado"); // Define o título da janela
	SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

	//Este laco repete enquanto a janela nao for fechada
	//Utilizamos ele para atualizar o estado do programa / jogo
	char mapa[16][25];

	carregaMapa(&meuJogo);
	meuJogo.jogador.pos.x = 7;
	meuJogo.jogador.pos.y = 7;


		while (!WindowShouldClose()) {
			BeginDrawing(); //Inicia o ambiente de desenho na tela
			ClearBackground(RAYWHITE); //Limpa a tela e define cor de fundo

			processarEntrada(&meuJogo);

			desenhaJogo(&meuJogo);

			EndDrawing(); //Finaliza o ambiente de desenho na tela
		}

		CloseWindow(); // Fecha a janela
		return 0;
	}
