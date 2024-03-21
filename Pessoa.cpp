#include "Pessoa.hpp"
#include "Aposta.hpp"

/*Construtor e Destrutor*/
Pessoa::Pessoa(string nome, string cpf){
	this->nome = nome;
	this->cpf = cpf;
}

/*Delete todas apostas feitas*/
Pessoa::~Pessoa(){
	int tamanho = apostas.size();
	for (int i = 0; i < tamanho; i++){
		delete apostas[i];
	}
	#ifdef DEBUG
		cout << "Pessoa destruida" << endl;
	#endif
}

/*Geters e Seters*/
string Pessoa::getNome(){
	return nome;
}

string Pessoa::getCpf(){
	return cpf;
}

void Pessoa::setNome(string nome){
	this->nome = nome;
}

void Pessoa::setCpf(string cpf){
	this->cpf = cpf;
}

vector<Aposta*> Pessoa::getApostas(){
	return apostas;
}

void Pessoa::addAposta(Aposta *aposta){
	apostas.push_back(aposta);
}

//Retorna dados da pessoa em forma de string (sem endl)
string Pessoa::getDados(){
	stringstream ss;
	ss << RED << nome << RESET << YELLOW << " CPF: " << cpf << RESET;
	return ss.str();
}

//Retorna as apostas feitas em formato de string
string Pessoa::getApostasString(){
	stringstream ss;
	for(int i = 0; i < apostas.size(); i++){
		ss << apostas[i]->getApostaString() << endl;
	}
	return ss.str();
}

/*Operators usados pra fazer o sort no momento do vencedor*/
bool Pessoa::operator>(const Pessoa &p) const{
	return this->nome > p.nome;
}

bool Pessoa::operator<(const Pessoa &p) const{
	return this->nome < p.nome;
}

// Função de comparação personalizada para ordenar ponteiros para objetos Pessoa
bool Pessoa::compararPonteiros(const Pessoa* p1, const Pessoa* p2) {
    return p1->nome < p2->nome;
}
