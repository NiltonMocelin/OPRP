#include "funcoes.h"

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec + (double) t.tv_usec / 1000000;
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

int place(int i, int j, char k, char a, char** board, int m, int n){

  /* marca todas as possiveis posicoes que podem ser atacaads pelo novo cavaleiro adicionado no novo tabuleiro*/
  if (k == 'K') { //se a variavel k, passada como parametro for igual a 'K', ou seja, eh um cavaleiro
  //marcar todas as posicoes que podem ser atacadas pelo cavaleiro no novo tabuleiro
  if(attack(i, j, a, board, m, n)){//se retornar zero, ocorreu colisao, se retornar um, posicionar ::::> [refatorado] nunca vai retornar zero, devido a garantia de canPlace
    board[i][j] = k; //coloca o cavalo na ij do tabuleiro novo
    return 1;
  }
}
else { //se a variavel k == rainha, entao
  if(attackqueens(i, j, a, board, m, n)){
    board[i][j] = k;
    return 1;
  }
}
return (0);//deu ruim, pq marquei o ataque do cavaleiro mas nao posicionei -> [feeling] isso nao vai acontecer, pois nao temos rainhas nesse processo,
// entao se chegamos nessa funcao, passamos antes por canPlace, que verifica se a posicao onde estou esta com ataque, e, se nao estou sob ataque,
//nao estou atacando ninguem <-> se nao estou atacando ninguem, nao estou sob ataque. O ataque eh representado na matriz por 'a', logo se eu estivesse sob ataque, canPlace nao entrava
}


