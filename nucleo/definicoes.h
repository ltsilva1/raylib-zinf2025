//
// Created by lucas on 26/05/2025.
//
#define LARGURA 1200
#define ALTURA 860
#define CASA 50
#define ALTURA_HUD 60
#define MAX_NOME_JOGADOR 20
#define DURACAO_MOVIMENTO 0.12f // Duração em segundos para mover uma casa.
#define JOGADOR_NUM_FRAMES 7       // 7 frames de animação por direção
#define JOGADOR_TEMPO_POR_FRAME 0.1f //Animação troca de frame a cada 0.1 segundos

#include "raylib.h"
#include <stdbool.h>

#ifndef DEFINICOES_H
#define DEFINICOES_H

typedef struct { // Estrutura básica de scores
    char nome[20];
    int score;
} Score;

typedef enum { // Conjunto de estados do jogo
    JOGANDO,
    MENU,
    PAUSADO,
    FIM_DE_JOGO,
    VITORIA,
    SCOREBOARDS_TABELA,
    ENTRANDO_NOME_RANKING
} Estado;

typedef struct { // Estrutura de posição de determinado elemento na grade
    int x;
    int y;
} PosicaoGrade;

typedef struct { // Estrutura com texturas para cada orientação do jogador/monstro
    Texture2D norte;
    Texture2D sul;
    Texture2D leste;
    Texture2D oeste;
} TexturasOri;

typedef struct { // Estrutura com texturas para cada parte da espada
    Texture2D cabo;
    Texture2D meio;
    Texture2D ponta;
} TexturaAtaquePartes;

typedef struct { // Estrutura com textura dos items do jogo
    Texture2D vidaTex;
    Texture2D espadaTex;
} TexturasItens;

typedef struct { // Estrutura com textura das variantes das paredes
    Texture2D var0;
    Texture2D var1;
} TexturasParede;

typedef struct { // Estrutura com textura dos fundos dos menus
    Texture2D fundoinical;
    Texture2D fundobasico;
} TexturasMenu;

typedef struct { // Estrutura com textura das animações da spritesheet
    Texture2D movTexNorte;
    Texture2D movTexSul;
    Texture2D movTexLeste;
    Texture2D movTexOeste;
} Animacoes;

typedef enum { // Conjunto de orientações
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA,
} Orientacao;


typedef struct { // Estrutura principal do jogador
    // Características básicas
    char nome[20];
    PosicaoGrade pos;
    Orientacao dir;
    TexturasOri tex;
    Animacoes animtex;
    int vidas;
    int pontuacaoTotal;
    bool temEspada;
    bool vivo;

    // Elementos de combate
    TexturaAtaquePartes texEsp;
    float instantesInvencibilidade;
    float instantesEspada;
    PosicaoGrade tilesAtaque[3];

    // Elementos de animação
    bool estaSeMovendo; // 0 para parado, 1 para se movendo
    PosicaoGrade posOrigem; // De qual casa o movimento começou
    PosicaoGrade posDestino; // Para qual casa o movimento vai
    int ultimoEixoMovido; // 0 para horizontal (X), 1 para vertical (Y) (Utilizado no buffer de movimentação)
    float progressoMovimento; // Um timer que vai de 0.0 até a duração do movimento
    int frameAtual;
} Jogador;

typedef struct { // Estrutura principal do monstro
    PosicaoGrade pos;
    Orientacao dir;
    int pontuacao;
    bool vivo;
    int passosRestantes;
    float tempoParaMover;
} Monstro;

typedef struct { // Estrutura principal do mapa atual
    char mapa[16][24];
    int chaoVariacao[16][24];
    int paredeVariacao[16][24];
    PosicaoGrade posInicialJogador;
    PosicaoGrade posInicialEspada;
    Monstro monstro[10];
    int numMonstros;
    int numMonstrosInicial;
    bool espadaPegada;
    PosicaoGrade vidasExtras[5];
    int vidasPegadas[5];
    int numVidasExtras;
    TexturasParede texparede;
    Texture2D chao[2];
} Mapa;

typedef struct { // Estrutura central do programa (maior parte das funções a utiliza como parâmetro)
    Estado estado;
    Score score[5];
    int seletorMenu;
    Jogador jogador;
    TexturasOri monstrosTex;
    Mapa mapa;
    int nivelAtual;
    TexturasItens itemTex;
    TexturasMenu menuTex;
    bool modoDebug;

    // CAMPOS PARA INPUT DE NOME
    char nomeBuffer[MAX_NOME_JOGADOR + 1]; // Buffer para guardar o nome (+1 para o '\0')
    int contadorNome; // Quantos caracteres já foram digitados
} Jogo;

#endif //DEFINICOES_H
