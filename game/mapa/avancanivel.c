//
// Created by lucas on 07/06/2025.
//
#include "definicoes.h"
#include "startup.h"
#include "avancanivel.h"
#include "placar.h"
#include "mapa.h"
#include "placar.h"

void avancaNivel(Jogo* jogo) {
        ++jogo->nivelAtual;

        if (!carregaMapa(jogo)) {
                // ...é vitória final! Agora verificamos se foi com recorde.
                if (EhNovoRecorde(jogo) == 1) {
                        jogo->estado = ENTRANDO_NOME_RANKING; // Se for recorde, VAI PARA A TELA DE ENTRADA DE NOME!
                        jogo->contadorNome = 0; // Prepara o buffer para o jogador digitar
                        jogo->nomeBuffer[0] = '\0';
                } else {
                        jogo->estado = VITORIA; // Se não for recorde, vai para a tela de vitória normal
                }
        }
        inicializarMonstros(jogo);
        inicializarJogador(jogo);
}
