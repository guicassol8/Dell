#include "Interface.hpp"

Interface::Interface(int edicao){
	this->sorteio = Sorteio(edicao);
	this->quantApostas = 0;
}

Interface::Interface(){
	this->sorteio = Sorteio();
	this->quantApostas = 0;
}

Interface::~Interface(){
	for (const auto& par : apostadores) {
		Pessoa* pessoa = par.second;
		delete pessoa;
	}
}

void Interface::addAposta(string nome, string cpf, unordered_set<int> aposta){
	Pessoa *pessoa;
	if (apostadores.find(cpf) == apostadores.end()){
		pessoa = new Pessoa(nome, cpf);
	}
	else{
		pessoa = apostadores[cpf];
	}
	Aposta *aux = new Aposta(quantApostas + 1, pessoa, aposta);
	pessoa->addAposta(aux);
	this->sorteio.addAposta(aux);
	apostadores[cpf] = pessoa;
	quantApostas++;
}

void Interface::printSorteio(){
	for (const auto& par : apostadores) {
		// 'par' é um par (chave, valor) no mapa, onde 'par.first' é a chave e 'par.second' é o valor
		Pessoa* pessoa = par.second;
		
		cout << pessoa->getDados() << endl;
		for (int i = 0; i < pessoa->getApostas().size(); i++) {
			cout << pessoa->getApostas()[i]->getApostaString() << endl;
		}
		cout << endl;
	}
}

void Interface::menu() {
    int escolha = 0;
	string nome;
	string escolhaTeste = "";
	string cpf = "";
	bool run = true;
	string lixo;
	unordered_set<int> aposta;
    while (run) {
		cpf = "";
		aposta.clear();
		int i = 0;
		int numeroAposta = 0;
		int caminho = 0;
        switch(escolha) {
            case 0:
                cout << RED << "MEGADELL" << endl;
                cout << "[Escolha uma opcao]" << RESET << endl;
                cout << YELLOW << "[1] - Adicionar Aposta" << endl;
                cout << "[2] - Finalizar Apostas" << endl;
                cout << "[3] - Verificar Apostas" << endl;
				cout << "[4] - Ler Arquivo" << endl;
				cout << "[5] - Regras" << RESET << endl;
                getline(cin,escolhaTeste);
				if (escolhaTeste.length() == 1 && isdigit(escolhaTeste[0])){
					escolha = stoi(escolhaTeste);
				}
				else {
					escolha = -2;
				}
                break;
            case 1:
				clearTerminal();
                cout << "Digite o nome do apostador" << endl;
				while(1){
            		getline(cin,nome);
					if (nome != ""){
						break;
					}
					cout << "Nome invalido" << endl;
				}
				while (1){
					cout << "Digite o cpf (apenas numeros)" << endl;
					getline(cin,cpf);
					if (verificaCPF(cpf)){
						break;
					}
					cout << "CPF invalido" << endl;
				}
				clearTerminal();
				while (1){
					cout << "Você gostaria de digitar os numeros da aposta?" << endl;
					cout << "[1] - Sim" << endl;
					cout << "[2] - Nao" << endl;
					getline(cin, lixo);
					// if (lixo == "");
					if (lixo.length() == 1 && isdigit(lixo[0])){
						if ((lixo[0] == 1 || lixo[0] == 2)){
							caminho = stoi(lixo);
							break;
						}
					}
					clearTerminal();
					cout << "Opcao invalida" << endl;
				}
				if (caminho == 1){
					while (i < 5) {
						lixo = "a";
						cout << "Digite um numero de 1 a 50 " << endl;
						while (1){
							getline(cin, lixo);
							if(lixo == "");
							else if (isNumber(lixo) && (aposta.find(stoi(lixo)) == aposta.end())){
								break;
							}
							cout << "Numero invalido" << endl;
						}
						numeroAposta = stoi(lixo);
						if (numeroAposta > 0 && numeroAposta < 51) {
							aposta.insert(numeroAposta);
							i++;
							clearTerminal();
						}
						else{
							clearTerminal();
							cout << "Numero invalido" << endl;
						}
					}
				}
				else{
					sortearAposta(aposta);
				}
				// Evitar numero excecivo de caracteres
				nome = nome.substr(0,75);
				addAposta(nome, cpf, aposta);
				escolha = 0;
				clearTerminal();
                break;
            case 2:
				for (int j = 0; j < 30; j++){
					if(sorteio.sortear()){
						break;
					}
				}
				run = false;
                break;
            case 3:
				clearTerminal();
				printSorteio();
				cout << "Digite qualquer coisa para continuar" << endl;
				getline(cin, lixo);
				escolha = 0;
				clearTerminal();
                break;
			case 4:
				clearTerminal();
				cout << "Digite o nome do arquivo" << endl;
				while(1){
					getline(cin, lixo);
					if(lerArquivo(lixo)){
						break;
					}
					cout << "Arquivo invalido" << endl;
				}
				escolha = 0;
				clearTerminal();
				break;
			case 5:
				menuExplicacao();
				escolha = 0;
				break;
            default:
				clearTerminal();
				cout << "Escolha Invalida!" << endl;
				escolha = 0;
                break;
        }
    }
	menuResultado();
}

