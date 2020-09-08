# GNU Makefile

CC = gcc
CCFLAGS = -Wall -O3
LDFLAGS = -lm
TARGET = gera_matrizv3 help

all: $(TARGET)

gera_matrizv3: gera_matrizv3.c matrizv3.c toolsv3.c
			$(CC) $(CCFLAGS) matrizv3.c toolsv3.c gera_matrizv3.c -o $@ $(LDFLAGS)

help:
	@echo
	@echo
	@echo "####### Exemplo de Execução obs: sem os < > #######"
	@echo "./gera_matrizv3 <qtd_linhas> <qtd_colunas>"
	@echo "make help, make all, make gera_matrizv3, make clean, make mapclean"

clean:
	-rm -f gera_matrizv3 *.map

mapclean:
	-rm -f *.map
