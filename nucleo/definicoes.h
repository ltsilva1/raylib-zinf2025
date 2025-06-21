//
// Created by lucas on 26/05/2025.
//
#define LARGURA 1200
#define ALTURA 860
#define CASA 50
#define ALTURA_HUD 60
#define MAX_NOME_JOGADOR 20
#include "raylib.h"
#include <stdbool.h>

#ifndef DEFINICOES_H
#define DEFINICOES_H

typedef struct {
    char nome[20];
    int score;
} Score;

typedef enum {
    JOGANDO,
    MENU,
    PAUSADO,
    FIM_DE_JOGO,
    VITORIA,
    SCOREBOARDS_TABELA,
    ENTRANDO_NOME_RANKING
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
    Texture2D fundoinical;
} TexturasMenu;

typedef enum {
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA,
} Orientacao;


typedef struct {
    char nome[20];
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
    float tempoParaJogadorMover; //????????????????? OQ CARALHOS É ISSO GABRIEL
    //bool estaSeMovendo; // 0 para parado, 1 para se movendo
    //PosicaoGrade posOrigem; // De qual casa o movimento começou
    //PosicaoGrade posDestino; // Para qual casa o movimento vai
    //float progressoMovimento; // Um timer que vai de 0.0 até a duração do movimento
} Jogador;

typedef struct {
    PosicaoGrade pos;
    Orientacao dir;
    Texturas tex;
    int pontuacao;
    int vivo; // bool
    int passosRestantes;
    float tempoParaMover;
} Monstro;

typedef struct {
    char mapa[16][24];
    int chaoVariacao[16][24];
    PosicaoGrade posInicialJogador;
    PosicaoGrade posInicialEspada;
    Monstro monstro[10];
    int numMonstros;
    int numMonstrosInicial;
    bool espadaPegada;
    PosicaoGrade vidasExtras[5];
    int vidasPegadas[5];
    int numVidasExtras;
    Texturas tex;
    Texture2D chao[2];
} Mapa;

typedef struct {
    Estado estado;
    Score score[5];
    int seletorMenu;
    Jogador jogador;
    Mapa mapa;
    int nivelAtual;
    Texture2D vidaTex;
    Texture2D espadaTex;
    TexturasMenu menuTex;
    bool modoDebug;
    // { CAMPOS PARA INPUT DE NOME }
    char nomeBuffer[MAX_NOME_JOGADOR + 1]; // Buffer para guardar o nome (+1 para o '\0')
    int contadorNome; // Quantos caracteres já foram digitados
} Jogo;

#endif //DEFINICOES_H
