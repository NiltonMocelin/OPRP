#include <iostream>
#include <time.h>
#include <sys/time.h>

using namespace std;

inline double time_i;

double wtime();

int attackqueens(int oi, int oj, char a, char** board, int m, int n);
void attack(int i, int j, char a,char** board, int m, int n);

void displayBoardCoordenatesMatrix(char** board, int m, int n);

void displayResult(char** board, int m, int n);

bool canPlace(int i, int j, char** board);

void makeBoard(char** board, int m, int n);

int place(int i, int j, char k, char a, char** board, char** new_board, int m, int n);

int attackqueens(int oi, int oj, char a, char** board, int m, int n);

void displayBoard(char** board, int m, int n);

void attack(int i, int j, char a, char** board, int m, int n);

void queens (int qui, int quj, char ** board, int m, int n);

void kkn(int k, int sti, int stj, char** board, int m, int n);
