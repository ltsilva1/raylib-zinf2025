#include <stdio.h>
#include <stdlib.h>

#include "definicoes.h"

void carregaMapa (Jogo* meuJogo) {
    //char mapa[16][24+1];  // 24 caracteres + '\0'
    FILE* f;

    f = fopen("mapa01.txt", "r");
    if (f == NULL) {
        exit(1);
    }

    for (int i = 0; i < 16; i++) {
        fgets(meuJogo->mapa.mapa[i], 24+2, f);  // lê até 24 caracteres + '\n' + '\0'
    }
    fclose(f);

    for (int i = 0; i < 16; i++) {
        // Imprime linha como string
        for (int j = 0; j < 24; j++) {
            char c = meuJogo->mapa.mapa[i][j];
            if (c == '\n' || c == '\0')
                break;
            printf("%c", c);
        }
        printf("\n");
    }
}
