
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "kq.h"
using namespace std;

//http://mathworld.wolfram.com/KnightsProblem.html

/* m*n is the board dimension
k is the number of knights to be placed on board
count is the number of possible solutions */
int m, n, k;

int main( int argc, char *argv[]){

  if (argc <= 2 ) {
    printf("./knight <linha_tabuleiro> <nro_cavalos>\n");
    return -1;
  }

  m = atoi(argv	[1]);
  n = m;
  k = atoi(argv [2]);

  //criando o tabuleiro
  char** board = new char*[m];
  for (int i = 0; i < m; i++) {
    board[i] = new char[n];
  }

  makeBoard(board, m, n); //colocando em cada celula o valor "_"


  kkn(k, 0, 0, board, m, n);

  return 0;
}
