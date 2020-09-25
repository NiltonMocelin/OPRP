
// C++ implementation of the above approach
#include "funcoes.h"

/* m*n is the board dimension
k is the number of knights to be placed on board
count is the number of possible solutions */

// Driver code
int main(int argc, char *argv[])
{
    int m = 0, n = 0, k = 0;
    if(argc!=3){

printf("Erro: escreva <dimensao> <qtdCavaleiros>\n");
exit(1);
}
//m=linhas; n=colunas
   m=n=atoi(argv[1]);
   k=atoi(argv[2]);

    /* Creation of a m*n board */
    char** board = new char*[m];
    for (int i = 0; i < m; i++) {
        board[i] = new char[n];
    }
    makeBoard(board, m, n);

    printf("\nkkn_otimizado -- posiciona cavaleiros apenas\n" );
    time_i=wtime();
    kkn_otimizado(k, board, m, n);

    printf("\nkkn (cavaleiros+rainhas)\n" );
    time_i=wtime();
    kkn(k, board, m, n);

    return 0;
}
