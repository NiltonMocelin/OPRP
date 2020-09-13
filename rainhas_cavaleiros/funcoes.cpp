#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "kq.h"
using namespace std;

/*
essa funcao coloca os cavalos no tabuleiro de forma que eles nao se ataquem
*/
void kkn(int k, int sti, int stj, char** board, int m, int n){

  /*
  Se nao tiver sobrado nenhum cavalo (a funcao do cavalo eh recursiva, entao vai sempre diminuindo 1),
  entao printar o tabuleiro e incrementar o board
  */
  if (k == 0) { // se o numero de cavalos for igual a 0, entao...
    queens(0,0,board, m, n); //funcao das rainhas
    displayBoardCoordenatesMatrix(board, m, n); //mostar o tabuleiro
    displayResult(board, m, n); // mostrar o resultado
    exit (1); //sair
  }

  else { //o numero de cavalos nao eh igual a

    /* loop que vai passar por todas as posicoes do tabuleiro */
    for (int i = sti; i < m; i++) {

      for (int j = stj; j < n; j++) {

        if (canPlace(i, j, board)) { //vai verificar se na posicao ij pode colocar o cavalo

          /* criacao de um novo tabuleiro e coloca o cavalo */
          char** new_board = new char*[m]; //cria um novo tabuleiro
          for (int x = 0; x < m; x++) {
            new_board[x] = new char[n];
          }

          //vai colocar o cavalo no tabuleiro e marcar todas as posicoes posicoes de ataque do cavalo no tabuleiro
          place(i, j, 'K', 'A', board, new_board, m, n);

          /*
            vai chamar recursivamente essa funcao pro cavalo k - 1
            e passando como paramentro o tabuleiro que tem as marcacoes de ataquem
          */
          kkn(k - 1, i, j, new_board, m, n); //chamada recursiva

          /* deletar o novo tabuleiro */
          for (int x = 0; x < m; x++) {
            delete[] new_board[x];
          }
          delete[] new_board;
        }
      }
      stj = 0;
    }
  }
}

//fazer iterativo e nao recursivo
void kkn_iterativo(int k, char** board, int m, int n){
/* ideia:
- o nosso codigo posiciona os cavaleiros onde conseguir, ok
- mas a quantidade de rainhas colocadas pode ser maximizado (ou nao, ainda nao tenho certeza)

Para posicionar as rainhas e cavaleiros o professor criava uma matriz auxiliar
Podemos criar uma matriz auxiliar para posicionar as rainhas.
Criamos um contador de rainhas e um contador maximo de rainhas.
A matriz board, armazena apenas a matriz que contem o numero maximo de rainhas.
Cada vez que uma solucao consegue posicionar mais que o maximo, substituimos a board pela auxiliar

Acredito que isso deva ser implementado para cavaleiros e para rainhas. De alguma forma, a cada iteracao, o cavaleiro_0 que era posicionado em [0][0]
deve ser posicionado em [0][1], da mesma forma as rainhas.

(pensar sobre isso)
*/
int contadorCavaleiros=0, contadorRainhas=0;

//Posicionar os k cavaleiros primeiro
  for (int i=0; i<k; i++){

    for(int ii=0; ii<m; ii++){

      for(int jj=0; jj<n; jj++){

          if(canPlace(ii, jj, board)){
            contadorCavaleiros++;
            //vai colocar o cavalo no tabuleiro e marcar todas as posicoes posicoes de ataque do cavalo no tabuleiro
            place(ii, jj, 'K', 'A', board, board, m, n);
          }

          if(contadorCavaleiros == k){//para sair de todos os for
            break;
          }
      }

      if(contadorCavaleiros == k){//para sair de todos os for
        break;
      }
    }
    if(contadorCavaleiros == k){//para sair de todos os for
      break;
    }
    }

int posicionarOutra=0;//rainha

  //posicionar as rainhas
  for(int i=0;i<m*n;i++){

    for(int ii=0; ii<m; ii++){

      for(int jj=0; jj<n; jj++){

          if(canPlace(ii, jj, board)){
            //vai colocar o cavalo no tabuleiro e marcar todas as posicoes posicoes de ataque do cavalo no tabuleiro
            if (place(ii, jj, 'Q', 'a', board, board, m, n)){
              board[ii][jj] = '*';
            }else {
              contadorRainhas++;
              board[ii][jj] = 'Q';
              posicionarOutra=1;//como nao temos controle, a cada vez que posicionarmos uma rainha setamos esta variavel para sair dos dois for
              break;//fim for interno - colunas da matriz
            }
          }

      }

        if(posicionarOutra==1){
          break;//fim do for das linhas da matriz
        }
      }

      //se saiu do for e nao eh para posicionar outra rainha => significa que percorreu toda a matriz e nao conseguiu posicionar
      if(posicionarOutra==1){
        posicionarOutra=0;
      }else{
        break;
      }

  }

    /* Se ao final de uma iteração nao conseguimos encontrar uma solucao
    deletar o tabuleiro e fazer novamente novo tabuleiro */
    // for (int x = 0; x < m; x++) {
    //   delete[] new_board[x];
    // }
    // delete[] new_board;

    printf("Qtd cavaleiros: %d\n", contadorCavaleiros);
    printf("Qtd rainhas : %d\n", contadorRainhas);
    displayBoardCoordenatesMatrix(board, m, n); //mostar o tabuleiro
    displayResult(board, m, n); // mostrar o resultado

}

