//
// Created by lucas on 26/05/2025.
//
#define LARGURA 1200
#define ALTURA 860
#define CASA 50
#define ALTURA_HUD 60
#include "raylib.h"
#include <stdbool.h>

#ifndef DEFINICOES_H
#define DEFINICOES_H

typedef enum {
    JOGANDO,
    MENU,
    PAUSADO,
    FIM_DE_JOGO
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
    float instantesInvencibilidade;
    float instantesEspada;
    PosicaoGrade tilesAtaque[3];
} Jogador;

typedef struct {
    PosicaoGrade pos;
    Orientacao dir;
    Texturas tex;
    int pontuacao;
    int vivo; // bool
    int passosRestantes;
} Monstro;

typedef struct {
    char mapa[16][25];
    PosicaoGrade posInicialJogador;
    PosicaoGrade posInicialEspada;
    Monstro monstro[10];
    int numMonstros;
    bool espadaPegada;
    PosicaoGrade vidasExtras[5];
    int vidasPegadas[5];
    Texturas tex;
    Texture2D chao;
} Mapa;

typedef struct {
    Estado estado;
    int seletorMenu;
    Jogador jogador;
    Mapa mapa;
    int nivelAtual;
    Texture2D vidaTex;
    Texture2D espadaTex;
    bool modoDebug;
} Jogo;

#endif //DEFINICOES_H
