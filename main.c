#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"
#include "nucleo/definicoes.h"
#include "nucleo/startup.h"
#include "graficos/render.h"
#include "input/processarEntrada.h"
#include "nucleo/logica.h"
#include "antirender.h"

int main() {
	Jogo zinf;

	InitWindow(LARGURA, ALTURA, "Morde & Assopra"); // Inicializa janela, com certo tamanho e titulo
	SetTargetFPS(60);// Ajusta a janela para 60 frames por segundo

	/* Inicializa a nossa estrutura principal, carregando o mapa, texturas
	 * e as outras estruturas auxiliares (jogador, monstros, etc.) */
	Inicializar(&zinf);

	/* O LOOP PRINCIPAL: Enquanto a janela estiver aberta, todas as operações do programa são executadas sequencialmente
	 * pelas três funções principais que gerenciam entrada, processamento e renderização, nessa ordem. */
	while (!WindowShouldClose()) {

		processarEntrada(&zinf); // Comandos de entrada

		processarLogica(&zinf); // Processamento lógico

		desenhaJogo(&zinf); // Gráficos (raylib)

	}

	descarregarTexturas(&zinf); // Libera as texturas carregadas
	CloseWindow(); // Fecha a janela
	return 0;
	}
