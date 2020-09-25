# Algoritmo posicionar Cavaleiros:

- sti e stj sao utilizados para definir a partir de qual coordenada comecamos a posicionar. Geralmente, tomam o valor inicial 0 ou a coordenada da proxima celula a partir do ultimo cavaleiro removido.

- Percorremos a board[i][j], i = sti -> m e j = stj -> n, na primeira iteracao, na segunda para frente zeramos stj, pois representa a coordenada inicial. Se for possivel posicionar um cavaleiro, posicione e marque suas posicoes de ataque.

- Caso toda a matriz tenha sido percorrida. Remova o utlimo cavaleiro da board, removendo suas posicoes de ataque e remarcando as posicoes de ataque de todos os outros cavaleiros (poderia ser simplificado se a matriz fosse de inteiros, onde se a celula fosse diferente de K ou Q, seria um numero, que representa a quantidade de pecas atacando).

- Caso removermos o cavaleiro da ultima celula, sti e stj tomam valores invalidos. Para resolver, removemos mais um cavaleiro e assim o algoritmo dá a sequencia correta.

# Algoritmo posicionar Rainhas:

- Usaremos a mesma estratégia, pois o que muda são as funções e não a lógica.
