 /*
if (movimentaOuNao == 2) {
       switch (novaDirRand) {
           case 0:
               deltaY = -1;
               monstro[i].dir = CIMA;
               break;
           case 1:
               deltaY = 1;
               monstro[i].dir = BAIXO;
               break;
           case 2:
               deltaX = 1;
               monstro[i].dir = DIREITA;
               break;
           case 3:
               deltaX = -1;
               monstro[i].dir = ESQUERDA;
               break;
       }
           }

       int proximoX = monstro[i].pos.x + deltaX;
       int proximoY = monstro[i].pos.y + deltaY;

       if (PosicaoValida(mapa, proximoX, proximoY)) { //Testa a colisão
           monstro[i].pos.x = proximoX;
           monstro[i].pos.y = proximoY;
       }

   }
   */
