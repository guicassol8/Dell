#include "Interface.hpp"

Interface::Interface(int edicao){
	this->sorteio = Sorteio(edicao);
	this->quantApostas = 0;
}

Interface::Interface(){
	this->sorteio = Sorteio();
	this->quantApostas = 0;
	this->quantRandom = 0;
}

//Deleta todos objetos pessoas por meio de um for
Interface::~Interface(){
	for (const auto& par : apostadores) {
		Pessoa* pessoa = par.second;
		delete pessoa;
	}
}

//Cria um objeto pessoa se necessario e cria um objeto Aposta
void Interface::addAposta(string nome, string cpf, unordered_set<int> aposta){
	Pessoa *pessoa;
	//Verifica se o cpf não faz parte do map, criando um novo objeto caso não
	if (apostadores.find(cpf) == apostadores.end()){
		pessoa = new Pessoa(nome, cpf);
	}
	else{
		//Se não já usa o ponteiro existente
		pessoa = apostadores[cpf];
	}
	//Cria quantApostas + 1 para garantir que o seu ID seja unico
	Aposta *aux = new Aposta(quantApostas + 1, pessoa, aposta);
	pessoa->addAposta(aux);
	this->sorteio.addAposta(aux);
	//Caso o cpf ja exista não muda nada, mas se não existia previamente vai adicionar no hashmap
	apostadores[cpf] = pessoa;
	quantApostas++;
}

/*Serve para printar todos os participantes e suas apostas*/
void Interface::printSorteio(){
	int quantApostas = 0;
	for (const auto& par : apostadores) {
		// 'par' é um par (chave, valor) no mapa, onde 'par.first' é a chave e 'par.second' é o valor
		Pessoa* pessoa = par.second;
		
		cout << pessoa->getDados() << endl;
		for (int i = 0; i < pessoa->getApostas().size(); i++) {
			cout << pessoa->getApostas()[i]->getApostaString() << endl;
		}
		cout << endl;
		quantApostas++;
	}
	cout << "Quantidade de Apostas: " << quantApostas << endl;
}


