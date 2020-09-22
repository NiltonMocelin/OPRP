# OPRP
Disciplina optativa de programação paralela UDESC - CCT

Obs: Para usar CUDA sempre deve copiar para a maquina física para utilizar (a menos que vc tenha uma gpu nvidia e o compilador nvcc instalado)
- 

# Problema dos cavaleiros mesclado com rainhas:

Posicionar K cavaleiros e então posicionar o maximo de rainhas que for possivel.

Atualmente:
- Versão recursiva do prof
- Versão recursiva copiada do github de alguém, que é muito proximo da do prof

[ ] Remover a recursão das funções
[ ] Paralelizar

# Versao atual multiplicação de matrizes CUDA v3:

[CORRIGIDO] Aparentemente o problema estava que nos limitavamos o indice "i" para o tamanho da matriz A em colunas.

Entretanto, nos geramos uma thread para cada multiplicacao de linha com coluna.

Por isso, o limite de "i" deve ser a qtd de linhas, pois assim teremos os indices das linhas para fazer as multiplicacaoes


# Colaboradores:
- Lucas Cobucci
- Nilton Mocelin

