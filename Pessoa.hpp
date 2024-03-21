#include <vector>
#include <sstream>
#include "Aposta.hpp"

//Definicao de cores para o terminal
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

class Aposta;

#ifndef _PESSOA_HPP
#define _PESSOA_HPP

using namespace std;

class Pessoa{
	private:
		string nome;
		string cpf;
		vector <Aposta*> apostas;
	public:
		Pessoa(string nome, string cpf);
		~Pessoa();
		string getNome();
		string getCpf();
		void setNome(string nome);
		void setCpf(string cpf);
		void addAposta(Aposta* aposta);
		vector <Aposta*> getApostas();
		string getDados();
		string getApostasString();
		bool operator>(const Pessoa& p) const;
		bool operator<(const Pessoa& p) const;
		static bool compararPonteiros(const Pessoa* p1, const Pessoa* p2);
};

#endif