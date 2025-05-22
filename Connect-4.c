#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Connect4.h"
#include "Minimax.h"

int posicioLliure(int col, char tauler[F][C]){

    for(int i=1;i<=F;i++)
    {
        if(tauler[F-i][col]==' ') return F-i;//RETORNA LA FILA DE LA POSICIO LLIURE PER TIRAR
    }
return -2;//SIGNIFICA QUE LA COLUMNA ESTA PLENA
}

void iniciaTauC4(char tauCh[2*F+1][2*C+1], char tauler[F][C]){//ACTIVAR PER JUGAR DOS HUMANS

    //CREA ELS FORATS DEL TAULER ON ES POSARAN LES FITXES
    for(int i=0;i<F;i++)
    {
        for(int j=0;j<C;j++)
        {
            tauCh[2*i+1][2*j+1]=' ';
            tauler[i][j]=' ';
        }
    }
    //CREA ELS MARGES DEL TAULER
    for(int i=0;i<=F;i++)
    {
        for(int j=0;j<=C;j++)
        {
            if(i==0) tauCh[2*i][2*j]='.';
            else if(j==0 || j==C) tauCh[2*i][2*j]='*';
            else if(i==F) tauCh[2*i][2*j]='*';
            else tauCh[2*i][2*j]='+';
        }
    }
    for(int i=0;i<=F;i++)
    {
        for(int j=0;j<C;j++)
        {
            if(i==0) tauCh[2*i][2*j+1]=' ';
            else tauCh[2*i][2*j+1]='-';
        }
    }
    for(int i=0;i<F;i++)
    {
        for(int j=0;j<=C;j++)
        {
            tauCh[2*i+1][2*j]='|';
        }
    }
    //ACTIVAR SI ES VOL JUGAR 2 HUMANS
    printf("\n\n");
    //Posem numero a les columnes
    for(int i=0;i<C;i++)
    {
        printf("    %d ", i+1);
    }
    printf("\n");
    //Dibuixa el tauler
    for (int i = 0; i < F*2+1; i++)
    {
        for (int j = 0; j < C*2+1; j++)
        {
            printf(" %c ", tauCh[i][j]);
        }
    printf("\n");
    }
}

void actualitzaTauC4(char tauCh[2*F+1][2*C+1], int freeFil, int col, char jugador, char tauler[F][C]){

    //ACTUALITZEM EL TAULER AMB ELS MARGES (EL QUE ES PRINTEA)
    tauCh[2*freeFil+1][2*(col-1)+1]=jugador;
    //ACTUALITZEM EL TAULER PER PASAR-LO COM A TAULER DE LA SEGUENT ARREL
    tauler[freeFil][col-1]=jugador;

    printf("\n\n\n\n\n\n");
    //INDIQUEM L'ULTIMA TIRADA QUE S'HA FET
    printf("ULTIMA TIRADA Jugador '%c': COLUMNA %d\n\n",jugador,col);
    //POSEM NUMERO A LES COLUMNES PER TIRAR
    for(int i=0;i<C;i++)
    {
        printf("    %d ", i+1);
    }
    printf("\n");
    //PRINTEA EL TAULER AMB ELS MARGES ACTUALITZAT
    for (int i = 0; i < F*2+1; i++)
    {
        for (int j = 0; j < C*2+1; j++)
        {
            printf(" %c ", tauCh[i][j]);
        }
    printf("\n");
    }
}

int verifyWinC4(char tau[F][C], int fila, int col, char jugador, int linia){

    int mDu=1, mDd=1, sDu=1, sDd=1, u=1, d=1, r=1, l=1;

    if(tau[fila][col]==jugador)
    {
        //VERIFICAR FILES
        while(col-l>=0 && tau[fila][col-l]==jugador) l++;
        while(col+r<C && tau[fila][col+r]==jugador) r++;
        //VERIFICAR COLUMNES
        while(fila-d>=0 && tau[fila-d][col]==jugador) d++;
        while(fila+u<F && tau[fila+u][col]==jugador) u++;
        //VERIFICAR DIAGONAL SECUNDARIA
        while(fila+mDu<F && col-mDu>=0 && tau[fila+mDu][col-mDu]==jugador) mDu++;
        while(fila-mDd>=0 && col+mDd<C && tau[fila-mDd][col+mDd]==jugador) mDd++;
        //VERIFICAR DIAGONAL PRINCIPAL
        while(fila+sDu<F && col+sDu<C && tau[fila+sDu][col+sDu]==jugador) sDu++;
        while(fila-sDd>=0 && col-sDd>=0 && tau[fila-sDd][col-sDd]==jugador) sDd++;

        if(l+r>linia || u+d>linia || mDu+mDd>linia || sDu+sDd>linia) return 1;//VICTORIA DEL JUGADOR QUE HA FET L'ULTIMA TIRADA
        if(linia==4)
        {
            if(col-l>=0 && col+r<C && l+r>linia-1 && tau[fila][col-l]==' ' && tau[fila][col+r]==' ' && ((fila+1<F && tau[fila+1][col-l]!=' ') || fila+1==F) && ((fila+1<F && tau[fila+1][col+r]!=' ') || fila+1==F)) return 1;
            if(fila+mDu<F && col-mDu>=0 && fila-mDd>=0 && col+mDd<C && mDu+mDd>linia-1 && tau[fila+mDu][col-mDu]==' ' && tau[fila-mDd][col+mDd]==' ' && ((fila+mDu+1<F && tau[fila+mDu+1][col-mDu]!=' ') || fila+mDu+1==F) && (tau[fila-mDd+1][col+mDd]!=' ')) return 1;
            if(fila+sDu<F && col+sDu<C && fila-sDd>=0 && col-sDd>=0 && sDu+sDd>linia-1 && tau[fila+sDu][col+sDu]==' ' && tau[fila-sDd][col-sDd]==' ' && ((fila+sDu+1<F && tau[fila+sDu+1][col+sDu]!=' ') || fila+sDu+1==F) && (tau[fila-sDd][col-sDd]!=' ')) return 1;
            else return 0;
        }
        else return 0;//CONTINUA EL JOC
    }
    else return 0;//CONTINUA EL JOC
}

