//
// Created by lucas on 07/06/2025.
//
#include "definicoes.h"
#include "startup.h"
#include "avancanivel.h"

#include "mapa.h"

void avancaNivel(Jogo* jogo) {
        ++jogo->nivelAtual;
        if (!carregaMapa(jogo)) {
                jogo->estado = FIM_DE_JOGO;
                return;
        }
        inicializarMonstrons(jogo);
        inicializarJogador(jogo);

}
