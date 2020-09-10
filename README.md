# OPRP
Disciplina optativa de programação paralela UDESC - CCT

Obs: sempre deve copiar para a maquina física para utilizar (a menos que vc tenha uma gpu nvidia e o compilador nvcc instalado)
- 

- GPU utilizada:
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


# TODO
Versao atual v3:
[CORRIGIDO] Aparentemente o problema estava que nos limitavamos o indice "i" para o tamanho da matriz A em colunas.
Entretanto, nos geramos uma thread para cada multiplicacao de linha com coluna.
Por isso, o limite de "i" deve ser a qtd de linhas, pois assim teremos os indices das linhas para fazer as multiplicacaoes


# Colaboradores:
- Lucas Cobucci
- Nilton Mocelin

