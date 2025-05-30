//
// Created by lucas on 26/05/2025.
//
#define LARGURA 1200
#define ALTURA 800
#define CASA 50

#ifndef DEFINICOES_H
#define DEFINICOES_H

typedef enum {
    JOGANDO,
    MENU,
    PAUSADO


} Estado;

typedef struct {
    int x;
    int y;

} PosicaoGrade;

typedef struct {
    char mapa[16][25];
    PosicaoGrade posInicialJogador;

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
    Estado estado;
    Jogador jogador;
    Mapa mapa;
    int nivelAtual;

} Jogo;

typedef struct {
    PosicaoGrade pos;
    Orientacao ori;
    int pontuacao;
}Monstro;

#endif //DEFINICOES_H
