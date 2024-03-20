#include <vector>
#include <sstream>
#include "Aposta.hpp"

class Aposta;

#ifndef _PESSOA_HPP
#define _PESSOA_HPP

using namespace std;

class Pessoa{
	private:
		string nome;
		string cpf;
		int quantDinheiro;
		vector <Aposta*> apostas;
	public:
		Pessoa(string nome, string cpf);
		~Pessoa();
		string getNome();
		string getCpf();
		int getQuantDinheiro();
		void setNome(string nome);
		void setCpf(string cpf);
		void setQuantDinheiro(int quantDinheiro);
		void addAposta(Aposta* aposta);
		vector <Aposta*> getApostas();
		string getDados();
		string getApostasString();
		bool operator>(const Pessoa& p) const;
		bool operator<(const Pessoa& p) const;
		static bool compararPonteiros(const Pessoa* p1, const Pessoa* p2);
};

#endif