void playC4(char tauCh[2*F+1][2*C+1], int profunditat, char taulerActual[F][C]){

    int tirada=0, col=0, freeFil=0, columnaValida=0, linia=4;
    char jugador=' ';

    //JOC
    while(tirada<F*C)
    {
        //if(tirada%2==1) jugador='O';//ACTIVAR ESTA LINEA PARA JUGAR DOS HUMANOS
        if(tirada%2==1)//QUITAR ESTE IF PARA JUGAR DOS HUMANOS
        {
            jugador='O';
            col=fMinimax(profunditat, taulerActual);//fMinimax RETORNA LA COLUMNA ON TIRA L'ORDINADOR
        }
        else if(tirada%2==0)
        {
            jugador='X';
        //}//PARA JUGAR 2 HUMANOS ACTIVAR ESTA LLAVE DE CIERRE
            while(!columnaValida)
            {
                printf("\nJUGADOR '%c', escull una columna entre 1-%d: ", jugador, C);
                scanf("%d", &col);
                while(col>=1 && col<=C)//COMPROVA QUE LA COLUMNA ESTIGUI DINS DEL TAULER
                {
                    if(posicioLliure(col-1, taulerActual)!=-2)//SI LA COLUMNA ESTA LLIURE SURT DELS BUCLES
                    {
                        columnaValida=1;
                        break;
                    }
                    else if(posicioLliure(col-1, taulerActual)==-2)//SI LA COLUMNA ESTA PLENA S'ESCULL UNA ALTRA COLUMNA
                    {
                        printf("\n\nJUGADOR '%c', escull una columna entre 1-%d que no estigui plena: ", jugador, C);
                        scanf("%d", &col);
                    }
                }
            }
        }//QUITAR PARA JUGAR 2 HUMANOS
        freeFil=posicioLliure(col-1, taulerActual);//ESULL LA FILA DE LA COLUMNA CORRECTE ON LLENÇAR
        actualitzaTauC4(tauCh,freeFil,col,jugador,taulerActual);//ACTUALITZA I PRINTEA EL TAULER ACTUAL
        if(verifyWinC4(taulerActual,freeFil,col-1,jugador,linia)==1)//VERIFICA SI EL JUGADOR ACTUAL HA GUANYAT
        {
            printf("\n\nVICTORIA JUGADOR '%c'!!\n\n", jugador);
            break;
        }
    columnaValida=0;
    tirada++;
    }
    //MISSATGE DE TABLES
    if(tirada==F*C+1 && verifyWinC4(taulerActual, freeFil, col-1, jugador, linia)==0) printf("\n\nEMPAT, la partida ha quedat en tables!!\n\n");
}

double comprovaFiles(char tau[F][C], int fila, int col, char jugador, int linia){

    double valorLinies=0;
    int signe=0;
    int r=1;

    if(jugador=='X') signe=-1;
    else if(jugador=='O') signe=1;

    if(tau[fila][col]==jugador)
    {
        //VERIFICAR FILES
        while(col+r<C && tau[fila][col+r]==jugador) r++;
        if(r>=linia)
        {
            if(col-1>=0 && tau[fila][col-1]==' ' && col+r<C && tau[fila][col+r]==' ')
            {
                if((fila+1<F && tau[fila+1][col-1]!=' ' && tau[fila+1][col+r]!=' ') || fila+1==F) return 1e6*signe;//3 SEGUIDAS Y 1 BUENA A CADA LADO
                else if(fila+1<F && tau[fila+1][col-1]==' ' && tau[fila+1][col+r]==' ') valorLinies=15000*signe;//3 SEGUIDAS Y 1 HUECO A CADA LADO
                else if(fila+1<F && (tau[fila+1][col-1]!=' ' || tau[fila+1][col+r]!=' '))
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA Y UN HUECO+
                    else if(signe==-1) valorLinies=1e6/2*signe+1e6/4*signe;//3 SEGUIDAS Y 1 BUENA Y UN HUECO-
                }
            }
            else if(col-1>=0 && tau[fila][col-1]==' ')
            {
                if((fila+1<F && tau[fila+1][col-1]!=' ') || fila+1==F)
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA POR LA IZQUIERDA+
                    else if(signe==-1) valorLinies=1e6/2*signe;//3 SEGUIDAS Y 1 BUENA POR LA IZQUIERDA-
                }
                else if(fila+1<F && tau[fila+1][col-1]==' ') valorLinies=15000*signe;//3 SEGUIDAS Y 1 HUECO POR LA IZQUIERDA
            }
            else if(col+r<C && tau[fila][col+r]==' ')
            {
                if((fila+1<F && tau[fila+1][col+r]!=' ') || fila+1==F)
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA POR LA DERECHA+
                    else if(signe==-1) valorLinies=1e6/2*signe;//3 SEGUIDAS Y 1 BUENA POR LA DERECHA-
                }
                else if(fila+1<F && tau[fila+1][col+r]==' ') valorLinies=15000*signe;//3 SEGUIDAS Y 1 HUECO POR LA DERECHA
            }
        }
        else if(r>=linia-1)
        {
            if(col-1>=0 && col+r<C && tau[fila][col-1]==' ' && tau[fila][col+r]==' ') valorLinies=333*signe;//2 SEGUIDAS Y 1 HUECO A CADA LADO
            else if(col-2>=0 && tau[fila][col-1]==' ' && (tau[fila][col-2]==' ' || tau[fila][col-2]==jugador)) valorLinies=333*signe;//2 SEGUIDAS Y 2 HUECOS POR LA IZQUIERDA
            else if(col+r+1<C && tau[fila][col+r]==' ' && (tau[fila][col+r+1]==' ' || tau[fila][col+r+1]==jugador)) valorLinies=333*signe;//2 SEGUIDAS Y 2 HUECOS POR LA DERECHA
        }
        else if(r>=linia-2)
        {
            if(col-1>=0 && col+r<C && tau[fila][col-1]==' ' && tau[fila][col+r]==' ') valorLinies=37*signe;//1 FICHA
            else if(col-1>=0 && tau[fila][col-1]==' ') valorLinies=37*signe;//1 FICHA
            else if(col+r<C && tau[fila][col+r]==' ') valorLinies=37*signe;//1 FICHA
        }
    return valorLinies;
    }
    else return -1;//No es pot calcular
}

