#include <iostream>
#include <unordered_set>

using namespace std;

class Pessoa;

#ifndef _APOSTA_HPP
#define _APOSTA_HPP
#include "Pessoa.hpp"

class Aposta {
	private:
		int codigoAposta;
		Pessoa *pessoa;
		unordered_set<int> aposta;
		vector<int> apostaVector;
	public:
		Aposta(int codigo,Pessoa *pessoa, unordered_set<int> &aposta);
		~Aposta();
		int getCodigoAposta();
		vector<int> getApostaVector();
		Pessoa* getPessoa();
		unordered_set<int> getAposta();
		string getApostaString();
		void setCodigoAposta(int codigo);
		bool deletNum(int numero);
		void setAposta(unordered_set<int> aposta);
		void imprimeDados();
		void imprimeAposta();
};

#endif
