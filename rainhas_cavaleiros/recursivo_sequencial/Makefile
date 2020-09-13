output: main.o funcoes.o
			 g++ -std=c++0x -Wall main.o funcoes.o -o output

main.o: main.cpp
			 g++ -c main.cpp

funcoes.o: funcoes.cpp funcoes.cpp
			 g++ -c funcoes.cpp

clean:
			 rm *.o output
