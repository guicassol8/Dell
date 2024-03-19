#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "Interface.hpp"


using namespace std;

int main (){
	unordered_set<int> numeros1;
	numeros1.insert(1);
	numeros1.insert(3);
	unordered_set<int> numeros2;
	numeros2.insert(2);
	numeros2.insert(1);
	unordered_set<int> numeros3;
	numeros3.insert(4);
	numeros3.insert(5);
	// Pessoa pessoa1 = Pessoa("Joao", "123.456.789-12");
	// Pessoa pessoa2 = Pessoa("Maria", "123.456.789-10");
	// Aposta aposta1 = Aposta(1,&pessoa1,numeros1);
	// Aposta aposta2 = Aposta(2,&pessoa2, numeros2);
	// Sorteio sorteio = Sorteio(1);
	// sorteio.addAposta(aposta1);
	// sorteio.addAposta(aposta2);
	// vector<Pessoa*> vencedores;
	// if (sorteio.sortear()){
	// 	vencedores = sorteio.getGanhador();
	// }
	// if (sorteio.sortear()){
	// 	vencedores = sorteio.getGanhador();
	// }
	// cout << "Vencedores: " << endl;
	// for (auto i : vencedores){
	// 	cout << i->getDados() << endl;
	// }"
	Interface interface = Interface();
	// interface.addAposta("Maria", "123", numeros1);
	// interface.addAposta("Joao", "456", numeros3);
	// interface.addAposta("Joao", "456", numeros2);
	// interface.printSorteio();
	interface.menu();
	return 0;
}
