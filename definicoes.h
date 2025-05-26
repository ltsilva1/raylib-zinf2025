//
// Created by lucas on 26/05/2025.
//
#define LARGURA 1200
#define ALTURA 800
#define CASA 50

#ifndef DEFINICOES_H
#define DEFINICOES_H

typedef struct {
    int x;
    int y;

} PosicaoGrade;

typedef struct {
    char mapa[16][25];

} Mapa;

typedef enum {
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA,

} Orientacao;

typedef struct {
    PosicaoGrade pos;
    Orientacao dir;


} Jogador;

typedef struct {
    Jogador jogador;
    Mapa mapa;

} Jogo;

#endif //DEFINICOES_H
