//
// Created by lucas on 26/05/2025.
//

#include "logica.h"

void processarLogica(Jogo *jogo) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if (jogo->mapa.mapa[i][j] == 'J') {
                jogo->jogador.pos.x = i;
                jogo->jogador.pos.y = j;
                break;
            }
        }
    }



}