#include <iostream>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <sys/time.h>

//definicoes para as flags :)
#define K_PARAR 1
#define Q_PARAR 1
#define K_CONTINUAR 0
#define Q_CONTINUAR 0

using namespace std;

inline double time_i;

double wtime();

inline omp_lock_t lock;
//uso: omp_set_lock(&lock); omp_unset_lock(&lock);

//usada para controlar as threads, quando uma encontrar o resultado esperado, as outras nao devem continuar
inline int flag1; //usada nos cavaleiros k_
inline int flag2; //usada nas rainhas Q_

int busca_primeira_linha_sem_peca(char **board, int m, int n, char peca);

int remover_ultima_peca(int *posicao_i, int *posicao_j, char **board, int m, int n, char peca);
int tentar_posicionar_peca(int i, int j, char **board, int m, int n, char peca);
void remarcar_ataque_pecas(char **board, int m, int n);

int attackqueens(int oi, int oj, char a, char** board, int m, int n);
int attack(int i, int j, char a, char** board, int m, int n);
bool canPlace(int i, int j, char** board);
int place(int i, int j, char k, char a, char** board, int m, int n);

void makeBoard(char** board, int m, int n);
void displayBoardCoordenatesMatrix(char** board, int m, int n);
void displayResult(char** board, int m, int n);
void displayBoard(char** board, int m, int n);


void queens (char ** board, int m, int n, int k);
void kkn(int sti, int stj, int k, char** board, int m, int n);//paralelo
void kkn_otimizado(int k, char** board, int m, int n);
