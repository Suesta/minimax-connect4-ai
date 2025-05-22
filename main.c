#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Connect4.h"
#include "Minimax.h"


int main(){

    int profunditat=2;//PER DEFECTE
    //CREA ESPAI PEL TAULER DE MARGES I PEL TAULER DE JOC
    char tauCh[2*F+1][2*C+1], tauler[F][C];

    srand(time(NULL));

    escullDificultat(&profunditat);
    iniciaTauC4(tauCh, tauler);
    playC4(tauCh, profunditat, tauler);
}
