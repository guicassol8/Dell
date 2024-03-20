#include "Sorteio.hpp"
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <utility>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>

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
		unordered_map<string, Pessoa*> apostadores;
    public:
		Interface(int edicao);
		Interface();
		~Interface();
		void addAposta(string nome, string cpf, unordered_set<int> aposta);
		void menu();
		void menuAposta();
		void menuSorteio();
		void menuExplicacao();
		void menuResultado();
		void printSorteio();
		bool lerArquivo(string nomeArquivo);
		bool confirmaInput(string info);
};

bool isNumber(string str);
bool verificaCPF(string cpf);
void clearTerminal();
void sortearAposta(unordered_set<int> &aposta);

#endif