double comprovaColumnes(char tau[F][C], int fila, int col, char jugador, int linia){

    double valorCols=0;
    int signe=0;
    int d=1;

    if(jugador=='X') signe=-1;
    else if(jugador=='O') signe=1;

    if(tau[fila][col]==jugador)
    {
        //VERIFICAR COLUMNES
        while(fila+d<F && tau[fila+d][col]==jugador) d++;
        if(d>=linia)
        {
            if(fila-1>=0 && tau[fila-1][col]==' ')
            {
                if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA
                else if(signe==-1) valorCols=1e6/2*signe;//3 SEGUIDAS Y 1 BUENA
            }
        }
        else if(d>=linia-1)
        {
            if(fila-2>=0 && tau[fila-1][col]==' ' && tau[fila-2][col]==' ') valorCols=555*signe;//2 SEGUIDAS Y 2 ESPACIOS HACIA ARRIBA
        }
    return valorCols;
    }
    else return -1;//No es pot calcular
}

double comprovaDiagonalsP(char tau[F][C], int fila, int col, char jugador, int linia){

    double valorDp=0;
    int signe=0;
    int mDd=1;

    if(jugador=='X') signe=-1;
    else if(jugador=='O') signe=1;

    if(tau[fila][col]==jugador)
    {
        //VERIFICAR DIAGONAL PRINCIPAL
        while(fila+mDd<F && col+mDd<C && tau[fila+mDd][col+mDd]==jugador) mDd++;
        if(mDd>=linia)
        {
            if(col-1>=0 && fila-1>=0 && tau[fila-1][col-1]==' ' && col+mDd<C && fila+mDd<F && tau[fila+mDd][col+mDd]==' ')
            {
                if(tau[fila][col-1]!=' ' && ((fila+mDd+1<F && tau[fila+mDd+1][col+mDd]!=' ') || fila+mDd+1==F)) return 1e6*signe;//3 SEGUIDAS Y 1 BUENA A CADA LADO
                else if(tau[fila][col-1]==' ' && fila+mDd+1<F && tau[fila+mDd+1][col+mDd]==' ') valorDp=20000*signe;//3 SEGUIDAS Y 1 HUECO A CADA LADO
                else if(tau[fila][col-1]!=' ' || (fila+mDd+1<F && tau[fila+mDd+1][col+mDd]!=' ') || fila+mDd+1==F)
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA Y UN HUECO+
                    else if(signe==-1) valorDp=1e6/2*signe+1e6/4*signe;//3 SEGUIDAS Y 1 BUENA Y UN HUECO-
                }
            }
            else if(col-1>=0 && fila-1>=0 && tau[fila-1][col-1]==' ')
            {
                if(tau[fila][col-1]!=' ')
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA POR LA IZQUIERDA+
                    else if(signe==-1) valorDp=1e6/2*signe;//3 SEGUIDAS Y 1 BUENA POR LA IZQUIERDA-
                }
                else if(tau[fila][col-1]==' ') valorDp=20000*signe;//3 SEGUIDAS Y 1 HUECO POR LA IZQUIERDA
            }
            else if(col+mDd<C && fila+mDd<F && tau[fila+mDd][col+mDd]==' ')
            {
                if((fila+mDd+1<F && tau[fila+mDd+1][col+mDd]!=' ') || fila+mDd+1==F)
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA POR LA DERECHA+
                    else if(signe==-1) valorDp=1e6/2*signe;//3 SEGUIDAS Y 1 BUENA POR LA DERECHA-
                }
                else if(fila+mDd+1<F && tau[fila+mDd+1][col+mDd]==' ') valorDp=20000*signe;//3 SEGUIDAS Y 1 HUECO POR LA DERECHA
            }
        }
        else if(mDd>=linia-1)
        {
            if(col-1>=0 && fila-1>=0 && tau[fila-1][col-1]==' ' && col+mDd<C && fila+mDd<F && tau[fila+mDd][col+mDd]==' ') valorDp=444*signe;//2 SEGUIDAS Y 1 HUECO A CADA LADO
            else if(col-2>=0 && fila-2>=0 && tau[fila-1][col-1]==' ' && (tau[fila-2][col-2]==' ' || tau[fila-2][col-2]==jugador)) valorDp=444*signe;//2 SEGUIDAS Y 2 HUECOS POR LA IZQUIERDA
            else if(col+mDd+1<C && fila+mDd+1<F && tau[fila+mDd][col+mDd]==' ' && (tau[fila+mDd+1][col+mDd+1]==' ' || tau[fila+mDd+1][col+mDd+1]==jugador)) valorDp=444*signe;//2 SEGUIDAS Y 2 HUECOS POR LA DERECHA
        }
        else if(mDd>=linia-2)
        {
            if(col-1>=0 && fila-1>=0 && tau[fila-1][col-1]==' ' && col+mDd<C && fila+mDd<F && tau[fila+mDd][col+mDd]==' ') valorDp=37*signe;//1 FICHA
            else if(col-1>=0 && fila-1>=0 && tau[fila-1][col-1]==' ') valorDp=37*signe;//1 FICHA
            else if(col+mDd<C && fila+mDd<F && tau[fila+mDd][col+mDd]==' ') valorDp=37*signe;//1 FICHA
        }
    return valorDp;
    }
    else return -1;//No es pot calcular
}

