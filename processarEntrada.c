//
// Created by lucas on 26/05/2025.
//

#include "processarEntrada.h"

#include "raylib.h"
#include "external/miniaudio.h"

void moveJogador(Jogador* jogador, /*MAPA AQUI*/ int direcaoX, int direcaoY);

void processarEntrada(Jogo *jogo) {
    if (IsKeyPressed(KEY_LEFT)) {moveJogador(&jogo->jogador, -1, 0);}
    if (IsKeyPressed(KEY_RIGHT)) {moveJogador(&jogo->jogador, 1, 0);}
    if (IsKeyPressed(KEY_UP)) {moveJogador(&jogo->jogador, 0, -1);}
    if (IsKeyPressed(KEY_DOWN)) {moveJogador(&jogo->jogador, 0, 1);}

}

void moveJogador(Jogador* jogador, /*MAPA AQUI*/ int direcaoX, int direcaoY) {
    jogador->pos.x += direcaoX;
    jogador->pos.y += direcaoY;


    
}