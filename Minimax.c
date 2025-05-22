#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Connect4.h"
#include "Minimax.h"

int randomChoice(int valor1, int valor2){

    int random_bit=rand()%2;//Nombre aleatori 0 o 1

    if(random_bit) return valor1;
    else return valor2;
}

int escollirCol(Node *arrel){

    int colMaxValor=numFill(arrel->tauler,0)-1;
    double maxValor=arrel->fills[0]->valor;

    if((arrel->n_fills)%2==0 && (arrel->n_fills)!=0)
    {
        double MaxValor1=arrel->fills[((arrel->n_fills)/2)-1]->valor, MaxValor2=arrel->fills[(arrel->n_fills)/2]->valor;

        if(MaxValor1==MaxValor2)
        {
            maxValor=MaxValor1;
            colMaxValor=numFill(arrel->tauler,randomChoice(((arrel->n_fills)/2)-1,(arrel->n_fills)/2))-1;
        }
        else if(MaxValor1>MaxValor2)
        {
            maxValor=MaxValor1;
            colMaxValor=numFill(arrel->tauler,((arrel->n_fills)/2)-1)-1;
        }
        else if(MaxValor1<MaxValor2)
        {
            maxValor=MaxValor2;
            colMaxValor=numFill(arrel->tauler,(arrel->n_fills)/2)-1;
        }
    }
    else if((arrel->n_fills)%2==1 && (arrel->n_fills)!=1)
    {
        double MaxValor1=arrel->fills[(((arrel->n_fills)-1)/2)-1]->valor, MaxValor2=arrel->fills[((arrel->n_fills)-1)/2]->valor, MaxValor3=arrel->fills[(((arrel->n_fills)-1)/2)+1]->valor;

        if(MaxValor2>=MaxValor3 && MaxValor2>=MaxValor1)
        {
            maxValor=MaxValor2;
            colMaxValor=numFill(arrel->tauler,((arrel->n_fills)-1)/2)-1;
        }
        else if(MaxValor1==MaxValor3)
        {
            maxValor=MaxValor1;
            colMaxValor=numFill(arrel->tauler,randomChoice((((arrel->n_fills)-1)/2)-1,(((arrel->n_fills)-1)/2)+1))-1;
        }
        else if(MaxValor3>MaxValor2 && MaxValor3>MaxValor1)
        {
            maxValor=MaxValor3;
            colMaxValor=numFill(arrel->tauler,(((arrel->n_fills)-1)/2)+1)-1;
        }
        else if(MaxValor1>MaxValor2 && MaxValor1>MaxValor3)
        {
            maxValor=MaxValor1;
            colMaxValor=numFill(arrel->tauler,(((arrel->n_fills)-1)/2)-1)-1;
        }
    }

    for(int i=0; i < arrel->n_fills; i++)
    {
        if(arrel->fills[i]->valor > maxValor)
        {
            maxValor=arrel->fills[i]->valor;//ESCULL LA COLUMNA DEL NIVELL 1 AMB VALOR MAXIM
            colMaxValor=numFill(arrel->tauler,i)-1;
        }
    }

return colMaxValor;
}

double estrategiaValors(Node *pare){

    double nouValorNode;
    if(pare->n_fills!=0)
    {
        nouValorNode=pare->fills[0]->valor;
        for(int i=1; i < pare->n_fills; i++)
        {
            if((pare->nivell)%2==0 && pare->fills[i]->valor  >  nouValorNode)  nouValorNode=pare->fills[i]->valor;
            else if((pare->nivell)%2==1 && pare->fills[i]->valor  <  nouValorNode)  nouValorNode=pare->fills[i]->valor;
        }
    }
    else return pare->valor;
return nouValorNode;//RETORNA EL VALOR DEL NODE SEGUINT L'ALGORITME MINIMAX REGULAR
}

int estableixJerarquia(int valorNodePare, int identificador){

    int valorNode;
    valorNode=valorNodePare*10+identificador;

return valorNode;//RETORNA L'IDENTIFICADOR UNIC PEL NODE ACTUAL
}

void copiaTauler(char tauPare[F][C],char tauFill[F][C]){
    for(int i=0;i<F;i++)
    {
        for(int j=0;j<C;j++)
        {
            tauFill[i][j]=tauPare[i][j];//COPIA EL TAULER PARE AL TAULER FILL
        }
    }
}

int colPlena(char tauler[F][C],int indicador){

    if(tauler[0][indicador]==' ') return 0;//COLUMNA LLIURE

return 1;//COLUMNA PLENA
}

int calculaNumFills(char tauler[F][C]){

    int contador=0;
    for(int i=0;i<C;i++)
    {
        if(colPlena(tauler,i)==0) contador++;//VA CALCULANT QUANTES COLUMNES LLIURES TE EL TAULER
    }
return contador;
}

