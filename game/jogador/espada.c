//
// Created by lucas on 06/06/2025.
//

#include "espada.h"
#include "jogador.h"
#include "definicoes.h"

void ataqueEspada(Jogo* jogo) {
    if (jogo->jogador.instantesEspada > 0 && jogo->jogador.temEspada == true) {

        // Define uma posição base para o ataque. Por padrão, é a posição atual do jogador.
        PosicaoGrade baseDoAtaque = jogo->jogador.pos;

        // Se o jogador estiver no meio de uma animação de movimento, a base passa a ser a casa de destino do movimento
        if (jogo->jogador.estaSeMovendo)
            baseDoAtaque = jogo->jogador.posDestino;

        // O ataque possui três casas de alcance
        switch (jogo->jogador.dir) {
            case CIMA:
                for (int i = 0; i < 3; ++i) {
                    jogo->jogador.tilesAtaque[i].y = baseDoAtaque.y - 1 - i;
                    jogo->jogador.tilesAtaque[i].x = jogo->jogador.pos.x;
                }
                break;
            case BAIXO:
                for (int i = 0; i < 3; ++i) {
                    jogo->jogador.tilesAtaque[i].y = baseDoAtaque.y + 1 + i;
                    jogo->jogador.tilesAtaque[i].x = baseDoAtaque.x;
                }
                break;
            case ESQUERDA:
                for (int i = 0; i < 3; ++i) {
                    jogo->jogador.tilesAtaque[i].y = baseDoAtaque.y;
                    jogo->jogador.tilesAtaque[i].x = baseDoAtaque.x  - 1 - i;
                }
                break;
            case DIREITA:
                for (int i = 0; i < 3; ++i) {
                    jogo->jogador.tilesAtaque[i].y = baseDoAtaque.y;
                    jogo->jogador.tilesAtaque[i].x = baseDoAtaque.x  + 1 + i;
                }
                break;
        }
        for (int i = 0; i < 10; ++i) { // Elimina o monstro e soma sua pontuação caso esteja dentro das casas de ataque da espada
            if (jogo->mapa.monstro[i].vivo == 1) {
                for (int j = 0; j < 3; ++j) {
                    if (jogo->jogador.tilesAtaque[j].y == jogo->mapa.monstro[i].pos.y && jogo->jogador.tilesAtaque[j].x == jogo->mapa.monstro[i].pos.x) {
                        jogo->mapa.monstro[i].vivo = 0;
                        jogo->jogador.pontuacaoTotal += jogo->mapa.monstro[i].pontuacao;
                        --jogo->mapa.numMonstros;
                    }
                }
            }
        }
        jogo->jogador.instantesEspada -= GetFrameTime(); // Garante que o ataque da espada termine após um período
    }
    if (jogo->jogador.instantesEspada <= 0) { // Se a espada não estiver em ação, tire as casas de ataque do mapa
        for (int k = 0; k < 3; ++k) {
            jogo->jogador.tilesAtaque[k].y = -1;
            jogo->jogador.tilesAtaque[k].x = -1;
        }

    }

}