int attackqueens(int oi, int oj, char a, char** board, int m, int n)
  {
    int i,j;

    i = oi;
    j = oj;
    while ((i > 0) && (j > 0)) {
      // if ((board[i-1][j-1] != 'K') || (board[i-1][j-1] != 'A') || (board[i-1][j-1] != 'Q') || (board[i-1][j-1] != 'q')){
        //board[i-1][j-1] = a;
        if ((board[i-1][j-1] == 'K') || (board[i-1][j-1] == 'Q')) {
          return(1);
        } else {
          board[i-1][j-1] = a;
        }
      // }
      i--;
      j--;
    }

    i = oi;
    j = oj;
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
  int attack(int i, int j, char a, char** board, int m, int n)
  {

    /* conditions to ensure that the
    block to be checked is inside the board */
    if ((i + 2) < m && (j - 1) >= 0) {
      //nao precisa disso, pois se tivesse um cavaleiro nas posicoes de ataque, eu estaria sendo atacado tbm
      // if(board[i + 2][j - 1] == 'K'){ // nao temos rainhas nessa etapa|| board[i + 2][j - 1] == 'Q'){
      //   return 0;//nao pode posicionar
      // }
      //se nao, ja marca o ataque (serve pra nd msm), mentira serve para a funcao can place
      board[i + 2][j - 1]= a;
    }
    if ((i - 2) >= 0 && (j - 1) >= 0) {
      // if(board[i - 2][j - 1] == 'K'){// || board[i - 2][j - 1] == 'Q'){
      //   return 0;
      // }
      board[i - 2][j - 1] = a;
    }
    if ((i + 2) < m && (j + 1) < n) {
      // if(board[i + 2][j + 1]=='K' ){//|| board[i + 2][j + 1] =='Q'){
      //   return 0;
      // }
      board[i + 2][j + 1]= a;
    }
    if ((i - 2) >= 0 && (j + 1) < n) {
      // if(board[i - 2][j + 1]=='K'){// || board[i - 2][j + 1]=='Q'){
      //   return 0;
      // }
      board[i - 2][j + 1]= a;
    }
    if ((i + 1) < m && (j + 2) < n) {
      // if(board[i + 1][j + 2]=='K'){// || board[i + 1][j + 2]=='Q'){
      //   return 0;
      // }
      board[i + 1][j + 2] = a;
    }
    if ((i - 1) >= 0 && (j + 2) < n) {
      // if(board[i - 1][j + 2] == 'K'){// || board[i - 1][j + 2] == 'Q'){
      //   return 0;
      // }
      board[i - 1][j + 2]= a;
    }
    if ((i + 1) < m && (j - 2) >= 0) {
      // if(board[i + 1][j - 2]=='K'){// || board[i + 1][j - 2] == 'Q'){
      //   return 0;
      // }
      board[i + 1][j - 2] = a;
    }
    if ((i - 1) >= 0 && (j - 2) >= 0) {
      // if(board[i - 1][j - 2]=='K'){// || board[i - 1][j - 2]=='Q'){
      //   return 0;
      // }
      board[i - 1][j - 2]= a;
    }

    //nenhuma verificacao reclamou, entao posicione :)
    return 1;
  }

  // void queens (int qui, int quj, char ** board, int m, int n) {
  //
  //   if ((qui*m)+(quj+1) >= (m*n)){
  //
  //   }else {
  //     for (int i = qui; i < m; i++) {
  //       for (int j = quj; j < n; j++) {
  //
  //         if (canPlace(i,j,board)) { //vai verificar se a posicao ij esta vazia
  //
  //           /* crio um novo tabuleiro */
  //           char** new_board = new char*[m];
  //           for (int x = 0; x < m; x++) {
  //             new_board[x] = new char[n];
  //           }
  //
  //           //coloco a rainha no tabuleiro e calculo suas posicoes de ataque
  //           //nao entendi essa parte
  //           if (place(i, j, 'Q', 'a', board, new_board, m, n)){
  //             board[i][j] = '*';
  //             queens(i, j, board, m, n);
  //           }
  //           else {
  //             board[i][j] = 'Q';
  //             queens(i, j, new_board, m, n);
  //           }
  //
  //           //libera memoria
  //           for (int x = 0; x < m; x++) {
  //             delete[] new_board[x];
  //           }
  //           delete[] new_board;
  //         }
  //       }
  //     }
  //   }
  // }

  int tentar_posicionar_cavaleiro(int i, int j, char **board, int m, int n)
  {

    if (canPlace(i, j, board)) {//verifica se estou sob ataque
      printf("Posicionando em: [%d, %d]\n",i, j);
      // exit(0);
      return place(i, j, 'K', 'A', board ,m,n);
    }

    return 0;

  }

  void remarcar_ataque_cavaleiros(char **board, int m, int n){

    for(int i=0; i<m; i++){
      for(int j=0; j<n ; j++){
        if(board[i][j]=='K'){
          attack(i,j,'A', board,m, n);
        }
      }
    }

  }

  //remove a ultima peca, o tipo eh 'K'=cavaleiro ou 'Q' rainha
  //posicao_i e posicao_j, sao as coordenadas da peca retirada
  void remover_ultimo_X(int *posicao_i, int *posicao_j, char **board, int m, int n, char peca)
  {

    //para remover a ultima peca, fazemos a verificacao do final para o comeco
    for(int i=m-1; i>=0;i--){
      for(int j=n-1; j>=0;j--){
        if(board[i][j] == peca){
          printf("Removido [%d][%d]\n",i,j );
          board[i][j]='_';
          //remover os ataque
          attack( i, j, '_', board, m, n);
          //problema, posso ter removido o ataque de um outro cavaleiro, junto com o meu -> remarcar
          remarcar_ataque_cavaleiros(board, m, n);

          *posicao_i=i;
          *posicao_j=j;
          return;
        }
      }
    }
    *posicao_i=0;
    *posicao_j=0;
  }

  /* Function for placing knights on board
  such that they don't attack each other */
  void kkn(int k, char** board, int m, int n)
  {
    // printf("sti: %d; stj: %d\n",sti, stj );
    /* If there are no knights left to be placed,
    display the board and increment the count */
    // if (k == 0) {
    //   //ao inves de mostrar o tabuleiro, chamar a funcao de posicionar as rainhas
    //   //se nao for possivel posicionar as N-K rainhas, sair e nao printar o resultado
    //   //se posicionou as N-k rainhas, mostrar a matriz e finalizar o programa
    //   // queens (0, 0, board, m, n);
    //
    //   printf("Solucao Encontrada: tempo %.3f\n",wtime()-time_i );
    //
    //   displayBoardCoordenatesMatrix(board, m, n);
    //   displayResult(board, m, n);
    //
    //   exit(0);
    //   // queremos apenas uma solucao
    //   // count++;
    // }
    // else {
      int sti=0, stj=0;

      char** new_board = new char*[m];
      for (int x = 0; x < m; x++) {
        new_board[x] = new char[n];
      }
      makeBoard(new_board, m, n);

      //ou percorre toda a matriz e nao consegue posicionar tudo ou posicionou todos os cavaleiros
      while( (sti < n && stj < n) && k > 0){
        printf("sti:%d; stj:%d\n",sti,stj );
        //[parada] fim da matriz ou k<=0
        for (int i = sti; i < m && k > 0; i++) {
          for (int j = stj; j < n && k > 0; j++) {

            printf("i:%d; j:%d\n",i,j );
            //tentar posicionar o cavaleiro
            if(tentar_posicionar_cavaleiro(i, j, new_board, m, n)){
              //conseguiu, a matriz tem um cavaleiro a mais
              k--;//precisa posicionar um cavaleiro a menos
              printf("K:%d\n",k );
              displayBoard(new_board, m, n);
              // exit(0);
            }

          }
          stj=0;

        }

        //saiu mas nao por ter posicionado todos, logo teremos outra tentativa
        if(k>0){

          //remover_ultimo_cavaleiro retorna a posicao em j do cavaleiro removido
          int novo_j=0, novo_i=0;
          remover_ultimo_X(&novo_i, &novo_j, new_board, m, n, 'K');
          k++;//removi o ultimo%d\n",k );
              // exit(0);
          //na proxima iteracao, comecar a posicionar pela celula seguinte de onde o cavaleiro foi removido
          stj = novo_j+1;
          sti = novo_i;

          //se a proxima celula esta fora da dimensao da coluna, entao va para aproxima linha
          if(stj >=n){
            stj=0;
            sti++;
          }

          //se eu removi o ultimo, pode remover mais um pq se nao, nao temos o que fazer
          if(sti >=n){
            // sti = sti%n +1;
            remover_ultimo_X(&novo_i, &novo_j, new_board, m, n, 'K');
            k++;
            stj = novo_j+1;
            sti = novo_i;

            if(stj >=n){
              stj=0;
              sti++;
            }


          }

        }

      }

      //se saiu e k==0 -> printar a matriz
      if(k<=0){
        printf("Solucao Encontrada: tempo %.3f\n",wtime()-time_i );

        displayBoardCoordenatesMatrix(new_board, m, n);
        displayResult(new_board, m, n);

      }else{
        printf("Solucao Nao Encontrada: tempo %.3f\n",wtime()-time_i );

      }
      printf("K:%d; sti:%d; stj:%d\n",k, sti, stj );

  }
