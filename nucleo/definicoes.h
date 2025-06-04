//
// Created by lucas on 26/05/2025.
//
#define LARGURA 1200
#define ALTURA 800
#define CASA 50
#include "raylib.h"

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
    Texture2D norte;
    Texture2D sul;
    Texture2D leste;
    Texture2D oeste;
} Texturas;

typedef struct {
    char mapa[16][25];
    PosicaoGrade posInicialJogador;
    PosicaoGrade posInicialEspada;
    int espadaPegada;
    PosicaoGrade vidasExtras[5];
    int vidasPegadas[5];
    Texturas tex;
    Texture2D chao;

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
    Texturas tex;
    int vidas;
    int pontuacaoTotal;
    int temEspada; // bool
    int contatoMonstro; // bool

} Jogador;


typedef struct {
    PosicaoGrade pos;
    Orientacao dir;
    Texturas tex;
    int pontuacao;
    int vivo; // bool

} Monstro;

typedef struct {
    Estado estado;
    int seletorMenu;
    Jogador jogador;
    Monstro monstro[10];
    int numMonstrosAtual;
    Mapa mapa;
    int nivelAtual;
    Texture2D vidaTex;
    Texture2D espadaTex;

} Jogo;

#endif //DEFINICOES_H
