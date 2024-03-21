#include "Pessoa.hpp"
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <utility>

#ifndef _SORTEIO_HPP
#define _SORTEIO_HPP

class Sorteio {
	private:
		int numEdicao;
		unordered_map<int,vector<Aposta*>> apostas;
		vector<int> sorteados;
		vector<pair<Pessoa*,Aposta*>> ganhadores;
		bool fim;
	public:
		Sorteio();
		Sorteio(int numEdicao);
		void addAposta(Aposta *aposta);
		bool sortear();
		//funcao para testes
		bool sortear(int x);
		int getNumEdicao();
		vector<int> getSorteados();
		vector<pair<Pessoa*,Aposta*>> getGanhador();
		int geraRandom ();
		bool inList(int x);
		static bool compararPares(const std::pair<Pessoa*,Aposta*>& a, const std::pair<Pessoa*,Aposta*>& b);
};


#endif