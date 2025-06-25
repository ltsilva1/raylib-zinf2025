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

        if (!carregaMapa(jogo)) { // Se não conseguir carregar o próximo mapa, assume que aquele foi o último do jogo
                if (EhNovoRecorde(jogo) == 1) {
                        jogo->estado = ENTRANDO_NOME_RANKING; // Se for recorde, vai para a tela de entrada de nome
                        jogo->contadorNome = 0; // Prepara o buffer para o jogador digitar
                        jogo->nomeBuffer[0] = '\0';
                } else {
                        jogo->estado = VITORIA; // Se não for recorde, vai para a tela de vitória normal
                }
        } else {
                // Caso consiga carregar o próximo mapa, reinicializa o jogador e os monstros dele
                inicializarMonstros(jogo);
                inicializarJogador(jogo);
        }
}