double comprovaDiagonalsS(char tau[F][C], int fila, int col, char jugador, int linia){

    double valorDs=0;
    int signe=0;
    int sDd=1;

    if(jugador=='X') signe=-1;
    else if(jugador=='O') signe=1;

    if(tau[fila][col]==jugador)
    {
        //VERIFICAR DIAGONAL SECUNDARIA
        while(fila+sDd<F && col-sDd>=0 && tau[fila+sDd][col-sDd]==jugador) sDd++;
        if(sDd>=linia)
        {
            if(col+1<C && fila-1>=0 && tau[fila-1][col+1]==' ' && col-sDd>=0 && fila+sDd<F && tau[fila+sDd][col-sDd]==' ')//HUECO A CADA LADO
            {
                if(tau[fila][col+1]!=' ' && ((fila+sDd+1<F && tau[fila+sDd+1][col-sDd]!=' ') || fila+sDd+1==F)) return 1e6*signe;//3 SEGUIDAS Y 1 BUENA A CADA LADO
                else if(tau[fila][col+1]==' ' && fila+sDd+1<F && tau[fila+sDd+1][col-sDd]==' ') valorDs=20000*signe;//3 SEGUIDAS Y 1 HUECO A CADA LADO
                else if(tau[fila][col+1]!=' ' || (fila+sDd+1<F && tau[fila+sDd+1][col-sDd]!=' ') || fila+sDd+1==F)
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA Y UN HUECO+
                    else if(signe==-1) valorDs=1e6/2*signe+1e6/4*signe;//3 SEGUIDAS Y 1 BUENA Y UN HUECO-
                }
            }
            else if(col+1<C && fila-1>=0 && tau[fila-1][col+1]==' ')
            {
                if(tau[fila][col+1]!=' ')
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA POR LA IZQUIERDA+
                    else if(signe==-1) valorDs=1e6/2*signe;//3 SEGUIDAS Y 1 BUENA POR LA IZQUIERDA-
                }
                else if(tau[fila][col+1]==' ') valorDs=20000*signe;//3 SEGUIDAS Y 1 HUECO POR LA IZQUIERDA
            }
            else if(col-sDd>=0 && fila+sDd<F && tau[fila+sDd][col-sDd]==' ')
            {
                if((fila+sDd+1<F && tau[fila+sDd+1][col-sDd]!=' ') || fila+sDd+1==F)
                {
                    if(signe==1) return 1e6;//3 SEGUIDAS Y 1 BUENA POR LA DERECHA+
                    else if(signe==-1) valorDs=1e6/2*signe;//3 SEGUIDAS Y 1 BUENA POR LA DERECHA-
                }
                else if(fila+sDd+1<F && tau[fila+sDd+1][col-sDd]==' ') valorDs=20000*signe;//3 SEGUIDAS Y 1 HUECO POR LA DERECHA
            }
        }
        else if(sDd>=linia-1)
        {
            if(col+1<C && fila-1>=0 && tau[fila-1][col+1]==' ' && col-sDd>=0 && fila+sDd<F && tau[fila+sDd][col-sDd]==' ') valorDs=444*signe;//2 SEGUIDAS Y 1 HUECO A CADA LADO
            else if(col+2<C && fila-2>=0 && tau[fila-1][col+1]==' ' && (tau[fila-2][col+2]==' ' || tau[fila-2][col+2]==jugador)) valorDs=444*signe;//2 SEGUIDAS Y 2 POR LA IZQUIERDA
            else if(col-sDd-1>=0 && fila+sDd+1<F && tau[fila+sDd][col-sDd]==' ' && (tau[fila+sDd+1][col-sDd-1]==' ' || tau[fila+sDd+1][col-sDd-1]==jugador)) valorDs=444*signe;//2 SEGUIDAS Y 2 POR LA DERECHA
        }
        else if(sDd>=linia-2)
        {
            if(col+1<C && fila-1>=0 && tau[fila-1][col+1]==' ' && col-sDd>=0 && fila+sDd<F && tau[fila+sDd][col-sDd]==' ') valorDs=37*signe;//1 FICHA
            else if(col+1<C && fila-1>=0 && tau[fila-1][col+1]==' ') valorDs=37*signe;//1 FICHA
            else if(col-sDd>=0 && fila+sDd<F && tau[fila+sDd][col-sDd]==' ') valorDs=37*signe;//1 FICHA
        }
    return valorDs;
    }
    else return -1;//No es pot calcular
}

