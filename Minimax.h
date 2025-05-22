typedef struct node{
    struct node **fills;
    int n_fills;
    char tauler[F][C];
    double valor;
    int nivell;
} Node;

//FUNCIONS PER CREAR ELS NODES
int estableixJerarquia(int valorNodePare, int identificador);
void copiaTauler(char tauPare[F][C],char tauFill[F][C]);
int colPlena(char tauler[F][C],int indicador);
int calculaNumFills(char tauler[F][C]);
int numFill(char tauler[F][C],int indicador);
int fesTirada(char tau[F][C],int col, char nivellCh);

//FUNCIONS PER CREAR L'ARBRE
Node *crearNode(Node *pare,int nivell,int col,int profunditat);
void crearNivell(Node *pare,int nivell,int profunditat);
void creaArbre(Node *arrel,int profunditat);
void recorrerArbreRecursiu(Node *p,int nivell,int profunditat);
void printeaArbreRecursiu(Node *p,int nivell,int profunditat);
void lliberaArbreRecursiu(Node *node);
void escullDificultat(int *profunditat);
int fMinimax(int profunditat, char taulerInicial[F][C]);

//FUNCIONS PER DONAR VALORS ALS NODES
double estrategiaValors(Node *pare);
int escollirCol(Node *arrel);
int randomChoice(int valor1, int valor2);



