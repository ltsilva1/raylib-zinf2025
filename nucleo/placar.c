#include "placar.h"

#include <stdio.h>

void salvaPlacar (Jogo* jogo) { // Salva o placar do jogo no arquivo binário
    FILE* f;

    f = fopen("ranking.bin", "wb");

    if (f == NULL) {
        printf("ERRO na abertura da leitura do placar");
    }

    fwrite(jogo->score, sizeof(Score), 5, f);

    fclose(f);
}

void lePlacar (Jogo* jogo) { // Lê o placar do arquivo binário para o jogo
    FILE* f;

    f = fopen("ranking.bin", "rb");

    if (f == NULL) { // Caso o arquivo não exista, carrega para o jogo um placar genérico
        for (int i = 0; i < 5; ++i) {
            sprintf(jogo->score[i].nome, "Desafiante %d", 1 + i);
            jogo->score[i].score = 0;
        }
        salvaPlacar(jogo);
        return;
    }
    fread(jogo->score, sizeof(Score), 5, f);
    fclose(f);
}

void ordenaPlacar(Score placar[]) { // Ordena o placar do jogo
    Score aux;

    for (int j = 0; j < 5 - 1; j++) { // bubble-sort
        for (int i = 0; i < 5 - 1 - j; i++) {
            if (placar[i].score < placar[i+1].score) {
                aux = placar[i];
                placar[i] = placar[i+1];
                placar[i+1] = aux;
            }
        }
    }
}

void atualizaPlacar (Jogo* jogo) { // Atualiza o placar do jogo em caso de novo recorde
    if (jogo->jogador.pontuacaoTotal > jogo->score[5-1].score) {

        jogo->score[5 - 1].score = jogo->jogador.pontuacaoTotal;

        ordenaPlacar(jogo->score);

        salvaPlacar(jogo);

    }
}

int EhNovoRecorde(const Jogo* jogo) { // Função genérica para testar novo recorde
    if (jogo->jogador.pontuacaoTotal > jogo->score[5 - 1].score) {
        return 1;
    }
    return 0;


}
