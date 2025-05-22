#define F 6
#define C 7

int posicioLliure(int col, char tauler[F][C]);
void iniciaTauC4(char tauCh[2*F+1][2*C+1], char tauler[F][C]);
void actualitzaTauC4(char tauCh[2*F+1][2*C+1], int freeFil, int col, char jugador, char tauler[F][C]);
int verifyWinC4(char tauler[F][C], int fila, int col, char jugador, int linia);

void playC4(char tauCh[2*F+1][2*C+1], int profunditat, char taulerActual[F][C]);

double comprovaFiles(char tau[F][C], int fila, int col, char jugador, int linia);
double comprovaColumnes(char tau[F][C], int fila, int col, char jugador, int linia);
double comprovaDiagonalsP(char tau[F][C], int fila, int col, char jugador, int linia);
double comprovaDiagonalsS(char tau[F][C], int fila, int col, char jugador, int linia);
double HeuristicaC4(int pareValor,char t[F][C],int fil,int col,char jugador);
