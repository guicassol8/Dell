#include "Sorteio.hpp"

Sorteio::Sorteio(int numEdicao){
    this->numEdicao = numEdicao;
	this->fim = false;
}

Sorteio::Sorteio(){
	this->fim = false;
	this->numEdicao = 0;
}

int Sorteio::getNumEdicao(){
    return this->numEdicao;
}

void Sorteio::addAposta(Aposta *aposta){
	for (auto i : aposta->getAposta()){
		apostas[i].push_back(aposta);
	}
}

//Funcao que sorteia apenas um numero, remove esse numero do hashet das apostas e retornar verdadeiro se algum ganhador for encontrado
bool Sorteio::sortear(){
	int rand = geraRandom();
	//Variavel que se mantem false se nenhum vencedor for encontrado
	bool validar = false;
	//Pega o numero sorteado e adiciona na lista de sorteados
	sorteados.push_back(rand);
	//For que pega do hashmap com a chave inteira rand um vector de ponteiros para as apostas
	vector<Aposta*> aux = apostas[rand];
	for(int i = 0; i < aux.size(); i++){
		//Se for verdadeiro significa que o hashset tem size 0, deletNum remove o numero sorteado do hashset da aposta
		if (aux[i]->deletNum(rand)){
			//Push back no ganhador pois o tamanho do hashset chegou a 0, oque significa que todos numeros da cartela de aposta ja foram "riscados"
			ganhadores.push_back(make_pair(aux[i]->getPessoa(),aux[i]));
			validar = true;
		}
	}
	return validar;
}

//Funcao que sorteia apenas um numero, remove esse numero do hashet das apostas e retornar verdadeiro se algum ganhador for encontrado
bool Sorteio::sortear(int x){
	//Variavel que se mantem false se nenhum vencedor for encontrado
	bool validar = false;
	int rand = x;
	//Pega o numero sorteado e adiciona na lista de sorteados
	sorteados.push_back(rand);
	//For que pega do hashmap com a chave inteira rand um vector de ponteiros para as apostas
	vector<Aposta*> aux = apostas[rand];
	for(int i = 0; i < aux.size(); i++){
		//Se for verdadeiro significa que o hashset tem size 0, deletNum remove o numero sorteado do hashset da aposta
		if (aux[i]->deletNum(rand)){
			//Push back no ganhador pois o tamanho do hashset chegou a 0, oque significa que todos numeros da cartela de aposta ja foram "riscados"
			ganhadores.push_back(make_pair(aux[i]->getPessoa(),aux[i]));
			validar = true;
		}
	}
	return validar;
}

vector<int> Sorteio::getSorteados(){
	return this->sorteados;
}

vector<pair<Pessoa*,Aposta*>> Sorteio:: getGanhador(){
	return ganhadores;
}

/*Importante ressaltar que essa função não cria numeros realmente aleatorios, visto que eles estão sendo
baseados no relogio do sistema, mas funciona para essa aplicação*/

int Sorteio::geraRandom(){
	int rand = 0;
	while(1){
		// Cria um gerador de numeros pseudoaleatorios com uma semente baseada no relogio do sistema
		mt19937 rng(random_device{}());

		// Cria um distribuidor uniforme para gerar números inteiros entre 1 e 50
    	uniform_int_distribution<int> dist(1, 50);

		rand = dist(rng);
		if (!inList(rand)){
			break;
		}
	}
	return rand;
}

/*Verifica em O(n) se o numero sorteado já foi sorteado*/
bool Sorteio::inList(int x){
	for (int i = 0; i < sorteados.size(); i++){
		if (sorteados[i] == x){
			return true;
		}
	}
	return false;
}

//Funcao estática usada para conseguir comparar um vector pair e ordenar os vencedores usando o sort()
bool Sorteio::compararPares(const pair<Pessoa*,Aposta*>& a, const pair<Pessoa*,Aposta*>& b){
	return Pessoa::compararPonteiros(a.first, b.first);
}