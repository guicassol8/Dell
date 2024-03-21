#include "Sorteio.hpp"
#include <algorithm>
#include <utility>
#include <thread>
#include <chrono>

//Definicao de cores para o terminal
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_

class Interface{
	private:
		Sorteio sorteio;
		int quantApostas;
		int quantRandom;
		unordered_map<string, Pessoa*> apostadores;
    public:
		Interface(int edicao);
		Interface();
		~Interface();
		void addAposta(string nome, string cpf, unordered_set<int> aposta);
		void menu();
		void menuExplicacao();
		void menuResultado();
		void menuPremiacao(int valor);
		void printSorteio();
		bool verSair(string input);
		bool confirmaInput(string info);
		void criarCasos(int quantidade);
		unordered_set<int> randomAposta();
};

bool isNumber(string str);
bool verificaCPF(string cpf);
void clearTerminal();
void sortearAposta(unordered_set<int> &aposta);

#endif