int numFill(char tauler[F][C],int indicador){

    int contador=0;
    int identificador=indicador;
    for(int i=0; i<=indicador+contador; i++)//COMPROVA QUE NO HI HAGI COLUMNES PLENES ABANS DE LA DE L'INDICADOR DE LA SUPOSADA COLUMNA
    {
        if(colPlena(tauler,i)==1)
        {
            identificador++;//SI ALGUNA ESTA PLENA LLAVORS L'IDENTIFICADOR S'HA DE MOURE ENDAVANT
            contador++;//TOTES LES POSICIONS AVANCEN TANTES VEGADES COM COLUMNES PLENES HI HAGI
        }

    }
return identificador+1;//RETORNA L'IDENTIFICADOR UNIC D'AQUEST FILL
}

int fesTirada(char tau[F][C],int col, char nivellCh){

    int i=1;
    for(i=1; i<=F; i++)
    {
        if(tau[F-i][col]==' ')
        {
            tau[F-i][col]=nivellCh;//SIMULA LA TIRADA CORRESPONENT AL NODE ACTUAL, ACTUALITZANT EL TAULER
            break;
        }
    }
return F-i;
}

Node *crearNode(Node *pare,int nivell,int col,int profunditat){

    char nivellCh;
    int filaBona;
    Node *p=malloc(sizeof(Node));//CREEM EL NOU NODE

    p->nivell=nivell;//ESTABLIM EL NIVELL AL QUE PERTANY EL NODE ACTUAL
    //DISTINGIM ENTRE EL TIPUS DE JUGADOR QUE FA LA TIRADA EN EL NODE ACTUAL (DEPEN DEL NIVELL)
    if(nivell%2==1) nivellCh='O';
    else if(nivell%2==0) nivellCh='X';
    copiaTauler(pare->tauler,p->tauler);//FEM UNA COPIA DEL TAULER PER NO ALTERAR EL TAULER PARE

    //ACTUALITZEM EL TAULER PER TENIR L'ACTUAL AMB LA TIRADA CORRESPONENT
    filaBona=fesTirada(p->tauler, col-1, nivellCh);//ES GUARDA LA FILA ON S'HA LLENÇAT EN AQUEST NODE
    //COL ES L'IDENTIFICADOR DE LA COLUMNA A LA QUE ES LLENÇA PER SIMULAR LA TIRADA DEL NODE ACTUAL

    if(nivell==1 && verifyWinC4(p->tauler,filaBona,col-1,nivellCh,4)==1)
    {
        //VERIFICA SI AMB AQUESTA TIRADA GUANYA LA PARTIDA
        p->valor=1e6;

        p->n_fills=0;
        p->fills=NULL;
    }
    else if(nivellCh=='O' && verifyWinC4(p->tauler,filaBona,col-1,nivellCh,4)==1)
    {
        //VERIFICA SI AMB AQUESTA TIRADA GUANYA LA PARTIDA
        p->valor=1e6;

        p->n_fills=0;
        p->fills=NULL;
    }
    else if(nivellCh=='X' && verifyWinC4(p->tauler,filaBona,col-1,nivellCh,4)==1)
    {
        //VERIFICA SI AMB AQUESTA TIRADA PERD LA PARTIDA
        p->valor=-1e6;

        p->n_fills=0;
        p->fills=NULL;
    }
    else
    {
        //PASEM A CALCULAR ELS FILLS
        if(nivell<profunditat)
        {
            p->n_fills=calculaNumFills(p->tauler);//CALCULEM EL NUM DE FILLS DEL TAULER/NODE ACTUAL
            p->fills=malloc(p->n_fills * sizeof(Node *));//RESERVEM MEMORIA PELS FILLS D'AQUEST NODE
            //IDENTIFICADOR UNIC DEL NODE
            p->valor=estableixJerarquia((int)pare->valor,col);//col ES LA FUNCIO int numFill
        }
        else//SI ESTEM A L'ULTIM NIVELL NO CREEM MÉS FILLS
        {
            p->n_fills=0;
            p->fills=NULL;
            //F.HEURISTICA:
            p->valor=HeuristicaC4(pare->valor,p->tauler,filaBona,col-1,nivellCh);
        }
    }

return p;
}

void crearNivell(Node *pare,int nivell,int profunditat){

    if(nivell>profunditat) return;//SI S'ARRIBA AL NIVELL DELS NODES FULLA S'ATURA LA RECURSIVITAT PER AQUELLA BRANCA
    for(int i=0; i < pare->n_fills; i++)
    {
        pare->fills[i]=crearNode(pare,nivell,numFill(pare->tauler,i),profunditat);//CREEM ELS NODES DEL NIVELL ACTUAL
        crearNivell(pare->fills[i],nivell+1,profunditat);//COMENCEM A CREAR EL NIVELL SEGUENT DEL NODE FILL ACTUAL
    }
}

