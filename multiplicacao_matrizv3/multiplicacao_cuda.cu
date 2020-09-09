// #######################################################
//
// Exemplo (template) de multiplicação de matrizes em CUDA
// Disciplina: OPRP001 - Programação Paralela
// Prof.: Mauricio Pillon
//
// #######################################################
#include <cuda.h>
#include <stdio.h>
#include <math.h>
#include "toolsv3.h"

#define T 1024 // numero max de threads por bloco

// GPU: Multiplicação das matrizes (a) e (b), resultado em (c)
__global__ void matMult (int *da, int *db, int *dc, int *C_dev, int *Cb_dev) {
    // TODO: Alunos
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    if(i<*Cb_dev && j<*Cb_dev){
	int soma=0;

	for(int ii=0; ii< *C_dev ; ii++){

	      	soma += da[i*(*C_dev)+ii] * db[ii*(*Cb_dev)+j];
    	}
	
	dc[i*(*Cb_dev)+j] = soma;
    }


}

// GPU: Imprime índices na matriz
__global__ void printIndex (void) {
   int i = blockIdx.x * blockDim.x + threadIdx.x;
   int j = blockIdx.y * blockDim.y + threadIdx.y;

   printf ("[%d][%d]\t(x)\t%d\t%d\t%d\t(y)\t%d\t%d\t%d\n",i,j, threadIdx.x, blockIdx.x, blockDim.x,threadIdx.y, blockIdx.y, blockDim.y);
}


// GPU: Inicializa os vetores (a), (b) e (c) na Memória Global
__global__ void dirtyMem (int *da) {
   int i = blockIdx.x * blockDim.x + threadIdx.x;

   da[i] = 0;
}

// CPU: Inicializa os vetores (a) e (b)
__host__ void initvet(int *host_a, mymatriz mat_a) {
  int lin_a =mat_a.lin, col_a=mat_a.col;

  //iniciar host_a
  for (int i=0; i < lin_a; i++) {
    for (int j=0; j < col_a; j++) {
     host_a[i*col_a+j] = mat_a.matriz[i][j];
    }
  }

}

// CPU: Imprime matriz
__host__ void printMat (int *mat, int lin, int col){

	for (int j =0; j < lin && j<15; j++)
	printf("\t(%d)", j);
	printf("\n");
	for (int i=0; i < lin && i<15; i++) {
		printf("(%d)", i);
		for (int j=0; j < col && j<15; j++){
			printf("\t%d", mat[i*col+j]);
		}
		printf("\n");
	}
}

__host__ mymatriz *mmultiplicar (mymatriz *mat_a, mymatriz *mat_b) {
	mymatriz *mat_c = NULL;

	if (mat_a->col != mat_b->lin){
		printf ("Erro: Matrizes incompatíveis!\n");
		exit(1);
	}

	mat_c = (mymatriz *) malloc (sizeof(mymatriz));

	mat_c->lin = mat_a->lin;
	mat_c->col = mat_b->col;

	if (malocar(mat_c)) {	printf ("ERROR: Out of memory\n"); }

		//a(linhas) x b(colunas)
		printf("Multiplicando com ijk\n" );
		for (int i=0; i <mat_a->lin; i++){
			for (int j=0; j <mat_b->col; j++){
				mat_c->matriz[i][j]=0;
				for (int k=0; k < mat_b->lin; k++){
					mat_c->matriz[i][j] += mat_a->matriz[i][k]*mat_b->matriz[k][j];
				}
			}
		}

    return mat_c;
}

