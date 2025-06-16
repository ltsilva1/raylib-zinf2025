#include "placar.h"

#include <stdio.h>

void salvaPlacar (Jogo* jogo) {
    FILE* f;

    f = fopen("ranking.bin", "wb");

    if (f == NULL) {
        printf("ERRO na abertura da leitura do placar");
    }

    fwrite(jogo->score, sizeof(Score), 5, f);

    fclose(f);
}

void lePlacar (Jogo* jogo) {
    FILE* f;

    f = fopen("ranking.bin", "rb");

    if (f == NULL) {
        for (int i = 0; i < 5; ++i) {
            snprintf(jogo->score[i].nome, 20, "Jogador %d", 1 + i);
            jogo->score[i].score = 0;
        }
        salvaPlacar(jogo);
        return;
    }
    fread(jogo->score, sizeof(Score), 5, f);
    fclose(f);
}

void ordenaPlacar(Score placar[]) {
    Score aux;

    for (int j = 0; j < 5 - 1; j++) {
        for (int i = 0; i < 5 - 1 - j; i++) {
            if (placar[i].score < placar[i+1].score) {
                aux = placar[i];
                placar[i] = placar[i+1];
                placar[i+1] = aux;
            }
        }
    }
}

void atualizaPlacar (Jogo* jogo) {
    if (jogo->jogador.pontuacaoTotal > jogo->score[5-1].score) {
        printf("--- ATUALIZANDO PLACAR ---\n"); //
        printf("Placar ANTES da atualizacao:\n");//
        for (int k=0; k<5; k++) { printf("  %d. %s - %d\n", k, jogo->score[k].nome, jogo->score[k].score); } //

        snprintf(jogo->score[5 - 1].nome, 20, "HEROI");
        jogo->score[5 - 1].score = jogo->jogador.pontuacaoTotal;

        printf("Placar APOS inserir novo score (antes de ordenar):\n"); //
        for (int k=0; k<5; k++) { printf("  %d. %s - %d\n", k, jogo->score[k].nome, jogo->score[k].score); } //
        ordenaPlacar(jogo->score);

        printf("Placar APOS ordenar:\n");//
        for (int k=0; k<5; k++) { printf("  %d. %s - %d\n", k, jogo->score[k].nome, jogo->score[k].score); } //
        salvaPlacar(jogo);
        printf("--------------------------\n"); //
    }


}

int EhNovoRecorde(const Jogo* jogo) {
    if (jogo->jogador.pontuacaoTotal > jogo->score[5 - 1].score) {
        return 1;
    }
    return 0;


}
