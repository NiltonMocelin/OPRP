#include "funcoes.h"

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

/* If the position is empty,
   place the knight */
bool canPlace(int i, int j, char** board)
{
    if (board[i][j] == '_')
        return true;
    else
        return false;
}

/* This function is used to create an empty m*n board */
void makeBoard(char** board, int m, int n)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = '_';
        }
    }
}

/* Place the knight at [i][j] position
   on board */

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
         attack(i, j, a, new_board, m, n); //marcar todas as posicoes que podem ser atacadas pelo cavaleiro no novo tabuleiro
       }
       else { //se a variavel k == rainha, entao
         return(attackqueens(i, j, a, new_board, m, n));
       }
       return (0);
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


/* This function displays our board */
void displayBoard(char** board, int m, int n)
{
    cout << endl
         << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << " " << board[i][j] << " ";
        }
        cout << endl;
    }
}

/* This function marks all the attacking
 position of a knight placed at board[i][j]
 position */
void attack(int i, int j, char a, char** board, int m, int n)
{

    /* conditions to ensure that the
       block to be checked is inside the board */
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
          //nao entendi essa parte
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

/* Function for placing knights on board
   such that they don't attack each other */
void kkn(int k, int sti, int stj, char** board, int m, int n)
{

    /* If there are no knights left to be placed,
     display the board and increment the count */
    if (k == 0) {
        //ao inves de mostrar o tabuleiro, chamar a funcao de posicionar as rainhas
        //se nao for possivel posicionar as N-K rainhas, sair e nao printar o resultado
        //se posicionou as N-k rainhas, mostrar a matriz e finalizar o programa
        queens (0, 0, board, m, n);
        // displayBoard(board);

        displayBoardCoordenatesMatrix(board, m, n);
        displayResult(board, m, n);

        exit(0);
        // queremos apenas uma solucao
        // count++;
    }
    else {

        /* Loop for checking all the
       positions on m*n board */
        for (int i = sti; i < m; i++) {
            for (int j = stj; j < n; j++) {

                /* Is it possible to place knight at
           [i][j] position on board? */
                if (canPlace(i, j, board)) {

                    /* Create a a new board and place the
                      new knight on it */
                    char** new_board = new char*[m];
                    for (int x = 0; x < m; x++) {
                        new_board[x] = new char[n];
                    }
                    place(i, j, 'K', 'A', board, new_board,m,n);

                    /* Call the function recursively for
                      (k-1) leftover knights */
                    kkn(k - 1, i, j, new_board, m, n);

                    /* Delete the new board
                    to free up the memory */
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
