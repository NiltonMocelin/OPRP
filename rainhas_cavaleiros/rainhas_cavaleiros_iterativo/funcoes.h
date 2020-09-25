#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

inline double time_i;

double wtime();

void remover_ultimo_X(int *posicao_i, int *posicao_j, char **board, int m, int n, char peca);
int tentar_posicionar_cavaleiro(int i, int j, char **board, int m, int n);
void remarcar_ataque_cavaleiros(char **board, int m, int n);

int attackqueens(int oi, int oj, char a, char** board, int m, int n);
int attack(int i, int j, char a, char** board, int m, int n);
bool canPlace(int i, int j, char** board);
int place(int i, int j, char k, char a, char** board, int m, int n);

void makeBoard(char** board, int m, int n);
void displayBoardCoordenatesMatrix(char** board, int m, int n);
void displayResult(char** board, int m, int n);
void displayBoard(char** board, int m, int n);


void queens (int qui, int quj, char ** board, int m, int n);
void kkn(int k, char** board, int m, int n);
