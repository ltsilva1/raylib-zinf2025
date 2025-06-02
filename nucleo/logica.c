#include "logica.h"
#include "../game/monstro/monstro.h"
#include "../game/jogador/jogador.h"


void processarLogica(Jogo *jogo) {
    moveMonstro(jogo->monstro, 10, &jogo->mapa);
    pegaEspada(&jogo->jogador, &jogo->mapa);
    pegaVida(&jogo->jogador, &jogo->mapa);

}
