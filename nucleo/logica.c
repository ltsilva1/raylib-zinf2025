#include "logica.h"

#include "startup.h"
#include "../game/monstro/monstro.h"
#include "../game/jogador/jogador.h"
#include "../game/jogador/espada.h"
#include "../game/mapa/avancanivel.h"



void processarLogica(Jogo *jogo) {
    if (jogo->estado == JOGANDO) {
        float deltaTime = 0.0f;
        deltaTime = GetFrameTime();
        moveMonstro(&jogo->jogador, jogo->mapa.monstro, jogo->mapa.numMonstros, &jogo->mapa, deltaTime);

        pegaEspada(&jogo->jogador, &jogo->mapa);

        pegaVida(&jogo->jogador, &jogo->mapa);

        danoJogador(&jogo->jogador, jogo->mapa.monstro);
        if (jogo->jogador.vidas <= 0) {
            jogo->estado = FIM_DE_JOGO;
            inicializarJogador(jogo);
        }
        if (jogo->jogador.instantesInvencibilidade > 0) {
            jogo->jogador.instantesInvencibilidade -= deltaTime;
        }

        ataqueEspada(jogo);

        if (jogo->mapa.numMonstros == 0) {
            avancaNivel(jogo);
        }
    }
}
