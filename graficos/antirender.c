//
// Created by lucas on 24/06/2025.
//

#include "antirender.h"

void descarregarTexturas(Jogo* jogo) {
    // Descarrega as texturas dos menus
    UnloadTexture(jogo->menuTex.fundoinical);
    UnloadTexture(jogo->menuTex.fundobasico);

    // Descarrega as texturas do jogador parado
    UnloadTexture(jogo->jogador.tex.sul);
    UnloadTexture(jogo->jogador.tex.norte);
    UnloadTexture(jogo->jogador.tex.leste);
    UnloadTexture(jogo->jogador.tex.oeste);

    // Descarrega as texturas do jogador movendo
    UnloadTexture(jogo->jogador.animtex.movTexNorte);
    UnloadTexture(jogo->jogador.animtex.movTexSul);
    UnloadTexture(jogo->jogador.animtex.movTexLeste);
    UnloadTexture(jogo->jogador.animtex.movTexOeste);

    // Descarrega as texturas do ataque da espada
    UnloadTexture(jogo->jogador.texEsp.cabo);
    UnloadTexture(jogo->jogador.texEsp.meio);
    UnloadTexture(jogo->jogador.texEsp.ponta);

    //Descarrega as texturas das paredes
    UnloadTexture(jogo->mapa.texparede.var0);
    UnloadTexture(jogo->mapa.texparede.var1);

    //Descarrega as texturas do chão
    UnloadTexture(jogo->mapa.chao[0]);
    UnloadTexture(jogo->mapa.chao[1]);

    //Descarrega as texturas dos inimigos
    UnloadTexture(jogo->monstrosTex.norte);
    UnloadTexture(jogo->monstrosTex.sul);
    UnloadTexture(jogo->monstrosTex.oeste);
    UnloadTexture(jogo->monstrosTex.leste);

    //Descarrega as texturas dos itens do mapa
    UnloadTexture(jogo->itemTex.vidaTex);
    UnloadTexture(jogo->itemTex.espadaTex);

}
