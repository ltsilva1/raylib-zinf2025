#include "logica.h"

#include "startup.h"
#include "../game/monstro/monstro.h"
#include "../game/jogador/jogador.h"
#include "../game/jogador/espada.h"
#include "../game/mapa/avancanivel.h"



void processarLogica(Jogo *jogo) {
    if (jogo->estado == JOGANDO) {
        float deltaTime = GetFrameTime();
        moveMonstro(&jogo->jogador, jogo->mapa.monstro, jogo->mapa.numMonstrosInicial, &jogo->mapa, deltaTime);

        pegaEspada(&jogo->jogador, &jogo->mapa);

        pegaVida(&jogo->jogador, &jogo->mapa);

        danoJogador(&jogo->jogador, jogo->mapa.monstro);

        if (jogo->jogador.vidas <= 0) {
            if (jogo->jogador.pontuacaoTotal > jogo->score[5 - 1].score) {
                // Se for, muda para a tela de entrada de nome
                jogo->estado = ENTRANDO_NOME_RANKING;
                // Prepara o buffer para uma nova entrada
                jogo->contadorNome = 0;
                jogo->nomeBuffer[0] = '\0';
            } else {
                jogo->estado = FIM_DE_JOGO;
            }
            return;
        }
        if (jogo->jogador.instantesInvencibilidade > 0) {
            jogo->jogador.instantesInvencibilidade -= deltaTime;
        }

        ataqueEspada(jogo);

        if (jogo->mapa.numMonstros == 0) {
            avancaNivel(jogo);
        }
    } else return;
}