void creaArbre(Node *arrel,int profunditat){

    crearNivell(arrel,arrel->nivell+1,profunditat);//COMENCEM A GENERAR L'ARBRE PEL PRIMER NIVELL, A PARTIR DEL NODE ARREL JA CREAT
}

void recorrerArbreRecursiu(Node *p,int nivell,int profunditat){//QUITAR/PONER LOS PRINTS

    if(nivell>profunditat) return;

    p->valor=estrategiaValors(p);//PUJA ELS VALORS ALS PARES APLICANT L'ALGORITME MINIMAX ORDINARI

    //for(int j=0;j<nivell;j++) printf("  ");
    //printf("%g\n",p->valor);

    for(int i=0; i < p->n_fills; i++)
    {
        recorrerArbreRecursiu(p->fills[i],nivell+1,profunditat);
    }
}

void printeaArbreRecursiu(Node *p,int nivell,int profunditat){

    if(nivell>profunditat) return;

    for(int j=0;j<nivell;j++) printf("  ");
    printf("%g\n",p->valor);

    //PRINTEEM LA MATRIU DE CADA NODE
    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if(p->tauler[i][j]==' ') printf(" %c ", '*');
            else printf(" %c ", p->tauler[i][j]);
        }
    printf("\n");
    }
    for(int i=0; i < p->n_fills; i++)
    {
        printeaArbreRecursiu(p->fills[i],nivell+1,profunditat);
    }
}

void lliberaArbreRecursiu(Node *node){

    if(node==NULL) return;//COMPROVEM QUE NO ARRIBEM AL NIVELL DE SOTA DE L'ARBRE

    for(int i=0; i < node->n_fills; i++)
    {
        lliberaArbreRecursiu(node->fills[i]);//LLIBEREM TOTS ELS NODES DE L'ARBRE RECURSIVAMENT
    }
    free(node->fills);//LLIBEREM L'ESPAI RESERVAT PELS NODES DEL SEGUENT NIVELL
    free(node);//LLIBEREM L'ESPAI RESERVAT PEL NODE ACTUAL
}

void escullDificultat(int *profunditat){

    char dificulCh[20];
    int entradaValida=0;

    while(!entradaValida)
    {
        printf("\n\nEscull dificultat: easy, medium, hard: ");
        scanf("%19s", dificulCh);//POSEM SUFICIENTS CARACTERS PERQUE NO DONI ERROR
        if(strcmp(dificulCh,"easy")==0 || strcmp(dificulCh,"Easy")==0)
        {
            *profunditat=2;
            entradaValida=1;
        }
        else if(strcmp(dificulCh,"medium")==0 || strcmp(dificulCh,"Medium")==0)
        {
            *profunditat=4;
            entradaValida=1;
        }
        else if(strcmp(dificulCh,"hard")==0 || strcmp(dificulCh,"Hard")==0)
        {
            *profunditat=6;
            entradaValida=1;
        }
        else
        {
            printf("\n\nDificultat no reconeguda\n");
        }
    }
}

int fMinimax(int profunditat, char taulerInicial[F][C]){

    int col=0;
    //CREAR ARBRE FINS AL NIVELL DESITJAT
    Node *arrel=malloc(sizeof(Node));
    arrel->n_fills=calculaNumFills(taulerInicial);
    arrel->fills=malloc(arrel->n_fills * sizeof(Node *));
    copiaTauler(taulerInicial, arrel->tauler);//COPIEM EL TAULER ACTUAL PER TENIRLO AL NODE ARREL
    arrel->valor=0;//FIXEM VALOR INICIAL DE L'ARREL DE L'ARBRE, 0 PER DEFECTE
    arrel->nivell=0;//FIXEM EL NIVELL DE L'ARREL COM EL NIVELL 0

    creaArbre(arrel,profunditat);//L'ARBRE JA ES CREA AMB ELS NODES FULLA AVALUATS EN LA FUNCIO HEURISTICA

    printf("\n\n\n\n\n\n");
    //printeaArbreRecursiu(arrel,0,profunditat);//SERVEIX PER VEURE EL VALOR ORIGINAL DELS NODES ABANS DE PUJAR ELS VALORS ALS PARES
    printf("\n\n\n\n\n\n");

    //PUJA ELS VALORS ALS PARES, S'APLICA FINS QUE S'HAN PUJAT ELS VALORS AL NIVELL 0 O ARREL
    for(int i=1;i<=profunditat;i++)
    {
        recorrerArbreRecursiu(arrel,0,profunditat);
        //printf("\n\n\n\n\n\n");
        //printf("\n\n\n\n\n\n");
    }

    col=escollirCol(arrel);//S'AGAFA LA COLUMNA LLIURE AMB VALOR MAXIM DEL NIVELL 1

    lliberaArbreRecursiu(arrel);//ESBORRAR L'ARBRE PER ALLIBERAR MEMORIA

return col+1;
}