__host__ int mcomparar (mymatriz *mat_a, int *vet_c, int col){
	for (int j =0; j < mat_a->col; j++)
	for (int i=0; i < mat_a->lin; i++) {
		for (int j=0; j < mat_a->col; j++){
			if (mat_a->matriz[i][j] != vet_c[i*col+j]) {
				printf("O elemento [%d,%d] é diferente nas matrizes analisadas!", i,j);
				return 1;
			}
		}
	}
	printf("\tVERIFICADO: Matrizes identicas\n");
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
__host__ int mimprimir (mymatriz *matriz){
	int linha, coluna;
	linha = matriz->lin;
	coluna = matriz->col;

	if (linha > 15) {
		linha = 15;
	}

	if (coluna > 15) {
		coluna = 15;
	}

	for (int j =0; j < coluna; j++)
	printf("\t(%d)", j);
	printf("\n");
	for (int i=0; i < linha; i++) {
		printf("(%d)", i);
		for (int j=0; j < coluna; j++){
			printf("\t%d", matriz->matriz[i][j]);
		}
		printf("\n");
	}

	printf("\n \
	// %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
	// 	WARNING: Impressão truncada em 15x15! \n \
	// 	WARNING: Último elemento matriz[%d][%d] = %d \n \
	// %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n", \
	matriz->lin-1, matriz->col-1, matriz->matriz[matriz->lin-1][matriz->col-1]);
	return 0;
}

// CPU: função principal
int main(int argc, char const *argv[]) {

  //Lendo matrizes de arquivo, utilizar os arquivos do gerador de arquivos para ter as matrizes
// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
  // DECLARAÇÃO de VARIÁVEIS
  mymatriz mat_a, mat_b;
  // char filename[100];
  FILE *fmat;
  int nr_line;
  int *vet_line = NULL;
  int L, C, Ca, Lb;
  // double start_time, end_time;
  // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

  if (argc != 3){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
		exit (1);
	}

  fmat = fopen(argv[1],"r");

  if (fmat == NULL) {
      printf("Error: Na abertura dos arquivos.");
      exit(1);
    }

    extrai_parametros_matriz(fmat, &L, &Ca, &vet_line, &nr_line);
    //return 1;
    mat_a.matriz = NULL;
    mat_a.lin = L;
    mat_a.col = Ca;
    if (malocar(&mat_a)) {
      printf ("ERROR: Out of memory\n");
    }
    filein_matriz (mat_a.matriz, L, Ca, fmat, vet_line, nr_line);
    free (vet_line);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%

    //               Leitura da Matriz B (arquivo)
    fmat = fopen(argv[2],"r");
    if (fmat == NULL) {
      printf("Error: Na abertura dos arquivos.");
      exit(1);
    }

    extrai_parametros_matriz(fmat, &Lb, &C, &vet_line, &nr_line);
    mat_b.matriz = NULL;
    mat_b.lin = Lb;
    mat_b.col = C;
    if (malocar(&mat_b)) {
      printf ("ERROR: Out of memory\n");
    }
    filein_matriz (mat_b.matriz, Lb, C, fmat, vet_line, nr_line);
    free (vet_line);
    fclose(fmat);
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%% (copiado)

  if(Ca != Lb){
    printf("Error: Matrizes incompativeis\n");
    exit(1);
  }

  //multiplicando e tomando o tempo
  printf("Multiplicacao sequencial\n");
  double tempo_s=wtime();
  mymatriz *mult_sequencial = mmultiplicar(&mat_a, &mat_b);
  tempo_s = wtime()-tempo_s;

  int *a, *b, *c; //matrizes (vetores) em host
  int *dev_a, *dev_b, *dev_c;//matrizes (vetores) em device
  int size_a, size_b, size_c;

  // Alocação de matriz quadrada
  size_a = L * Ca * sizeof(int);
  size_b = Lb * C * sizeof(int);
  size_c = L * C * sizeof(int);

  cudaError_t error_c;
  // Alocação de memória no host
  error_c = cudaMallocHost((void **) &a, size_a);
  if(error_c != cudaSuccess)
  {
     printf("GPUassert: %s\n", cudaGetErrorString(error_c));
  }

  error_c=cudaMallocHost((void **) &b, size_b);
  if(error_c != cudaSuccess)
  {
     printf("GPUassert: %s\n", cudaGetErrorString(error_c));
  }

  error_c=cudaMallocHost((void **) &c, size_c);
  if(error_c != cudaSuccess)
  {
     printf("GPUassert: %s\n", cudaGetErrorString(error_c));
  }

  initvet(a, mat_a);
  initvet(b, mat_b);

  // Impressão na tela dos valores dos vetores
  printf ("\t ### Valores Lidos de arquivo na CPU ###\n");
  printf ("\t ### Matriz (a) ### \n");
  printMat(a, L, Ca);
  printf ("\t ### Matriz (b) ### \n");
  printMat(b,Lb, C);

  // Alocação de memória na GPU para os vetores (a,b e c)
  cudaMalloc ((void **) &dev_a, size_a);
  cudaMalloc ((void **) &dev_b, size_b);
  cudaMalloc ((void **) &dev_c, size_c);

  ////////////////////////////////// Parte inutil (carregar valores nas posicoes antes de enviar os valores corretos///////////////////////////////////////
  //Número de blocos e threads p/ dimensões (x,y)
  dim3 dimBlock (1, 1); //dimensao de um bloco (1,1) = 1024 (threads)
  dim3 dimThreads(L, Ca);//assim podemos multiplicar ate L*C=1024 (pelo q entendi)

  if(L*Ca > T){ // Dimensoes ultrapassam a quantidade de threads de um so bloco
	dimThreads.x=(int) ceil(sqrt(T));
        dimThreads.y=(int) ceil(sqrt(T));

        dimBlock.x= (int) ceil(double(L)/sqrt(T));//sqrt(1024)
        dimBlock.y= (int) ceil(double(Ca)/sqrt(T));//sqrt(1024) pois 32*32=1024 e precisamos L*C < 1024
  }

  // Atribui valores iniciais aos vetores em GPU
  dirtyMem<<<dimBlock, dimThreads>>>(dev_a);
////////////////////////////////////////////////////////////
	 dimThreads.x=Lb;
         dimThreads.y=C;
         dimBlock.x= 1;
         dimBlock.y= 1;
   if(Lb*C > T){ // Dimensoes ultrapassam a quantidade de threads de um so bloco
	dimThreads.x=(int) ceil(sqrt(T));
        dimThreads.y=(int) ceil(sqrt(T));

        dimBlock.x= (int) ceil(double(Lb)/sqrt(T));//sqrt(1024)
        dimBlock.y= (int) ceil(double(C)/sqrt(T));//sqrt(1024) pois 32*32=1024 e precisamos L*C < 1024
 
 }

  dirtyMem<<<dimBlock, dimThreads>>>(dev_b);
/////////////////////////////////////////////////////////
	  dimThreads.x=L;
          dimThreads.y=C;
          dimBlock.x= 1;
          dimBlock.y= 1;
//////parte inutil menos inutil, mas ainda assim serve pra nada, carregar 0 na matriz resultante//
   if(L*C > T){ // Dimensoes ultrapassam a quantidade de threads de um so bloco
  
	dimThreads.x=(int) ceil(sqrt(T));
        dimThreads.y=(int) ceil(sqrt(T));

        dimBlock.x= (int) ceil(double(L)/sqrt(T));//sqrt(1024)
        dimBlock.y= (int) ceil(double(C)/sqrt(T));//sqrt(1024) pois 32*32=1024 e precisamos L*C < 1024
 }
  dirtyMem<<<dimBlock, dimThreads>>>(dev_c);
////////////////////////////////Fim parte inutil/////////////////////////////////////////////

  //Cópia dos vetores gerados em CPU p/ memória da GPU
  //cudaMemcpy(destino, origem, size, direcao)
  cudaMemcpy (dev_a, a, size_a, cudaMemcpyHostToDevice);
  cudaMemcpy (dev_b, b, size_b, cudaMemcpyHostToDevice);

  ////////////////////////////////// Arrumar aqui /////////////////////////////////////////
  //Número de blocos e threads p/ dimensões (x,y)
    dimThreads.x=L;
    dimThreads.y=C;
    dimBlock.x= 1;
    dimBlock.y= 1;

  if(L*C > T){ // Dimensoes ultrapassam a quantidade de threads de um so bloco
	dimThreads.x=(int) ceil(sqrt(T));
	dimThreads.y=(int) ceil(sqrt(T));

	dimBlock.x= (int) ceil(double(L)/sqrt(T));//sqrt(1024)
	dimBlock.y= (int) ceil(double(C)/sqrt(T));//sqrt(1024) pois 32*32=1024 e precisamos L*C < 1024
  }

  int *C_dev, *Cb_dev;//c_dev = Ca (matrizA) e Cb_dev=C (matrizb)
  cudaMalloc((void **) &C_dev, sizeof(int));
  cudaMalloc((void **) &Cb_dev, sizeof(int));
  cudaMemcpy (C_dev, &Ca, sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(Cb_dev, &C, sizeof(int), cudaMemcpyHostToDevice);

  ///////////////////////////////////////////////////////////////////////////////////////
  // Execução do kernel matMult em GPU
  printf("Multiplicacao CUDA\n");
  double tempo_c = wtime();
  matMult<<< dimBlock, dimThreads>>>(dev_a, dev_b, dev_c, C_dev, Cb_dev);

  cudaDeviceSynchronize();

  // Cópia do vetor (c) da GPU (Memória Global) para CPU
  cudaMemcpy (c, dev_c, size_c, cudaMemcpyDeviceToHost);
  tempo_c = wtime()- tempo_c;
  ///////////////////////////////////////////////////////////////////////////////////////

  printf ("\t ### [CUDA] Matriz (c) ### \n");
  printMat(c, L, C);

  printf("\n\t ### [sequencial] Matriz ###\n");
  mimprimir(mult_sequencial);

  printf("Comparando as matrizes:\n");
  mcomparar(mult_sequencial, c, C);
  printf("Tempo de execucao sequencial: %.3f\n", tempo_s);
  printf("Tempo de execucao CUDA: %.3f\n", tempo_c);

  // Libera a Memória Global (GPU)
  cudaFree(dev_a);
  cudaFree(dev_b);
  cudaFree(dev_c);

  // Libera a Memória Global (CPU)
  cudaFreeHost(a);
  cudaFreeHost(b);
  cudaFreeHost(c);

  return 0;
}
