#include "logica.h"

#include "startup.h"
#include "../game/monstro/monstro.h"
#include "../game/jogador/jogador.h"
#include "../game/jogador/espada.h"
#include "../game/mapa/avancanivel.h"



void processarLogica(Jogo *jogo) {
    if (jogo->estado == JOGANDO) { // Garante que a lógica só é processada quando o jogador estiver jogando
        float deltaTime = GetFrameTime();

        atualizarAnimacaoJogador(&jogo->jogador, deltaTime); // Avança a animação do jogador quando em movimento

        // Funções da lógica de jogabilidade
        moveMonstro(jogo->mapa.monstro, jogo->mapa.numMonstrosInicial, &jogo->mapa, deltaTime);
        pegaEspada(&jogo->jogador, &jogo->mapa);
        pegaVida(&jogo->jogador, &jogo->mapa);
        danoJogador(&jogo->jogador, jogo->mapa.monstro);
        ataqueEspada(jogo);

        // Morte do jogador
        if (jogo->jogador.vidas <= 0) {
            jogo->jogador.vivo = false;
            if (jogo->jogador.pontuacaoTotal > jogo->score[5 - 1].score) {
                // Se a pontuação atual for maior que a última do placar, muda para a tela de entrada de nome
                jogo->estado = ENTRANDO_NOME_RANKING;
                // Prepara o buffer para uma nova entrada
                jogo->contadorNome = 0;
                jogo->nomeBuffer[0] = '\0';
            } else {
                jogo->estado = FIM_DE_JOGO; // Caso não seja, apenas muda para a tela de fim de jogo
            }
            return;
        }
        if (jogo->jogador.instantesInvencibilidade > 0) {
            jogo->jogador.instantesInvencibilidade -= deltaTime; // Momentos de invencibilidade após receber um ataque
        }

        if (jogo->mapa.numMonstros == 0) {
            avancaNivel(jogo); // Se não houver mais monstros vivos no mapa, avança de nível
        }
    } else return; // Não processa a lógica caso o jogador não esteja jogando
}