//verifica se a posicao ij do tabuleiro esta vago
bool canPlace(int i, int j, char** board){
  if (board[i][j] == '_')
    return true;
  else
    return false;
}

/*
coloca o cavalo na posicao ij do tabuleiro ou
coloca a rainha na posicao ij
*/
int place(int i, int j, char k, char a, char** board, char** new_board, int m, int n){

    /* copia as configuracoes do tabuleiro antigo para o novo */
    for (int y = 0; y < m; y++) {
      for (int z = 0; z < n; z++) {
        new_board[y][z] = board[y][z];
      }
    }

    new_board[i][j] = k; //coloca o cavalo na ij do tabuleiro novo

    /* marca todas as possiveis posicoes que podem ser atacaads pelo novo cavaleiro adicionado no novo tabuleiro*/
    if (k == 'K') { //se a variavel k, passada como parametro for igual a 'K', ou seja, eh um cavaleiro
      attack(i, j, a, new_board, m, j); //marcar todas as posicoes que podem ser atacadas pelo cavaleiro no novo tabuleiro
    }
    else { //se a variavel k == rainha, entao
      return(attackqueens(i, j, a, new_board, m, n));
    }
    return (0);
  }

/*
vai marcar todas as posiveis posicoes de ataque do cavalo no linha_tabuleiro
lembrar que o cavalo sempre se movimenta em L (2 na vertical e 1 na horizontal) ou (2 na horizontal e 1 na vertical)
*/
void attack(int i, int j, char a, char** board, int m, int n){

  //faz as verificacoes de vertical e horizontal
  if ((i + 2) < m && (j - 1) >= 0) {
  	board[i + 2][j - 1] = a;
  }
  if ((i - 2) >= 0 && (j - 1) >= 0) {
  	board[i - 2][j - 1] = a;
  }
  if ((i + 2) < m && (j + 1) < n) {
  	board[i + 2][j + 1] = a;
  }
  if ((i - 2) >= 0 && (j + 1) < n) {
  	board[i - 2][j + 1] = a;
  }
  if ((i + 1) < m && (j + 2) < n) {
  	board[i + 1][j + 2] = a;
  }
  if ((i - 1) >= 0 && (j + 2) < n) {
  	board[i - 1][j + 2] = a;
  }
  if ((i + 1) < m && (j - 2) >= 0) {
  	board[i + 1][j - 2] = a;
  }
  if ((i - 1) >= 0 && (j - 2) >= 0) {
  	board[i - 1][j - 2] = a;
  }
}


void queens (int qui, int quj, char ** board, int m, int n) {

  if ((qui*m)+(quj+1) >= (m*n)){}

  else {
    for (int i = qui; i < m; i++) {
      for (int j = quj; j < n; j++) {

        if (canPlace(i,j,board)) { //vai verificar se a posicao ij esta vazia

          /* crio um novo tabuleiro */
          char** new_board = new char*[m];
          for (int x = 0; x < m; x++) {
            new_board[x] = new char[n];
          }

          //coloco a rainha no tabuleiro e calculo suas posicoes de ataque
          if (place(i, j, 'Q', 'a', board, new_board, m, n)){
            board[i][j] = '*';
            queens(i, j, board, m, j);
          }
          else {
            board[i][j] = 'Q';
            queens(i, j, new_board, m, n);
          }

          //libera memoria
          for (int x = 0; x < m; x++) {
            delete[] new_board[x];
          }
          delete[] new_board;
        }
      }
    }
  }
}


