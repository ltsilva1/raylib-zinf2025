//
// Created by lucas on 26/05/2025.
//

#include "../nucleo/startup.h"
#include "../game/mapa/mapa.h"
#include "../nucleo/placar.h"
#include <stdlib.h>
#include <time.h>

void Inicializar(Jogo *jogo) {
    // Estabelece os valores para inicialização ou reinicialização do jogo
    carregarTexturas(jogo);
    srand(time(NULL));
    jogo->jogador.pontuacaoTotal = 0;
    jogo->estado = MENU;
    jogo->nivelAtual = 1;
    jogo->seletorMenu = 0;
    jogo->modoDebug = false;
    lePlacar(jogo);
    carregaMapa(jogo);
    inicializarMonstros(jogo);
    inicializarJogador(jogo);

}
void inicializarJogador(Jogo *jogo) {
    // Status básicos
    jogo->jogador.vidas = 3;
    jogo->jogador.vivo = true;
    jogo->jogador.dir = BAIXO;
    jogo->jogador.pos.x = jogo->mapa.posInicialJogador.x;
    jogo->jogador.pos.y = jogo->mapa.posInicialJogador.y;

    // Status de combate
    for (int i = 0; i < 3; ++i) {
        jogo->jogador.tilesAtaque[i].x = -1;
        jogo->jogador.tilesAtaque[i].y = -1;
    }
    jogo->jogador.temEspada = 0;
    jogo->jogador.instantesEspada = 0;
    jogo->jogador.instantesInvencibilidade = 0;


    // Status da animação de movimento do jogador
    jogo->jogador.estaSeMovendo = false;
    jogo->jogador.progressoMovimento = 0.0f;
    jogo->jogador.ultimoEixoMovido = 0;

    // Define origem e destino para a posição inicial para evitar dados lixo
    jogo->jogador.posOrigem = jogo->jogador.pos;
    jogo->jogador.posDestino = jogo->jogador.pos;
    jogo->jogador.frameAtual = 0;

}

void carregarTexturas(Jogo* jogo) {
    // Carrega as texturas dos menus
    jogo->menuTex.fundoinical = LoadTexture(".recursos/menu/fundoinicial.png");
    jogo->menuTex.fundobasico = LoadTexture(".recursos/menu/fundobasico.png");

    // Carrega as texturas do jogador parado
    jogo->jogador.tex.sul = LoadTexture(".recursos/jogador/jogador_baixo.png");
    jogo->jogador.tex.norte = LoadTexture(".recursos/jogador/jogador_cima.png");
    jogo->jogador.tex.leste = LoadTexture(".recursos/jogador/jogador_direita.png");
    jogo->jogador.tex.oeste = LoadTexture(".recursos/jogador/jogador_esquerda.png");

    // Carrega as texturas do jogador movendo
    jogo->jogador.animtex.movTexNorte = LoadTexture(".recursos/jogador/animacoes/andando_cima.png");
    jogo->jogador.animtex.movTexSul = LoadTexture(".recursos/jogador/animacoes/andando_baixo.png");
    jogo->jogador.animtex.movTexLeste = LoadTexture(".recursos/jogador/animacoes/andando_direita.png");
    jogo->jogador.animtex.movTexOeste = LoadTexture(".recursos/jogador/animacoes/andando_esquerda.png");

    // Carrega as texturas do ataque da espada
    jogo->jogador.texEsp.cabo = LoadTexture(".recursos/ataque/espada_cabo.png");
    jogo->jogador.texEsp.meio = LoadTexture(".recursos/ataque/espada_meio.png");
    jogo->jogador.texEsp.ponta = LoadTexture(".recursos/ataque/espada_ponta.png");

    //Carrega as texturas das paredes
    jogo->mapa.texparede.var0 = LoadTexture(".recursos/paredes/arbustoparede.png");
    jogo->mapa.texparede.var1 = LoadTexture(".recursos/paredes/arbustoparede_deserto.png");

    //Carrega as texturas do chão
    jogo->mapa.chao[0] = LoadTexture(".recursos/chao/chao_commato.png");
    jogo->mapa.chao[1] = LoadTexture(".recursos/chao/chao_semmato.png");

    //Carrega as texturas dos inimigos
    jogo->monstrosTex.norte = LoadTexture(".recursos/inimigos/inimigo_cima.png");
    jogo->monstrosTex.sul = LoadTexture(".recursos/inimigos/inimigo_baixo.png");
    jogo->monstrosTex.oeste = LoadTexture(".recursos/inimigos/inimigo_direita.png");
    jogo->monstrosTex.leste = LoadTexture(".recursos/inimigos/inimigo_esquerda.png");

    //Carrega as texturas dos itens do mapa
    jogo->itemTex.vidaTex = LoadTexture(".recursos/items/vida.png");
    jogo->itemTex.espadaTex = LoadTexture(".recursos/items/espada.png");

}

void inicializarMonstros(Jogo* jogo) {
    for (int i = 0; i < jogo->mapa.numMonstrosInicial; ++i) {
        jogo->mapa.monstro[i].pontuacao = rand() % 100 + 1; // Define um valor aleatório para a pontuação do monstro
        jogo->mapa.monstro[i].vivo = 1;
        jogo->mapa.monstro[i].dir = (rand() % 4); // Define uma direção aleatória no spawn

        // Garante que o monstro não está no meio de uma sequência de passos quando começa
        jogo->mapa.monstro[i].passosRestantes = 0;

        // Define um tempo inicial pequeno para que os monstros comecem a se mover em momentos diferentes.
        jogo->mapa.monstro[i].tempoParaMover = (rand() % 101) / 100.0f;

    }

    for (int i = jogo->mapa.numMonstrosInicial; i < 10; ++i)
        jogo->mapa.monstro[i].vivo = 0; // Garante que nenhum monstro adicional além dos inimigos do mapa seja utilizado
}

