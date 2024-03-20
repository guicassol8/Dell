CFLAGS = -c -std=c++11 #-DDEBUG

all:			main

main:			main.o Pessoa.o Sorteio.o Aposta.o Interface.o
					g++ -o main main.o Pessoa.o Sorteio.o Aposta.o Interface.o

main.o:			main.cpp
					g++ ${CFLAGS} main.cpp		

Interface.o:	Interface.cpp Interface.hpp Sorteio.hpp
					g++ ${CFLAGS} Interface.cpp

Pessoa.o:		Pessoa.cpp Pessoa.hpp Aposta.hpp
					g++ ${CFLAGS} Pessoa.cpp

Sorteio.o:		Sorteio.cpp Sorteio.hpp Aposta.hpp Pessoa.hpp
					g++ ${CFLAGS} Sorteio.cpp

Aposta.o:		Aposta.cpp Aposta.hpp Pessoa.hpp
					g++ ${CFLAGS} Aposta.cpp

clean:
				rm -f main main.o Pessoa.o Sorteio.o Aposta.o Interface.o