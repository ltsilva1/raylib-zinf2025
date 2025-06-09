//
// Created by lucas on 07/06/2025.
//
#include "definicoes.h"
#include "startup.h"
#include "avancanivel.h"

#include "mapa.h"
#include "placar.h"

void avancaNivel(Jogo* jogo) {
        ++jogo->nivelAtual;
        if (!carregaMapa(jogo)) {
                jogo->estado = VITORIA;
                atualizaPlacar(jogo);
                return;
        }
        inicializarMonstrons(jogo);
        inicializarJogador(jogo);

}