void Interface::menuResultado(){
	clearTerminal();
	vector<pair<Pessoa*,Aposta*>> ganhadores = sorteio.getGanhador();
	cout << "Fim do Sorteio!" << endl;
	cout << "Numeros Sorteados: ";
	for (int i = 0; i < sorteio.getSorteados().size(); i++) {
		cout << sorteio.getSorteados()[i] << " ";
	}
	cout << endl;
	sort(ganhadores.begin(), ganhadores.end(), Sorteio::compararPares);
	if (ganhadores.size() > 0) {
		cout << "Ganhadores:" << endl;
		for (int i = 0; i < ganhadores.size(); i++) {
			cout << ganhadores[i].first->getDados() << endl;
			cout << "Aposta: ";
			for (auto i : ganhadores[i].second->getApostaVector()) {
				cout << i << " ";
			}
			cout << "Codigo Aposta: " << ganhadores[i].second->getCodigoAposta() << endl;
			cout << endl;
		}
	}
	else{
		cout << "Nenhum ganhador!" << endl;
	}
}

bool Interface::lerArquivo(string nomeArquivo){
	ifstream arquivo(nomeArquivo);
	string nome;
	string cpf;
	string aposta;
	if (!arquivo.is_open()){
		return false;	
	}
	while (!arquivo.eof()){
		unordered_set<int> apostaSet;
		getline(arquivo,nome);
		getline(arquivo, cpf);
		for (int i = 0; i < 5; i++) {
			getline(arquivo, aposta);
			apostaSet.insert(stoi(aposta));
		}
		addAposta(nome, cpf, apostaSet);
	}
	arquivo.close();
	return true;
}

void Interface::menuExplicacao(){
	clearTerminal();
	cout << "MEGADELL" << endl;
	cout << "Explicacao" << endl;
	cout << "A aposta consiste em 5 numeros de 1 a 50, cada numero pode aparecer apenas uma vez na aposta." << endl;
	cout << "Ao finalizar as apostas, o sistema sorteia os numeros de 1 a 50 e verifica se algum dos apostadores ganhou." << endl;
	cout << "Existem duas maneiras de registrar apostadores:" << endl;
	cout << endl << "Input - O input foi feito para o usuario, adicionar pelo proprio terminal impede com que dados incorretos sejam armazenados";
	cout << endl << "Arquivo - O arquivo foi feito para o administrador do sorteio, no caso do arquivo ele aceita informacoes incorretas";
	cout << ", por isso é importante que ele esteja formatado da seguinte maneira:" << endl;
	cout << "Nome" << endl;
	cout << "CPF (apenas numeros de 11 digitos)" << endl;
	cout << "Aposta 1" << endl;
	cout << "Aposta 2" << endl;
	cout << "Aposta 3" << endl;
	cout << "Aposta 4" << endl;
	cout << "Aposta 5" << endl;
	cout << endl << "Qualquer informação incorreta escrita no arquivo pode causar podera causar comportamentos inesperados"  << endl;
	cout << "Digite qualquer coisa para continuar" << endl;
	string lixo;
	getline(cin, lixo);
	clearTerminal();
}


bool verificaCPF(string cpf){
	if (cpf.length() != 11)
		return false;
	for (int i = 0; i < cpf.length(); i++) {
		if (!isdigit(cpf[i]))
			return false;
	}
	return true;
}


void clearTerminal(){
    #ifdef _WIN32 //Verifica se é windows
        system("cls");
    #else
        system("clear");
    #endif	
}

bool isNumber(string str){
	for (int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

void sortearAposta(unordered_set<int> &aposta){
	int rand = 0;
	for (int i = 0; i < 5; i++){
		while(1){
			// Cria um gerador de numeros pseudoaleatorios com uma semente baseada no relogio do sistema
			mt19937 rng(random_device{}());

			// Cria um distribuidor uniforme para gerar números inteiros entre 1 e 50
			uniform_int_distribution<int> dist(1, 50);

			rand = dist(rng);
			if (aposta.find(rand) == aposta.end()){
				aposta.insert(rand);
				break;
			}
		}
	}
}