int attackqueens(int oi, int oj, char a, char** board, int m, int n){

  int i,j;
  i = oi;
  j = oj;

  //esta olhando a diagonal (de baixo pra cima) (da direita pra esquerda)
  while ((i > 0) && (j > 0)) {
    if ((board[i-1][j-1] != 'K') || (board[i-1][j-1] != 'A') || (board[i-1][j-1] != 'Q') || (board[i-1][j-1] != 'q')){
      //board[i-1][j-1] = a;
      if ((board[i-1][j-1] == 'K')) {
        return(1);
      } else {
        board[i-1][j-1] = a;
      }
    }
    i--;
    j--;
  }

  i = oi;
  j = oj;

  //esta olhando olhando as linhas, indo de baixo pra cima
  while (i > 0) {
    if (board[i-1][j] == 'Q') {
      return(1);
    }
    if (board[i-1][j] == 'K') {
      return(1);
    } else {
      board[i-1][j] = a;
    }
    i--;
  }

  i = oi;
  j = oj;
  //esta olhando a diagonal (de baixo pra cima) (esquerda pra direita)
  while ((i > 0) && (j < n)) {
    if (board[i-1][j+1] == 'Q') {
      return(1);
    }
    if (board[i-1][j+1] == 'K') {
      return(1);
    } else {
      board[i-1][j+1] = a;
    }
    i--;
    j++;
  }

  i = oi;
  j = oj;
  //esta olhando olhando as colunas, da direita pra esquerda
  while (j > 0) {
    if (board[i][j-1] == 'Q') {
      return(1);
    }
    if (board[i][j-1] == 'K') {
      return(1);
    } else {
        board[i][j-1] = a;
    }
    j--;
  }

  i = oi;
  j = oj;
  //esta olhando olhando as colunas, da esquerda para a direita
  while (j+1 < n) {
    if (board[i][j+1] == 'Q') {
      return(1);
    }
    if (board[i][j+1] == 'K') {
      return(1);
    } else {
       board[i][j+1] = a;
    }
    j++;
  }

  i = oi;
  j = oj;
  //esta olhando a diagonal (de cima pra baixo) (da direita pra esquerda)
  while ((i+1 < m) && (j > 0)) {
    if (board[i+1][j-1] == 'Q') {
      return(1);
    }
    if (board[i+1][j-1] == 'K') {
      return(1);
    } else {
       board[i+1][j-1] = a;
    }
    i++;
    j--;
  }

  i = oi;
  j = oj;
  //esta olhando as linhas, indo de baixo pra cima
  while (i+1 < m) {
    if (board[i+1][j] == 'Q') {
      return(1);
    }
    if (board[i+1][j] == 'K') {
      return(1);
    } else {
       board[i+1][j] = a;
    }
    i++;
  }

  i = oi;
  j = oj;
  //esta olhando a diagonal (de cima pra baixo) (da esquerda pra direita)
  while ((i+1 < m) && (j+1 < n)) {
    if (board[i+1][j+1] == 'Q') {
      return(1);
    }
    if (board[i+1][j+1] == 'K') {
      return(1);
    } else {
       board[i+1][j+1] = a;
    }
    i++;
    j++;
  }
  return(0);
  }



/*
########################################################################
          FUNCOES DE PRINT DO TABULEIRO
########################################################################
*/
/* This function is used to create an empty m*n board */
void makeBoard(char** board, int m, int n){
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = '_';
		}
	}
}

/* This function displays our board */
void displayBoard(char** board, int m, int n){
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << "\t" << board[i][j] << " ";
		}
		cout << endl;
	}
}

/* This function displays our board */
void displayBoardCoordenatesMatrix(char** board, int m, int n){
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((board[i][j] != 'K') && (board[i][j] != 'Q')) {
				cout << "\t" << (i*m)+(j+1) << ";" ;
			} else {
				cout << "\t" << board[i][j] << ";" ;
			}
		}
		cout << endl;
	}
	cout << endl;
}

/* This function displays our board */
void displayResult(char** board, int m, int n){
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 'K') {
				cout << "K" << (i*m)+(j+1) << ";" ;
			}
			if (board[i][j] == 'Q') {
				cout << "Q" << (i*m)+(j+1) << ";" ;
			}
		}
	}
	cout << endl;
}


/* This function displays our board */
void displayBoardCoordenates(char** board, int m, int n){
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if ((board[i][j] == 'K') || (board[i][j] == 'Q')) {
				//cout << m << board[i][j] << i << j << (i*m)+(j+1) << ";" ;
				cout << (i*m)+(j+1) << ";" ;
			}
		}
	}
	cout << endl;
}
