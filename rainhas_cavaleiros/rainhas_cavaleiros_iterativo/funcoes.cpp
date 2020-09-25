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
return (0);
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
          return(0);
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
        return(0);
      }
      if (board[i-1][j] == 'K') {
        return(0);
      } else {
        board[i-1][j] = a;
      }
      i--;
    }

    i = oi;
    j = oj;
    while ((i > 0) && (j < n)) {
      if (board[i-1][j+1] == 'Q') {
        return(0);
      }
      if (board[i-1][j+1] == 'K') {
        return(0);
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
        return(0);
      }
      if (board[i][j-1] == 'K') {
        return(0);
      } else {
        board[i][j-1] = a;
      }
      j--;
    }

    i = oi;
    j = oj;
    while (j+1 < n) {
      if (board[i][j+1] == 'Q') {
        return(0);
      }
      if (board[i][j+1] == 'K') {
        return(0);
      } else {
        board[i][j+1] = a;
      }
      j++;
    }

    i = oi;
    j = oj;
    while ((i+1 < m) && (j > 0)) {
      if (board[i+1][j-1] == 'Q') {
        return(0);
      }
      if (board[i+1][j-1] == 'K') {
        return(0);
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
        return(0);
      }
      if (board[i+1][j] == 'K') {
        return(0);
      } else {
        board[i+1][j] = a;
      }
      i++;
    }

    i = oi;
    j = oj;
    while ((i+1 < m) && (j+1 < n)) {
      if (board[i+1][j+1] == 'Q') {
        return(0);
      }
      if (board[i+1][j+1] == 'K') {
        return(0);
      } else {
        board[i+1][j+1] = a;
      }
      i++;
      j++;
    }
    return(1);
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

  void queens (char ** board, int m, int n) {

    int sti=0, stj=0, melhor_rainhas=0;

    char** melhor_tabuleiro = new char*[m];
    for (int x = 0; x < m; x++) {
      melhor_tabuleiro[x] = new char[n];
    }
    makeBoard(melhor_tabuleiro, m, n);

    char** new_board = new char*[m];
    for (int x = 0; x < m; x++) {
      new_board[x] = new char[n];
    }
    makeBoard(new_board, m, n);


    int rainhas_atual=0;

    while(sti < n && stj < n && rainhas_atual < m){
      printf("sti:%d; stj:%d\n",sti,stj );
      //[parada] fim da matriz ou rainhas = m
      for (int i = sti; i < m && rainhas_atual < m; i++) {
        for (int j = stj; j < n && rainhas_atual < m; j++) {

          printf("i:%d; j:%d\n",i,j );
          //tentar posicionar a rainha
          if(tentar_posicionar_peca(i, j, new_board, m, n, 'Q')){

            //conseguiu, a matriz tem um cavaleiro a mais
            rainhas_atual++;//precisa posicionar um cavaleiro a menos
            printf("Q:%d\n",rainhas_atual );
            displayBoard(new_board, m, n);
            // exit(0);
          }

        }
        stj=0;

      }

      if(rainhas_atual > melhor_rainhas){
        melhor_rainhas = rainhas_atual;

        //o novo melhor eh o tabuleiro atual
        for(int i=0; i<m; i++){
          for(int j=0; j<n; j++){
            melhor_tabuleiro[i][j] = new_board[i][j];
          }
        }

      }

      //saiu mas nao por ter posicionado todos, logo teremos outra tentativa
      if(rainhas_atual<m){

        //remover_ultimo_cavaleiro retorna a posicao em j do cavaleiro removido
        int novo_j=0, novo_i=0;
        remover_ultima_peca(&novo_i, &novo_j, new_board, m, n, 'Q');
        rainhas_atual--;//removi o ultimo%d\n",k );
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
          if(remover_ultima_peca(&novo_i, &novo_j, new_board, m, n, 'Q')){
          rainhas_atual--;
          stj = novo_j+1;
          sti = novo_i;

          if(stj >=n){
            stj=0;
            sti++;
          }

        }else{      //se estou posicionando o primeiro cavaleiro na ultima celula mas ainda teria de posicionar mais, entao nao ha solucao
          break;
        }
        }

      }

    }

    //se saiu e k==0 -> printar a matriz
    if(melhor_rainhas>0){

      printf("-------------------------------------------------------\n");

      displayBoardCoordenatesMatrix(melhor_tabuleiro, m, n);
      displayResult(melhor_tabuleiro, m, n);

      printf("Solucao Encontrada - %d rainhas posicionadas: tempo %.3f\n",melhor_rainhas, wtime()-time_i );

    }else{
      printf("Solucao Nao Encontrada: tempo %.3f\n",wtime()-time_i );

    }
    printf("melhor_rainhas:%d; sti:%d; stj:%d\n",melhor_rainhas, sti, stj );


  }

  int tentar_posicionar_peca(int i, int j, char **board, int m, int n, char peca)
  {

    if (canPlace(i, j, board)) {//verifica se estou sob ataque
//     printf("Posicionando em: [%d, %d]\n",i, j);
      // exit(0);
      return place(i, j, peca, 'A', board ,m,n);
    }

    return 0;

  }

  void remarcar_ataque_pecas(char **board, int m, int n){

    for(int i=0; i<m; i++){
      for(int j=0; j<n ; j++){
        if(board[i][j]=='K'){
            attack(i,j,'A', board,m, n);
        } else if (board[i][j]=='Q'){
            attackqueens(i, j, 'A', board, m, n);
        }
      }
    }

  }

  //remove a ultima peca, o tipo eh 'K'=cavaleiro ou 'Q' rainha
  //posicao_i e posicao_j, sao as coordenadas da peca retirada
  int remover_ultima_peca(int *posicao_i, int *posicao_j, char **board, int m, int n, char peca)
  {

    //para remover a ultima peca, fazemos a verificacao do final para o comeco
    for(int i=m-1; i>=0;i--){
      for(int j=n-1; j>=0;j--){
        if(board[i][j] == peca){
//         printf("Removido [%d][%d]\n",i,j );
          board[i][j]='_';

          //remover os ataque
          if(peca == 'K'){
            attack( i, j, '_', board, m, n);
          }else{
            attackqueens(i, j, '_', board, m, n);
          }
          //problema, posso ter removido o ataque de um outro cavaleiro, junto com o meu -> remarcar
          remarcar_ataque_pecas(board, m, n);

          *posicao_i=i;
          *posicao_j=j;
          return 1;
        }
      }
    }
    *posicao_i=0;
    *posicao_j=0;
    return 0; //nao tem o que remover :) nao encontrou resposta!
  }

  void kkn_otimizado(int k, char** board, int m, int n){

    if(ceil(m*n / 2.0) < k){

      printf("Solucao nao encontrada\n");
      return;
    }

    int qtd_cavaleiros = k;

    for(int i=0; i<m && k>0;i++){
      int stj=i%2;
      // printf("stj: %d\n",stj );
      for(int j=stj; j<n && k>0;j+=2){
        // printf("[%d][%d]\n",i,j );
        k--;
        board[i][j]='K';
      }
    }

    displayBoardCoordenatesMatrix(board, m, n);
    displayResult(board, m, n);
    printf("Solucao Encontrada - %d cavaleiros posicionados: tempo %.3f\n",qtd_cavaleiros, wtime()-time_i );




  }

  /* Function for placing knights on board
  such that they don't attack each other */
  void kkn(int k, char** board, int m, int n)
  {
      int sti=0, stj=0, qtd_cavaleiros=k;

      char** new_board = new char*[m];
      for (int x = 0; x < m; x++) {
        new_board[x] = new char[n];
      }
      makeBoard(new_board, m, n);

      //ou percorre toda a matriz e nao consegue posicionar tudo ou posicionou todos os cavaleiros
      while( (sti < n && stj < n) && k > 0){
//       printf("sti:%d; stj:%d\n",sti,stj );
        //[parada] fim da matriz ou k<=0
        for (int i = sti; i < m && k > 0; i++) {
          for (int j = stj; j < n && k > 0; j++) {

//           printf("i:%d; j:%d\n",i,j );
            //tentar posicionar o cavaleiro
            if(tentar_posicionar_peca(i, j, new_board, m, n, 'K')){

              //conseguiu, a matriz tem um cavaleiro a mais
              k--;//precisa posicionar um cavaleiro a menos
//             printf("K:%d\n",k );
//             displayBoard(new_board, m, n);
              // exit(0);
            }

          }
          stj=0;

        }

        //saiu mas nao por ter posicionado todos, logo teremos outra tentativa
        if(k>0){

          //remover_ultimo_cavaleiro retorna a posicao em j do cavaleiro removido
          int novo_j=0, novo_i=0;
          remover_ultima_peca(&novo_i, &novo_j, new_board, m, n, 'K');
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
            if(remover_ultima_peca(&novo_i, &novo_j, new_board, m, n, 'K')){
            k++;
            stj = novo_j+1;
            sti = novo_i;

            if(stj >=n){
              stj=0;
              sti++;
            }

          }else{      //se estou posicionando o primeiro cavaleiro na ultima celula mas ainda teria de posicionar mais, entao nao ha solucao
            break;
          }
          }

        }

      }

      //se saiu e k==0 -> printar a matriz
      if(k<=0){

        printf("-------------------------------------------------------\n");

        displayBoardCoordenatesMatrix(new_board, m, n);
        displayResult(new_board, m, n);

        printf("Solucao Encontrada - %d cavaleiros posicionados: tempo %.3f\n",qtd_cavaleiros, wtime()-time_i );

      }else{
        printf("Solucao Nao Encontrada: tempo %.3f\n",wtime()-time_i );

      }
      printf("K:%d; sti:%d; stj:%d\n",k, sti, stj );

  }
