#include "logica.h"

#include "startup.h"
#include "../game/monstro/monstro.h"
#include "../game/jogador/jogador.h"
#include "../game/jogador/espada.h"
#include "../game/mapa/avancanivel.h"
#define MAX_MONSTROS 10



void processarLogica(Jogo *jogo) {
    if (jogo->estado == JOGANDO) {
        float deltaTime = GetFrameTime();
        moveMonstro(&jogo->jogador, jogo->mapa.monstro, MAX_MONSTROS, &jogo->mapa, deltaTime);

        pegaEspada(&jogo->jogador, &jogo->mapa);

        pegaVida(&jogo->jogador, &jogo->mapa);

        danoJogador(&jogo->jogador, jogo->mapa.monstro);
        if (jogo->jogador.vidas <= 0) {
            jogo->estado = FIM_DE_JOGO;
            return;
        }
        if (jogo->jogador.instantesInvencibilidade > 0) {
            jogo->jogador.instantesInvencibilidade -= deltaTime;
        }

        ataqueEspada(jogo);

        int monstrosVivos = 0;
        for (int i = 0; i < MAX_MONSTROS; i++) {
            if (jogo->mapa.monstro[i].vivo == 1) {
                monstrosVivos++;
            }
        }

        jogo->mapa.numMonstros = monstrosVivos;

        if (jogo->mapa.numMonstros == 0) {
            avancaNivel(jogo);
        }
    } else return;
}
