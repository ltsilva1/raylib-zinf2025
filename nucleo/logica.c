#include "logica.h"
#include "../game/monstro/monstro.h"


void processarLogica(Jogo *jogo) {
    moveMonstro(jogo->monstro, 10, &jogo->mapa);

}
