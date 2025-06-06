#include "logica.h"

#include "startup.h"
#include "../game/monstro/monstro.h"
#include "../game/jogador/jogador.h"
#include "../game/jogador/espada.h"



void processarLogica(Jogo *jogo) {
            moveMonstro(&jogo->jogador, jogo->monstro, 10, &jogo->mapa);
            pegaEspada(&jogo->jogador, &jogo->mapa);
            pegaVida(&jogo->jogador, &jogo->mapa);
            danoJogador(&jogo->jogador, jogo->monstro);
            if (jogo->jogador.vidas <= 0) {
                jogo->estado = FIM_DE_JOGO;
                inicializarJogador(jogo);
            }
            if (jogo->jogador.instantesInvencibilidade > 0) {
                jogo->jogador.instantesInvencibilidade -= GetFrameTime();
            }
            ataqueEspada(jogo);

}
