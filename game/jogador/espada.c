//
// Created by lucas on 06/06/2025.
//

#include "espada.h"
#include "jogador.h"
#include "definicoes.h"

void ataqueEspada(Jogo* jogo) {
    if (jogo->jogador.instantesEspada > 0 && jogo->jogador.temEspada == true) {
        switch (jogo->jogador.dir) {
            case CIMA:
                for (int i = 0; i < 3; ++i) {
                    jogo->jogador.tilesAtaque[i].y = jogo->jogador.pos.y - 1 - i;
                    jogo->jogador.tilesAtaque[i].x = jogo->jogador.pos.x;
                }
                break;
            case BAIXO:
                for (int i = 0; i < 3; ++i) {
                    jogo->jogador.tilesAtaque[i].y = jogo->jogador.pos.y + 1 + i;
                    jogo->jogador.tilesAtaque[i].x = jogo->jogador.pos.x;
                }
                break;
            case ESQUERDA:
                for (int i = 0; i < 3; ++i) {
                    jogo->jogador.tilesAtaque[i].y = jogo->jogador.pos.y;
                    jogo->jogador.tilesAtaque[i].x = jogo->jogador.pos.x  - 1 - i;
                }
                break;
            case DIREITA:
                for (int i = 0; i < 3; ++i) {
                    jogo->jogador.tilesAtaque[i].y = jogo->jogador.pos.y;
                    jogo->jogador.tilesAtaque[i].x = jogo->jogador.pos.x  + 1 + i;
                }
                break;
        }
        for (int i = 0; i < 10; ++i) {
            if (jogo->mapa.monstro[i].vivo == 1) {
            for (int j = 0; j < 3; ++j) {
                if (jogo->jogador.tilesAtaque[j].y == jogo->mapa.monstro[i].pos.y && jogo->jogador.tilesAtaque[j].x == jogo->mapa.monstro[i].pos.x) {
                    jogo->mapa.monstro[i].vivo = 0;
                    jogo->jogador.pontuacaoTotal += jogo->mapa.monstro[i].pontuacao;
                    ;;--jogo->mapa.numMonstros;
                }
            }
            }
        }
        jogo->jogador.instantesEspada -= GetFrameTime();
    }
    if (jogo->jogador.instantesEspada <= 0) {
        for (int k = 0; k < 3; ++k) {
            jogo->jogador.tilesAtaque[k].y = -1;
            jogo->jogador.tilesAtaque[k].x = -1;
        }

    }

}
