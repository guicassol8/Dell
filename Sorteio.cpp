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

/*Para evitar complexidade quadratica e observacoes desnecessarias é uma boa toda vez que verificar que certo elemento ja esta nos
apostados remover ele da lista, para evitar verifica-lo denovo*/

/*Outra otimizacao poderia ser ordenar pelo tamanho do vetor presente em aposta e ele vai parar de verificar se os unicos com 1 de tamanho vencerem
So que eu nao acho q essa otimizacao seja muito necessaria

Outra otimizacao talvez inutil é de alguma maneira conseguir as apostas para verem suas semelhancas e junta-las para evitar passar mais de uma vez 
em algo igual

Tambem da para fazer um hash map onde o numero é a chave e dentro nos numeros estão a chave da aposta, assim toda vez que um numero novo aparece ele
vai acessar a posicao e dar um sinal para a aposta tirar de seu vetor o numero, assim tornando absurdamente mais rápido
*/

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

bool Sorteio::inList(int x){
	for (int i = 0; i < sorteados.size(); i++){
		if (sorteados[i] == x){
			return true;
		}
	}
	return false;
}

bool Sorteio::compararPares(const pair<Pessoa*,Aposta*>& a, const pair<Pessoa*,Aposta*>& b){
	return Pessoa::compararPonteiros(a.first, b.first);
}