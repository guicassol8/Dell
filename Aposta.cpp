#include "Aposta.hpp"

Aposta::Aposta(int codigo, Pessoa *pessoa, unordered_set<int> &aposta){
	this->codigoAposta = 1000 + codigo;
	this->aposta = aposta;
	this->pessoa = pessoa;
	for (auto apostas : aposta){
		apostaVector.push_back(apostas);
	}
}

Aposta::~Aposta(){
	#ifdef DEBUG
		cout << "Aposta destruida" << endl;
	#endif
}

int Aposta::getCodigoAposta(){
	return codigoAposta;
}

unordered_set<int> Aposta::getAposta(){
	return aposta;
}

void::Aposta::setCodigoAposta(int codigo){
	this->codigoAposta = codigo;
}

void::Aposta::setAposta(unordered_set<int> aposta){
	this->aposta = aposta;
}

//Funcao que remove numero do hashset de numeros apostados e retorna true se o size do hashset for 0, significando que todos numeros foram "riscados"
bool Aposta::deletNum(int numero){
	auto it = aposta.find(numero);
	//
	if(it != aposta.end()){
		aposta.erase(it);
	}
	//
	if(aposta.size() == 0){
		return true;
	}
	return false;
}

Pessoa *Aposta::getPessoa(){
	return pessoa;
}

void Aposta::imprimeAposta(){
	cout << "Aposta " << codigoAposta << ": ";
	for(auto it = aposta.begin(); it != aposta.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
}

string Aposta::getApostaString(){
	stringstream ss;
	for(auto it = aposta.begin(); it != aposta.end(); it++){
		ss << *it << " ";
	}
	ss << "Codigo: " << codigoAposta;
	return ss.str();
}

vector<int> Aposta::getApostaVector(){
	return apostaVector;
}