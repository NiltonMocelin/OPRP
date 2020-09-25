# Algoritmo posicionar Cavaleiros:

- sti e stj sao utilizados para definir a partir de qual coordenada comecamos a posicionar. Geralmente, tomam o valor inicial 0 ou a coordenada da proxima celula a partir do ultimo cavaleiro removido.

- Percorremos a board[i][j], i = sti -> m e j = stj -> n, na primeira iteracao, na segunda para frente zeramos stj, pois representa a coordenada inicial. Se for possivel posicionar um cavaleiro, posicione e marque suas posicoes de ataque.

- Caso toda a matriz tenha sido percorrida. Remova o utlimo cavaleiro da board, removendo suas posicoes de ataque e remarcando as posicoes de ataque de todos os outros cavaleiros (poderia ser simplificado se a matriz fosse de inteiros, onde se a celula fosse diferente de K ou Q, seria um numero, que representa a quantidade de pecas atacando).

- Caso removermos o cavaleiro da ultima celula, sti e stj tomam valores invalidos. Para resolver, removemos mais um cavaleiro e assim o algoritmo dá a sequencia correta.

# Algoritmo posicionar Rainhas:

- Usaremos a mesma estratégia, pois o que muda são as funções e não a lógica.

- Como não sabemos quantas rainhas é possivel colocar, mas o maximo é o max_rainhas = min(n,m).

- Temos um contador de rainhas e um contador maximo. Bem como, salvamos o tabuleiro com o numero maximo de rainhas.

- Cada vez que a matriz é percorrida, verificamos se o numero de rainhas atual é maior que o maximo. Se sim, substituimos o maximo e o tabuleiro pelos atuais.

- O algoritmo para quando tento posicionar a primeira peça na ultima posicao da matriz, pq nesse caso, ja tentamos todas as possibilidades e não conseguiremos posicionar mais que 1 ou 0 rainhas.
 
