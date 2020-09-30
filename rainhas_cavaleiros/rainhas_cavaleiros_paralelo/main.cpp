
// C++ implementation of the above approach
#include "funcoes.h"

/* m*n is the board dimension
k is the number of knights to be placed on board
count is the number of possible solutions */

// Driver code
int main(int argc, char *argv[])
{
  int m = 0, n = 0, k = 0;

  //tratando os parametros de entrada
  if(argc!=3){

    printf("Erro: escreva <dimensao> <qtdCavaleiros>\n");
    exit(1);
  }
  //m=linhas; n=colunas
  m=n=atoi(argv[1]);
  k=atoi(argv[2]);

  //montando o tabuleiro
  /* Creation of a m*n board */
  char** board = new char*[m];
  for (int i = 0; i < m; i++) {
    board[i] = new char[n];
  }
  makeBoard(board, m, n);

  //------------------- Posicionando ----------------------------------------//
  //inicializando mutex do openmp
  omp_init_lock(&lock);
  omp_set_nested(1);//habilita threads aninhadas

  // printf("\nkkn_otimizado -- posiciona cavaleiros apenas\n" );
  // time_i=wtime();
  // kkn_otimizado(k, board, m, n);

  // printf("Max threads: %d\n", omp_get_max_threads());

  flag1 = K_CONTINUAR;
  flag2 = Q_CONTINUAR;


  printf("\nkkn (cavaleiros+rainhas)\n" );
  time_i=wtime();

  //escalonar a tarefa
  #pragma omp parallel for
  for(int i=0; i<omp_get_max_threads(); i++){

    int ii=0, jj = i* ((m*n-k)/omp_get_max_threads());

    while(jj >= n){
      jj-=n;
      ii++;
    }

    // printf("id:%d || i: %d -> [%d][%d]\n",omp_get_thread_num(), i , ii, jj );
    kkn(ii,jj, k, board, m, n);
  }

  printf("[Cavaleiros] Solucao Nao Encontrada: tempo %.3f\n",wtime()-time_i);

  //destruindo o mutex
  omp_destroy_lock(&lock);

  return 0;
}
