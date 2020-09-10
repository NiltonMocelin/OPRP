# CUDA version:
nvcc: NVIDIA (R) Cuda compiler driver

Copyright (c) 2005-2015 NVIDIA Corporation

Built on Tue_Aug_11_14:27:32_CDT_2015

Cuda compilation tools, release 7.5, V7.5.17


# GPU utilizada:

Device name:                GeForce GT 730

Major revision number:      2

Minor revision Number:      1

Total Global Memory:        2081751040

Total shared mem per block: 49152

Total const mem size:       65536

Warp size:                  32

Maximum block dimensions:   1024 x 1024 x 64

Maximum grid dimensions:    65535 x 65535 x 65535

Clock Rate:                 1400000

Number of muliprocessors:   2

Obs: Por mais que a gpu diga que podemos ter 1024x1024x64 threads por bloco => https://forums.developer.nvidia.com/t/run-2-multiprocessors-from-one-global-function/57199/2 diz que só é possivel utilizar 1024 threads. Assim, utilizamos no maximo dimThreads(32,32) pois 32x32 = 1024 (maximo de threads por bloco)

# Multiplicacao CUDA com matrizes não quadradas
- [x] Leitura das matrizes em arquivo
- [x] Inicialização dos vetores com o valor dos arquivos
- [x] Alterando os valores no DEVICE e trazendo para o HOST
- [x] Modelar a multiplicação
- [x] Entender como utilizar os blocos e threads
- [x] Entender como utilizar os indices (pois as matrizes não são quadradas)
- [x] Corrigir: Multiplicacao ocorre, mas não soma na celula (problema de concorrencia)
- [X] Implementar multiplicacao sequencial
- [X] Marcar tempo e comparar com a versao sequencial
- [x] Melhorar: Na funciona para matrizes grandes - provavelmente precise entender melhor a questao dos blocos e threads da GPU
- [X] Adicionado SpeedUp
