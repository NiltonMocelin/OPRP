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

//isso tem q tirar
#define N 4
#define T 1024 // numero max de threads por bloco

// GPU: Multiplicação das matrizes (a) e (b), resultado em (c)
__global__ void matMult (int *da, int *db, int *dc, int *C_dev) {
    // TODO: Alunos
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;

    int soma =0;

    for(int ii=0; ii< *C_dev ; ii++){

      printf("[%d]= da: %d db:%d\n",i*blockDim.y+j, i*(*C_dev)+ii, ii*(blockDim.y) + j);
      soma += da[i*(*C_dev)+ii] * db[ii*blockDim.y+j];
    }

    dc[i*blockDim.y+j] = soma;


}

// GPU: Imprime índices na matriz
__global__ void printIndex (void) {
   int i = blockIdx.x * blockDim.x + threadIdx.x;
   int j = blockIdx.y * blockDim.y + threadIdx.y;

   printf ("[%d][%d]=%d\t(x)\t%d\t%d\t%d\t(y)\t%d\t%d\t%d\n",i,j,(i*N+j), threadIdx.x, blockIdx.x, blockDim.x,threadIdx.y, blockIdx.y, blockDim.y);
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
      printf("host[%d] = %d\n", i*col_a+j, mat_a.matriz[i][j]);
     host_a[i*col_a+j] = mat_a.matriz[i][j];
    }
  }

}

// CPU: Imprime matriz
__host__ void printMat (int *mat, int lin, int col){

	for (int j =0; j < lin; j++)
	printf("\t(%d)", j);
	printf("\n");
	for (int i=0; i < lin; i++) {
		printf("(%d)", i);
		for (int j=0; j < col; j++){
			printf("\t%d", mat[i*col+j]);
		}
		printf("\n");
	}
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

  int *a, *b, *c; //matrizes (vetores) em host
  int *dev_a, *dev_b, *dev_c;//matrizes (vetores) em device
  int size_a, size_b, size_c;

  printf("R1\n");
  // Alocação de matriz quadrada
  size_a = L * Ca * sizeof(int);
  size_b = Lb * C * sizeof(int);
  size_c = L * C * sizeof(int);
  printf("R2\n");

  printf("R3\n");

  cudaError_t error_c;

  // // Alocação de memória no host
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

  printf("R4\n");

  printf("B1\n");
  initvet(a, mat_a);
  initvet(b, mat_b);
  printf("B2\n");

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

  // Atribui valores iniciais aos vetores em GPU
  dirtyMem<<<1, L*Ca>>>(dev_a);
  dirtyMem<<<1, C*Lb>>>(dev_b);
  dirtyMem<<<1, C*L>>>(dev_c);

  ///////////////////////////// teste ///////////////////////////////////////
  //verificar os indices
  // printf("Indice A\n");
  // printIndex<<<1, L*Ca>>>();
  // printf("\nIndice B\n");
  // printIndex<<<1, C*Lb>>>();
  // printf("\nIndice C\n");
  // printIndex<<<1, L*C>>>();
  ////Cópia GPU para CPU
  // cudaMemcpy (a, dev_a, size_a, cudaMemcpyDeviceToHost);
  // cudaMemcpy (b, dev_b, size_b, cudaMemcpyDeviceToHost);
  // cudaMemcpy (c, dev_c, size_c, cudaMemcpyDeviceToHost);
  ////Impressão na tela dos valores dos vetores
  // printf ("\t ### Valores Inicializados na GPU ###\n");
  // printf ("\t ### Matriz (a) ### \n");
  // printMat(a, L, Ca);
  // printf ("\t ### Matriz (b) ### \n");
  // printMat(b,Lb, C);
  // printf ("\t ### Matriz (c) ### \n");
  // printMat(c, L, C);
  ///////////////////////////// teste ///////////////////////////////////////


  //Cópia dos vetores gerados em CPU p/ memória da GPU
  //cudaMemcpy(destino, origem, size, direcao)
  cudaMemcpy (dev_a, a, size_a, cudaMemcpyHostToDevice);
  cudaMemcpy (dev_b, b, size_b, cudaMemcpyHostToDevice);

  // int L_max = L, C_max = C;
  // if(Lb > L){
  //   L_max = Lb;
  // }
  // if(Ca > C){
  //   C_max = Ca;
  // }

  ////////////////////////////////// Arrumar aqui /////////////////////////////////////////
  //alocar no device o tamanho das matrizes
  // int *linA_dev=cudaMalloc((void **) &linA_dev, sizeof(int)), *colA_dev=cudaMalloc((void **) &colA_dev, sizeof(int)), *linB_dev=cudaMalloc((void **) &linB_dev, sizeof(int)), *colB_dev=cudaMalloc((void **) &colB_dev, sizeof(int));

  //Número de blocos e threads p/ dimensões (x,y)
  dim3 dimBlock (1, 1); //dimensao de um bloco (1,1) = 65k x 65k (threads)
  dim3 dimThreads(L, C);//assim podemos multiplicar ate 65k x 65k (pelo q entendi)
  int *C_dev;
  cudaMalloc((void **) &C_dev, sizeof(int));
  cudaMemcpy (C_dev, &Ca, sizeof(int), cudaMemcpyHostToDevice);

  // Imprime as posições acessadas pelo dimBlock e dimThreads
  printIndex<<< dimBlock, dimThreads>>>();

  // // Execução do kernel matMult em GPU
  matMult<<< dimBlock, dimThreads>>>(dev_a, dev_b, dev_c, C_dev);
  cudaDeviceSynchronize();

  ///////////////////////////////////////////////////////////////////////////////////////
  // Cópia do vetor (c) da GPU (Memória Global) para CPU
  cudaMemcpy (c, dev_c, size_c, cudaMemcpyDeviceToHost);

  //Impressão na tela dos valores dos vetores
  printf ("\t ### Valores após processamento em GPU ###\n");
  printf ("\t ### Matriz (a) ### \n");
  printMat(a, L, Ca);
  printf ("\t ### Matriz (b) ### \n");
  printMat(b,Lb, C);
  printf ("\t ### Matriz (c) ### \n");
  printMat(c, L, C);

  // Libera a Memória Global (GPU)
  cudaFree(dev_a);
  cudaFree(dev_b);
  cudaFree(dev_c);
  printf("A1\n");
  // Libera a Memória Global (CPU)
  cudaFreeHost(a);
  cudaFreeHost(b);
  cudaFreeHost(c);
  printf("A2\n");
  return 0;
}
