#include "Pessoa.hpp"
#include "Aposta.hpp"

Pessoa::Pessoa(string nome, string cpf){
	this->nome = nome;
	this->cpf = cpf;
	quantDinheiro = 0;
}

Pessoa::~Pessoa(){
	int tamanho = apostas.size();
	for (int i = 0; i < tamanho; i++){
		delete apostas[i];
	}
	#ifdef DEBUG
		cout << "Pessoa destruida" << endl;
	#endif
}

string Pessoa::getNome(){
	return nome;
}

string Pessoa::getCpf(){
	return cpf;
}

int Pessoa::getQuantDinheiro(){
	return quantDinheiro;
}

void Pessoa::setNome(string nome){
	this->nome = nome;
}

void Pessoa::setCpf(string cpf){
	this->cpf = cpf;
}

void Pessoa::setQuantDinheiro(int quantDinheiro){
	this->quantDinheiro = quantDinheiro;
}

void Pessoa::addAposta(Aposta *aposta){
	apostas.push_back(aposta);
}

vector<Aposta*> Pessoa::getApostas(){
	return apostas;
}

string Pessoa::getDados(){
	stringstream ss;
	ss << nome << " " << cpf << " " << quantDinheiro;
	return ss.str();
}

string Pessoa::getApostasString(){
	stringstream ss;
	for(int i = 0; i < apostas.size(); i++){
		ss << apostas[i]->getApostaString() << endl;
	}
	return ss.str();
}

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