/*Funcao principal da interface, cria o menu principal com os switch cases para mudar de aba*/
void Interface::menu() {
	clearTerminal();
	//Variaveis inicializadas fora do switch pq switch eh horrivel
    int escolha = 0;
	string nome;
	string escolhaTeste = "";
	string cpf = "";
	bool run = true;
	string lixo;
	unordered_set<int> aposta;
	// Vai continuar rodando até run for falso, significando que o sorteio já acabou e não é mais necessário outras abas
    while (run) {
		cpf = "";
		aposta.clear();
		int i = 0;
		int numeroAposta = 0;
		int caminho = 0;
        switch(escolha) {
			// Case do menu, onde todas os outros cases vão visitar no final
            case 0:
                cout << RED << "MEGADELL" << endl;
                cout << "[Escolha uma opcao]" << RESET << endl;
                cout << YELLOW << "[1] - Adicionar Aposta" << endl;
                cout << "[2] - Finalizar Apostas" << endl;
                cout << "[3] - Verificar Apostas" << endl;
				cout << "[4] - Criar Apostas Teste" << endl;
				cout << "[5] - Regras" << RESET << endl;
                getline(cin,escolhaTeste);
				//Tratamento de inputs incorretos
				if (escolhaTeste.length() == 1 && isdigit(escolhaTeste[0])){
					if (confirmaInput(escolhaTeste)){
							escolha = stoi(escolhaTeste);
							clearTerminal();
							break;
					}
					else{
						clearTerminal();
						continue;
					}
				}
				else {
					escolha = -2;
				}
                break;
			//Case referente a criação de apostador
            case 1:
				clearTerminal();
				while(1){
					cout << "Digite o nome do apostador" << endl;
					cout << endl << "Para sair digite 'sair'" << endl;
            		getline(cin,nome);
					//Tratamento de input
					if (verSair(nome)){
						break;
					}
					if (nome != ""){
						if (confirmaInput(nome)){
							clearTerminal();
							break;
						}
						else{
							clearTerminal();
							continue;
						}
					}
					clearTerminal();
					cout << "Nome invalido" << endl;
				}
				if (verSair(nome)){
					clearTerminal();
					escolha = 0;
					break;
				}
				while (1){
					cout << "Digite o cpf (11 digitos apenas)" << endl;
					getline(cin,cpf);
					//Tratamento de input
					if (verificaCPF(cpf)){
						if (confirmaInput(cpf)){
							clearTerminal();
							break;
						}
						else{
							clearTerminal();
							continue;
						}
					}
					clearTerminal();
					cout << "CPF invalido" << endl;
				}
				clearTerminal();
				while (1){
					cout << "Você gostaria de digitar os numeros da aposta?" << endl;
					cout << "[1] - Sim" << endl;
					cout << "[2] - Surpresinha" << endl;
					getline(cin, lixo);
					//Tratamento de input
					if (lixo.length() == 1 && isdigit(lixo[0])){
						if ((lixo == "1" || lixo == "2")){
							if (confirmaInput(lixo)){
								clearTerminal();
								caminho = stoi(lixo);
								break;
							}
							else{
								clearTerminal();
								continue;
							}
						}
					}
					clearTerminal();
					cout << "Opcao invalida" << endl;
				}
				if (caminho == 1){
					while (i < 5) {
						lixo = "a";
						while (1){
						cout << "Digite um numero de 1 a 50 ("<< i +1 << "/5)" << endl;
							getline(cin, lixo);
							if(lixo == "");
							//Tratamento de input
							else if (isNumber(lixo) && (aposta.find(stoi(lixo)) == aposta.end())){
								break;
							}
							clearTerminal();
							cout << "Numero invalido" << endl;
						}
						numeroAposta = stoi(lixo);
						if (numeroAposta > 0 && numeroAposta < 51) {
							if (!confirmaInput(lixo)){
								clearTerminal();
								continue;
							}
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
			//Case referente à apuração de das votações e o começo do fim do menu
            case 2:
				//Chama sortear até retornar true, significando que alguém venceu, ou ate chegar no limite de 30 numeros
				for (int j = 0; j < 30; j++){
					if(sorteio.sortear()){
						break;
					}
					clearTerminal();
					cout << "Numeros Sorteados:";
					for (auto i : sorteio.getSorteados()){
						cout << GREEN << " [" << i << "]" << RESET;
					}
					cout << endl;
					//usa da biblioteca chronos e thread para segurar o codigo por 450 milisegundos
					this_thread::sleep_for(chrono::milliseconds(450));
				}
				run = false;
                break;
			//Case referente ao print de todos apostadores e suas apostas
            case 3:
				clearTerminal();
				printSorteio();
				cout << "Digite qualquer coisa para continuar" << endl;
				getline(cin, lixo);
				escolha = 0;
				clearTerminal();
                break;
			//Case para criação de casos teste
			case 4:
				clearTerminal();
				while(1){
					cout << "Digite quantos apostadores testes você deseja criar (nao digite mais de 100.000)" << endl;
					cout << endl << "Caso deseja sair, digite 'sair'" << endl;
            		getline(cin,lixo);
					//Tratamento de input para que o numero não seja gigante, tornando a aplicação lenta
					if (verSair(lixo)){
						break;
					}
					if(!isNumber(lixo) || lixo == ""){
						clearTerminal();
						cout << "Input Invalido" << endl;
						continue;	
					}
					if(stoi(lixo) > 100000){
						clearTerminal();
						cout << "Input Invalido" << endl;
						continue;
					}
					if (!confirmaInput(lixo)){
						clearTerminal();
						continue;
					}
					if(stoi(lixo) >= 20000){
						cout << "Isso pode demorar alguns segundos..." << endl;
					}
					criarCasos(stoi(lixo));
					break;
				}
				escolha = 0;
				clearTerminal();
				break;
			// Case que faz a explicação das regras do jogo
			case 5:
				menuExplicacao();
				escolha = 0;
				break;
			// Case quando o usuario digita um numero no menu mas não corresponde a nenhum dos casos, sendo invalido
            default:
				clearTerminal();
				cout << "Escolha Invalida!" << endl;
				escolha = 0;
                break;
        }
    }
	//Após ter achado seu vencedor ou não chama o menu de resultado
	menuResultado();
}

//Basicamente pega as referencias dos ganhadores e as usa para printar todos seus dados
void Interface::menuResultado(){
	clearTerminal();
	int valor;
	while(1){
		cout << "Digite qual o premio em $ deste sorteio(maximo 500.000)" << endl;
		string premio;
		getline(cin,premio);
		//Tratamento de input
		if (premio.size() < 7 && isNumber(premio) && premio.size() != 0){
			valor = stoi(premio);
			clearTerminal();
			break;
		}
		clearTerminal();
		cout << "Digite um numero válido" << endl;
	}
	vector<pair<Pessoa*,Aposta*>> ganhadores = sorteio.getGanhador();
	cout << RED << "Fim do Sorteio!" << RESET << endl << endl;
	cout << "Numeros Sorteados: ";
	for (int i = 0; i < sorteio.getSorteados().size(); i++) {
		cout << sorteio.getSorteados()[i] << " ";
	}
	cout << endl << endl;
	//Sort para caso haja mais de uma vencedora
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
		string lixo;
		cout << "Digite algo para prosseguir para a premiação" << endl;
		getline(cin,lixo);
		menuPremiacao(valor);
	}
	else{
		cout << "Nenhum ganhador!" << endl;
		cout << "O valor de "<< GREEN << valor << RESET <<"$ foi doado para os estagiarios da DELL!" << endl;
	}
}


//Mostra mensagens diferentes dependendo da quantidade de vencedores
void Interface::menuPremiacao(int valor){
	clearTerminal();
	if(sorteio.getGanhador().size() == 1){
		cout << BLUE << sorteio.getGanhador()[0].first->getNome()<< RESET << endl << "Foi o vencedor e levou uma bolada de " << GREEN << valor << RESET << "$ para casa!" << endl;
	}
	else{
		for (auto i : sorteio.getGanhador()){
			cout << BLUE << i.first->getNome() << RESET << " ";
		}
		cout << endl << "Foram os vencedores e separaram o premio, levando uma bolada de " << GREEN << valor/sorteio.getGanhador().size() << RESET << "$ para casa!" << endl;
	}

}

//Menu que explica as regras
void Interface::menuExplicacao(){
	clearTerminal();
	cout << RED << "MEGADELL" << RESET << endl;
	cout << YELLOW << "Explicacao" << endl << endl;
	cout << "A aposta consiste em 5 numeros de 1 a 50, cada numero pode aparecer apenas uma vez na aposta." << endl;
	cout << "A quantidade de dinheiro ganha é distribuida igualmente entre todos os vencedores, ela é definida antes da revelação dos resultados." << endl;
	cout << "Ao finalizar as apostas, o sistema sorteia o numeros de 1 a 50 5 vezes e verifica se algum dos apostadores ganhou, se ninguém ganhar o processo se repete até um maximo de 25 vezes." << endl;
	cout << "Você pode registrar manualmente as apostas, ou gerar casos testes." << endl;
	cout << "Após o primeiro registro de apostador, sempre que o mesmo cpf for usado a aposta irá para aquele cpf, independente do nome colocado."<< RESET << endl << endl;
	cout << "Digite qualquer coisa para continuar" << endl;
	string lixo;
	getline(cin, lixo);
	clearTerminal();
}

//Usado para tratar input, verifica se seu tamanho eh diferente de 11 e ve se todos caracteres da string são um numero, o tornando valido
bool verificaCPF(string cpf){
	if (cpf.length() != 11)
		return false;
	for (int i = 0; i < cpf.length(); i++) {
		if (!isdigit(cpf[i]))
			return false;
	}
	return true;
}

//Limpa o terminal
void clearTerminal(){
    #ifdef _WIN32 //Verifica se é windows
        system("cls");
    #else
        system("clear");
    #endif	
}

//Percorre a string verificando cada caracter para ver se algum não é digito.
bool isNumber(string str){
	for (int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

//Função basicamente copiada do sorteio
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

//Usado para impetir inputs acidentais
bool Interface::confirmaInput(string info){
	clearTerminal();
	string confirmacao;
	while(1){
		cout << "Voce deseja salvar essa informacao?" << endl;
		cout << "\"" << info << "\"" << endl;
		cout << GREEN << "[s] - Sim" << RESET << endl;
		cout << RED << "[n] - Nao" << RESET << endl;
		getline(cin,confirmacao);
		if (confirmacao == "s" || confirmacao == "S"){
			return true;
		}
		else if (confirmacao == "n" || confirmacao == "N"){
			return false;
		}
		clearTerminal();
		cout << "Opcao invalida" << endl;
	}
}

//Verifica se a pessoa deseja sair de algum menu
bool Interface::verSair(string input){
	if (input == "sair" || input == "Sair" || input == "SAIR"){
		return true;
	}
	return false;
}

//Cria casos teste, cpf e nome baseados na quantidade de casos teste, sendo sempre unicos
void Interface::criarCasos(int quantidade){
	for (int i = 0; i < quantidade; i++){
		string nome = "Nome" + to_string(this->quantRandom);
		string cpf = to_string(this->quantRandom);
		quantRandom++;
		unordered_set<int> random = randomAposta();
		addAposta(nome,cpf,random);
	}
}

//Auxilia a função criarCasos para criar um hash set aleatório
unordered_set<int> Interface::randomAposta(){
	int rand = 0;
	unordered_set<int> aux;
	for (int i = 0; i < 5; i++){
		while(1){
			// Cria um gerador de numeros pseudoaleatorios com uma semente baseada no relogio do sistema
			mt19937 rng(random_device{}());

			// Cria um distribuidor uniforme para gerar números inteiros entre 1 e 50
			uniform_int_distribution<int> dist(1, 50);

			rand = dist(rng);
			if(aux.find(rand) == aux.end()){
				aux.insert(rand);
				break;
			}
		}
	}
	return aux;
}