double HeuristicaC4(int pareValor,char t[F][C],int fil,int col,char jugador){

    double valor=0;
    char jugadorfc;
    int linia=3;

    //COMPROVAR TOTES LES POSICIONS DEL TAULER ACTUAL
    for(int f=0;f<F;f++)
    {
        for(int c=0;c<C;c++)
        {
            if(t[f][c]=='O')
            {
                jugadorfc=t[f][c];
                //DIAGONAL SECUNDARIA O
                if((f+1!=F || c-1!=-1 || (f+1<F && c-1>=0 && t[f+1][c-1]!='X')) && ((f-1>=0 && c+1<C && t[f-1][c+1]!='O') || f-1==-1 || c+1==C))//NO HAY MURO ABAJO Y NO HAY 'O' ARRIBA
                {
                    if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)==1e6) return 1e6;//AQUI GANA LA MAQUINA
                    else if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)==20000) valor+=comprovaDiagonalsS(t,f,c,jugadorfc,linia);//AQUI HAY 3 SEGUIDAS
                    else if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)>=0)//AQUI HAY 2 SEGUIDAS O UNA SOLO
                    {
                        if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)==444 && (((f-1>=0 && c+1<C && t[f-1][c+1]=='X') || f-1==-1 || c+1==C) || ((f-2>=0 && c+2<C && t[f-1][c+1]==' ' && t[f-2][c+2]!='O') || (f-1>=0 && c+1<C && t[f-1][c+1]==' ' && (c+2==C || f-2==-1)))))//1ER CASO: HAY 2 SEGUIDAS Y HAY MURO ARRIBA O HAY ESPACIO ARRIBA Y NO HAY 'O' EN DOS POSICIONES ARRIBA
                        {
                            if(f+3<F && c-3>=0 && t[f+3][c-3]=='O' && t[f+2][c-2]==' ' && t[f+3][c-2]!=' ' && ((f+4<F && c-4>=0 && t[f+4][c-4]!='O') || f+4==F || c-4==-1 || (f+4<F && c-4>=0 && t[f+4][c-4]=='O' && ((f+5<F && c-5>=0 && t[f+5][c-5]!='O') || f+5==F || c-5==-1)))) return 1e6;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(f+3<F && c-3>=0 && t[f+3][c-3]=='O' && t[f+2][c-2]==' ' && ((f+4<F && c-4>=0 && t[f+4][c-4]!='O') || f+4==F || c-4==-1 || (f+4<F && c-4>=0 && t[f+4][c-4]=='O' && ((f+5<F && c-5>=0 && t[f+5][c-5]!='O') || f+5==F || c-5==-1)))) valor+=20000;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA MALA
                            else valor+=comprovaDiagonalsS(t,f,c,jugadorfc,linia);//SOLO TENEMOS DOS SEGUIDAS
                        }
                        else if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)==37 && (((f-1>=0 && c+1<C && t[f-1][c+1]=='X') || f-1==-1 || c+1==C) || ((f-2>=0 && c+2<C && t[f-1][c+1]==' ' && t[f-2][c+2]!='O') || (f-1>=0 && c+1<C && t[f-1][c+1]==' ' && (c+2==C || f-2==-1)))))//2NDO CASO: HAY 1 FICHA Y HAY MURO ARRIBA O HAY ESPACIO ARRIBA Y NO HAY 'O' EN DOS POSICIONES ARRIBA
                        {
                            if(f+3<F && c-3>=0 && t[f+2][c-2]=='O' && t[f+2][c-1]!=' ' && t[f+3][c-3]=='O' && t[f+1][c-1]==' ' && ((f+4<F && c-4>=0 && t[f+4][c-4]!='O') || f+4==F || c-4==-1)) return 1e6;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(f+3<F && c-3>=0 && t[f+2][c-2]=='O' && t[f+3][c-3]=='O' && t[f+1][c-1]==' ' && ((f+4<F && c-4>=0 && t[f+4][c-4]!='O') || f+4==F || c-4==-1)) valor+=20000;//LO MISMO QUE TENER 3 SEGUIDAS Y MALA
                            else if(f+2<F && c-2>=0 && t[f+2][c-2]=='O' && ((f+3<F && c-3>=0 && t[f+3][c-3]==' ') || (f-1>=0 && c+1<C && t[f-1][c+1]==' ')) && t[f+1][c-1]==' ') valor+=444;//LO MISMO QUE TENER 2 SEGUIDAS Y DOS HUECOS
                        }
                    }
                }
                //DIAGONAL PRINCIPAL O
                if((f+1!=F || c+1!=C || (f+1<F && c+1<C && t[f+1][c+1]!='X')) && ((f-1>=0 && c-1>=0 && t[f-1][c-1]!='O') || f-1==-1 || c-1==-1))//NO HAY MURO ABAJO Y NO HAY 'O' ARRIBA
                {
                    if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)==1e6) return 1e6;//AQUI GANA LA MAQUINA
                    else if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)==20000) valor+=comprovaDiagonalsP(t,f,c,jugadorfc,linia);//AQUI HAY 3 SEGUIDAS
                    else if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)>=0)//AQUI HAY 2 SEGUIDAS O UNA SOLO
                    {
                        if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)==444 && (((f-1>=0 && c-1>=0 && t[f-1][c-1]=='X') || f-1==-1 || c-1==-1) || ((f-2>=0 && c-2>=0 && t[f-1][c-1]==' ' && t[f-2][c-2]!='O') || (f-1>=0 && c-1>=0 && t[f-1][c-1]==' ' && (c-2==-1 || f-2==-1)))))//1ER CASO: HAY 2 SEGUIDAS Y HAY MURO ARRIBA O HAY ESPACIO ARRIBA Y NO HAY 'O' EN DOS POSICIONES ARRIBA
                        {
                            if(f+3<F && c+3<C && t[f+3][c+3]=='O' && t[f+2][c+2]==' ' && t[f+3][c+2]!=' ' && ((f+4<F && c+4<C && t[f+4][c+4]!='O') || f+4==F || c+4==C || (f+4<F && c+4<C && t[f+4][c+4]=='O' && ((f+5<F && c+5<C && t[f+5][c+5]!='O') || f+5==F || c+5==C)))) return 1e6;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(f+3<F && c+3<C && t[f+3][c+3]=='O' && t[f+2][c+2]==' ' && ((f+4<F && c+4<C && t[f+4][c+4]!='O') || f+4==F || c+4==C || (f+4<F && c+4<C && t[f+4][c+4]=='O' && ((f+5<F && c+5<C && t[f+5][c+5]!='O') || f+5==F || c+5==C)))) valor+=20000;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA MALA
                            else valor+=comprovaDiagonalsP(t,f,c,jugadorfc,linia);//SOLO TENEMOS DOS SEGUIDAS
                        }
                        else if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)==37 && (((f-1>=0 && c-1>=0 && t[f-1][c-1]=='X') || f-1==-1 || c-1==-1) || ((f-2>=0 && c-2>=0 && t[f-1][c-1]==' ' && t[f-2][c-2]!='O') || (f-1>=0 && c-1>=0 && t[f-1][c-1]==' ' && (c-2==-1 || f-2==-1)))))//2NDO CASO: HAY 1 FICHA Y HAY MURO ARRIBA O HAY ESPACIO ARRIBA Y NO HAY 'X' EN DOS POSICIONES ARRIBA
                        {
                            if(f+3<F && c+3<C && t[f+2][c+2]=='O' && t[f+2][c+1]!=' ' && t[f+3][c+3]=='O' && t[f+1][c+1]==' ' && ((f+4<F && c+4<C && t[f+4][c+4]!='O') || f+4==F || c+4==C)) return 1e6;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(f+3<F && c+3<C && t[f+2][c+2]=='O' && t[f+3][c+3]=='O' && t[f+1][c+1]==' ' && ((f+4<F && c+4<C && t[f+4][c+4]!='O') || f+4==F || c+4==C)) valor+=20000;//LO MISMO QUE TENER 3 SEGUIDAS Y MALA
                            else if(f+2<F && c+2<C && t[f+2][c+2]=='O' && ((f+3<F && c+3<C && t[f+3][c+3]==' ') || (f-1>=0 && c-1>=0 && t[f-1][c-1]==' ')) && t[f+1][c+1]==' ') valor+=444;//LO MISMO QUE TENER 2 SEGUIDAS Y DOS HUECOS
                        }
                    }
                }
                //FILA O
                if((c+1!=C || (c+1<C && t[f][c+1]!='X')) && ((c-1>=0 && t[f][c-1]!='O') || c-1==-1))//NO HAY MURO DERECHA Y NO HAY 'O' IZQUIERDA
                {
                    if(comprovaFiles(t,f,c,jugadorfc,linia)==1e6) return 1e6;//AQUI GANA LA MAQUINA
                    else if(comprovaFiles(t,f,c,jugadorfc,linia)==15000) valor+=comprovaFiles(t,f,c,jugadorfc,linia);//AQUI HAY 3 SEGUIDAS BUENAS
                    else if(comprovaFiles(t,f,c,jugadorfc,linia)>=0)//AQUI HAY 2 SEGUIDAS O UNA SOLO
                    {
                        if(comprovaFiles(t,f,c,jugadorfc,linia)==333 && (((c-1>=0 && t[f][c-1]=='X') || c-1==-1) || ((c-2>=0 && t[f][c-1]==' ' && t[f][c-2]!='O') || (c-1>=0 && t[f][c-1]==' ' && c-2==-1))))//1ER CASO: HAY 2 SEGUIDAS Y HAY MURO IZQUIERDA O HAY ESPACIO IZQUIERDA Y NO HAY 'O' EN DOS POSICIONES A LA IZQUIERDA
                        {
                            if(c+3<C && t[f][c+3]=='O' && t[f][c+2]==' ' && ((f+1<F && t[f+1][c+2]!=' ') || f+1==F) && ((c+4<C && t[f][c+4]!='O') || c+4==C || (c+4<C && t[f][c+4]=='O' && ((c+5<C && t[f][c+5]!='O') || c+5==C)))) return 1e6;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(c+3<C && t[f][c+3]=='O' && t[f][c+2]==' ' && ((c+4<C && t[f][c+4]!='O') || c+4==C || (c+4<C && t[f][c+4]=='O' && ((c+5<C && t[f][c+5]!='O') || c+5==C)))) valor+=15000;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA MALA
                            else valor+=comprovaFiles(t,f,c,jugadorfc,linia);//SOLO TENEMOS DOS SEGUIDAS
                        }
                        else if(comprovaFiles(t,f,c,jugadorfc,linia)==37 && (((c-1>=0 && t[f][c-1]=='X') || c-1==-1) || ((c-2>=0 && t[f][c-1]==' ' && t[f][c-2]!='O') || (c-1>=0 && t[f][c-1]==' ' && c-2==-1))))//2NDO CASO: HAY 1 FICHA Y HAY MURO IZQUIERDA O HAY ESPACIO IZQUIERDA Y NO HAY 'X' EN DOS POSICIONES IZQUIERDA
                        {
                            if(c+3<C && t[f][c+2]=='O' && ((f+1<F && t[f+1][c+1]!=' ') || f+1==F) && t[f][c+3]=='O' && t[f][c+1]==' ' && ((c+4<C && t[f][c+4]!='O') || c+4==C)) return 1e6;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(c+3<C && t[f][c+2]=='O' && t[f][c+3]=='O' && t[f][c+1]==' ' && ((c+4<C && t[f][c+4]!='O') || c+4==C)) valor+=15000;//LO MISMO QUE TENER 3 SEGUIDAS Y MALA
                            else if(c+2<C && t[f][c+2]=='O' && ((c+3<C && t[f][c+3]==' ') || (c-1>=0 && t[f][c-1]==' ')) && t[f][c+1]==' ') valor+=333;//LO MISMO QUE TENER 2 SEGUIDAS Y DOS HUECOS
                        }
                    }
                }
                //COLUMNA O
                if((f+1!=F || (f+1<F && t[f+1][c]!='X')) && ((f-1>=0 && t[f-1][c]!='O') || f-1==-1))//NO HAY MURO ABAJO Y NO HAY 'O' ARRIBA
                {
                    if(comprovaColumnes(t,f,c,jugadorfc,linia)==1e6) return 1e6;//AQUI GANA LA MAQUINA
                    else if(comprovaColumnes(t,f,c,jugadorfc,linia)==555) valor+=comprovaColumnes(t,f,c,jugadorfc,linia);//AQUI HAY 2 SEGUIDAS
                }
            }
            else if(t[f][c]=='X')
            {
                jugadorfc=t[f][c];
                //DIAGONAL SECUNDARIA X
                if((f+1!=F || c-1!=-1 || (f+1<F && c-1>=0 && t[f+1][c-1]!='O')) && ((f-1>=0 && c+1<C && t[f-1][c+1]!='X') || f-1==-1 || c+1==C))//NO HAY MURO ABAJO Y NO HAY 'X' ARRIBA
                {
                    if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)==-1e6) return -1e6;//AQUI GANA EL HUMANO
                    else if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)<=-20000) valor+=comprovaDiagonalsS(t,f,c,jugadorfc,linia);//AQUI HAY 3 SEGUIDAS
                    else if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)<=0)//AQUI HAY 2 SEGUIDAS O UNA SOLO
                    {
                        if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)==-444 && (((f-1>=0 && c+1<C && t[f-1][c+1]=='O') || f-1==-1 || c+1==C) || ((f-2>=0 && c+2<C && t[f-1][c+1]==' ' && t[f-2][c+2]!='X') || (f-1>=0 && c+1<C && t[f-1][c+1]==' ' && (c+2==C || f-2==-1)))))//1ER CASO: HAY 2 SEGUIDAS Y HAY MURO ARRIBA O HAY ESPACIO ARRIBA Y NO HAY 'X' EN DOS POSICIONES ARRIBA
                        {
                            if(f+3<F && c-3>=0 && t[f+3][c-3]=='X' && t[f+2][c-2]==' ' && t[f+3][c-2]!=' ' && ((f+4<F && c-4>=0 && t[f+4][c-4]!='X') || f+4==F || c-4==-1 || (f+4<F && c-4>=0 && t[f+4][c-4]=='X' && ((f+5<F && c-5>=0 && t[f+5][c-5]!='X') || f+5==F || c-5==-1)))) valor+=-1e6/2;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(f+3<F && c-3>=0 && t[f+3][c-3]=='X' && t[f+2][c-2]==' ' && ((f+4<F && c-4>=0 && t[f+4][c-4]!='X') || f+4==F || c-4==-1 || (f+4<F && c-4>=0 && t[f+4][c-4]=='X' && ((f+5<F && c-5>=0 && t[f+5][c-5]!='X') || f+5==F || c-5==-1)))) valor+=-20000;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA MALA
                            else valor+=comprovaDiagonalsS(t,f,c,jugadorfc,linia);//SOLO TENEMOS DOS SEGUIDAS
                        }
                        else if(comprovaDiagonalsS(t,f,c,jugadorfc,linia)==-37 && (((f-1>=0 && c+1<C && t[f-1][c+1]=='O') || f-1==-1 || c+1==C) || ((f-2>=0 && c+2<C && t[f-1][c+1]==' ' && t[f-2][c+2]!='X') || (f-1>=0 && c+1<C && t[f-1][c+1]==' ' && (c+2==C || f-2==-1)))))//2NDO CASO: HAY 1 FICHA Y HAY MURO ARRIBA O HAY ESPACIO ARRIBA Y NO HAY 'X' EN DOS POSICIONES ARRIBA
                        {
                            if(f+3<F && c-3>=0 && t[f+2][c-2]=='X' && t[f+2][c-1]!=' ' && t[f+3][c-3]=='X' && t[f+1][c-1]==' ' && ((f+4<F && c-4>=0 && t[f+4][c-4]!='X') || f+4==F || c-4==-1)) valor+=-1e6/2;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(f+3<F && c-3>=0 && t[f+2][c-2]=='X' && t[f+3][c-3]=='X' && t[f+1][c-1]==' ' && ((f+4<F && c-4>=0 && t[f+4][c-4]!='X') || f+4==F || c-4==-1)) valor+=-20000;//LO MISMO QUE TENER 3 SEGUIDAS Y MALA
                            else if(f+2<F && c-2>=0 && t[f+2][c-2]=='X' && ((f+3<F && c-3>=0 && t[f+3][c-3]==' ') || (f-1>=0 && c+1<C && t[f-1][c+1]==' ')) && t[f+1][c-1]==' ') valor+=-444;//LO MISMO QUE TENER 2 SEGUIDAS Y DOS HUECOS
                        }
                    }
                }
                //DIAGONAL PRINCIPAL X
                if((f+1!=F || c+1!=C || (f+1<F && c+1<C && t[f+1][c+1]!='O')) && ((f-1>=0 && c-1>=0 && t[f-1][c-1]!='X') || f-1==-1 || c-1==-1))//NO HAY MURO ABAJO Y NO HAY 'X' ARRIBA
                {
                    if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)==-1e6) return -1e6;//AQUI GANA EL HUMANO
                    else if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)<=-20000) valor+=comprovaDiagonalsP(t,f,c,jugadorfc,linia);//AQUI HAY 3 SEGUIDAS
                    else if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)<=0)//AQUI HAY 2 SEGUIDAS O UNA SOLO
                    {
                        if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)==-444 && (((f-1>=0 && c-1>=0 && t[f-1][c-1]=='O') || f-1==-1 || c-1==-1) || ((f-2>=0 && c-2>=0 && t[f-1][c-1]==' ' && t[f-2][c-2]!='X') || (f-1>=0 && c-1>=0 && t[f-1][c-1]==' ' && (c-2==-1 || f-2==-1)))))//1ER CASO: HAY 2 SEGUIDAS Y HAY MURO ARRIBA O HAY ESPACIO ARRIBA Y NO HAY 'X' EN DOS POSICIONES ARRIBA O HAY ESPACIO EN 3 POSICIONES ARRIBA
                        {
                            if(f+3<F && c+3<C && t[f+3][c+3]=='X' && t[f+2][c+2]==' ' && t[f+3][c+2]!=' ' && ((f+4<F && c+4<C && t[f+4][c+4]!='X') || f+4==F || c+4==C || (f+4<F && c+4<C && t[f+4][c+4]=='X' && ((f+5<F && c+5<C && t[f+5][c+5]!='X') || f+5==F || c+5==C)))) valor+=-1e6/2;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(f+3<F && c+3<C && t[f+3][c+3]=='X' && t[f+2][c+2]==' ' && ((f+4<F && c+4<C && t[f+4][c+4]!='X') || f+4==F || c+4==C || (f+4<F && c+4<C && t[f+4][c+4]=='X' && ((f+5<F && c+5<C && t[f+5][c+5]!='X') || f+5==F || c+5==C)))) valor+=-20000;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA MALA
                            else valor+=comprovaDiagonalsP(t,f,c,jugadorfc,linia);//SOLO TENEMOS DOS SEGUIDAS
                        }
                        else if(comprovaDiagonalsP(t,f,c,jugadorfc,linia)==-37 && (((f-1>=0 && c-1>=0 && t[f-1][c-1]=='O') || f-1==-1 || c-1==-1) || ((f-2>=0 && c-2>=0 && t[f-1][c-1]==' ' && t[f-2][c-2]!='X') || (f-1>=0 && c-1>=0 && t[f-1][c-1]==' ' && (c-2==-1 || f-2==-1)))))//2NDO CASO: AQUI HAY 1 CON ESPACIO
                        {
                            if(f+3<F && c+3<C && t[f+2][c+2]=='X' && t[f+2][c+1]!=' ' && t[f+3][c+3]=='X' && t[f+1][c+1]==' ' && ((f+4<F && c+4<C && t[f+4][c+4]!='X') || f+4==F || c+4==C)) valor+=-1e6/2;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(f+3<F && c+3<C && t[f+2][c+2]=='X' && t[f+3][c+3]=='X' && t[f+1][c+1]==' ' && ((f+4<F && c+4<C && t[f+4][c+4]!='X') || f+4==F || c+4==C)) valor+=-20000;//LO MISMO QUE TENER 3 SEGUIDAS Y MALA
                            else if(f+2<F && c+2<C && t[f+2][c+2]=='X' && ((f+3<F && c+3<C && t[f+3][c+3]==' ') || (f-1>=0 && c-1>=0 && t[f-1][c-1]==' ')) && t[f+1][c+1]==' ') valor+=-444;//LO MISMO QUE TENER 2 SEGUIDAS Y DOS HUECOS
                        }
                    }
                }
                //FILA X
                if((c+1!=C || (c+1<C && t[f][c+1]!='O')) && ((c-1>=0 && t[f][c-1]!='X') || c-1==-1))//NO HAY MURO DERECHA Y NO HAY 'O' IZQUIERDA
                {
                    if(comprovaFiles(t,f,c,jugadorfc,linia)==-1e6) return -1e6;//AQUI GANA EL HUMANO
                    else if(comprovaFiles(t,f,c,jugadorfc,linia)<=-15000) valor+=comprovaFiles(t,f,c,jugadorfc,linia);//AQUI HAY 3 SEGUIDAS BUENAS
                    else if(comprovaFiles(t,f,c,jugadorfc,linia)<=0)//AQUI HAY 2 SEGUIDAS O UNA SOLO
                    {
                        if(comprovaFiles(t,f,c,jugadorfc,linia)==-333 && (((c-1>=0 && t[f][c-1]=='O') || c-1==-1) || ((c-2>=0 && t[f][c-1]==' ' && t[f][c-2]!='X') || (c-1>=0 && t[f][c-1]==' ' && c-2==-1))))//1ER CASO: HAY 2 SEGUIDAS Y HAY MURO IZQUIERDA O HAY ESPACIO IZQUIERDA Y NO HAY 'O' EN DOS POSICIONES A LA IZQUIERDA
                        {
                            if(c+3<C && t[f][c+3]=='X' && t[f][c+2]==' ' && ((f+1<F && t[f+1][c+2]!=' ') || f+1==F) && ((c+4<C && t[f][c+4]!='X') || c+4==C || (c+4<C && t[f][c+4]=='X' && ((c+5<C && t[f][c+5]!='X') || c+5==C)))) valor+=-1e6/2;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(c+3<C && t[f][c+3]=='X' && t[f][c+2]==' ' && ((c+4<C && t[f][c+4]!='X') || c+4==C || (c+4<C && t[f][c+4]=='X' && ((c+5<C && t[f][c+5]!='X') || c+5==C)))) valor+=-15000;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA MALA
                            else valor+=comprovaFiles(t,f,c,jugadorfc,linia);//SOLO TENEMOS DOS SEGUIDAS
                        }
                        else if(comprovaFiles(t,f,c,jugadorfc,linia)==-37 && (((c-1>=0 && t[f][c-1]=='O') || c-1==-1) || ((c-2>=0 && t[f][c-1]==' ' && t[f][c-2]!='X') || (c-1>=0 && t[f][c-1]==' ' && c-2==-1))))//2NDO CASO: HAY 1 FICHA Y HAY MURO IZQUIERDA O HAY ESPACIO IZQUIERDA Y NO HAY 'X' EN DOS POSICIONES IZQUIERDA
                        {
                            if(c+3<C && t[f][c+2]=='X' && ((f+1<F && t[f+1][c+1]!=' ') || f+1==F) && t[f][c+3]=='X' && t[f][c+1]==' ' && ((c+4<C && t[f][c+4]!='X') || c+4==C)) valor+=-1e6/2;//LO MISMO QUE TENER 3 SEGUIDAS Y UNA BUENA
                            else if(c+3<C && t[f][c+2]=='X' && t[f][c+3]=='X' && t[f][c+1]==' ' && ((c+4<C && t[f][c+4]!='X') || c+4==C)) valor+=-15000;//LO MISMO QUE TENER 3 SEGUIDAS Y MALA
                            else if(c+2<C && t[f][c+2]=='X' && ((c+3<C && t[f][c+3]==' ') || (c-1>=0 && t[f][c-1]==' ')) && t[f][c+1]==' ') valor+=-333;//LO MISMO QUE TENER 2 SEGUIDAS Y DOS HUECOS
                        }
                    }
                }
                //COLUMNA X
                if((f+1!=F || (f+1<F && t[f+1][c]!='O')) && ((f-1>=0 && t[f-1][c]!='X') || f-1==-1))//NO HAY MURO ABAJO Y NO HAY 'O' ARRIBA
                {
                    if(comprovaColumnes(t,f,c,jugadorfc,linia)==-1e6/2) valor+=-1e6/2;//AQUI GANARIA EL HUMANO
                    else if(comprovaColumnes(t,f,c,jugadorfc,linia)==-555) valor+=comprovaColumnes(t,f,c,jugadorfc,linia);//AQUI HAY 2 SEGUIDAS
                }
            }
        }
    }
return valor;
}
