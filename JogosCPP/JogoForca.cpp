#include "JogoForca.h"
#include "main.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>

using namespace std;

namespace JogoForca {
	void limpaTela() {
		system("CLS");
	}

	bool opcaoInvalida(int opcao) {
		if (opcao < 1 || opcao > 3)
			return true;
		return false;
	}

	void lerNumero(int& numero) {
		while (!(cin >> numero)) {
			cout << "Erro! Você digitou uma letra. Por favor, insira apenas números: ";

			cin.clear(); // Remove o estado de erro do cin
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta o texto incorreto do buffer
		}
	}

	bool lerPalavra(string palavraSecreta) {
		string palavra;
		cout << "Digite a palavra : (letras minusculas) ";
		cin >> palavra;
		if (palavra == palavraSecreta)
			return true;
		else {
			cout << "Você errou o seu chute " << endl;
			return false;
		}
		
	}

	void arriscarPalavra(string palavraSecreta, string& palavraComMascara) {
		limpaTela();
		if (lerPalavra(palavraSecreta))
			palavraComMascara = palavraSecreta;
	}

	void resetaJogo(string& palavraComMascara, int& tentativasRestante, string& letrasArriscadas) {
		tentativasRestante = 5;
		size_t tamPalavra = palavraComMascara.size();
		letrasArriscadas = "";
		palavraComMascara = "";
		mascararPalavraSecreta(palavraComMascara, tamPalavra);
	}

	void lerLetra(char& letra) {
		while ((cin >> letra)) {
			if (isalpha(static_cast<unsigned char>(letra))) {
				letra = tolower(letra);
				return;
			}
			else {
				if (letra == '1') {
					cout << "Digite a palavra : " << endl;
					return;
				}
				if (letra == '3')
					return;
				cout << "Apenas letras são validas! " << endl;
				cout << "Digite uma letra : ";
			}
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta o texto incorreto do buffer
		}
	}

	void adicionarPalavra() {
		ofstream arquivo("palavras.txt", ios::app);
		string palavra;
		cin >> palavra;

		if (arquivo.is_open()) {
			arquivo << palavra << "\n";
			arquivo.close();
			cout << "Palavra adicionada com sucesso! " << endl;
		}
	}

	vector<string> recuperandoPalavras() {
		ifstream arquivo("palavras.txt");

		if (!arquivo.is_open()) {
			cout << "Erro ao abrir o arquivo." << endl;
			exit(1);
		}

		vector<string> palavras;
		string linha;
		while (getline(arquivo, linha)) {
			palavras.push_back(linha);
		}

		arquivo.close();

		return palavras;
	}

	void interfaceInicial() {
		cout << "Bem vindo ao Jogo da Forca\n" << endl;
		cout << "1 - Jogar" << endl;
		cout << "2 - Sobre" << endl;
		cout << "3 - Voltar." << endl;
		cout << "\nEscolha uma opção e tecle ENTER " << endl;
	}

	string retornaPalavraAleatoria() {
		vector<string> palavras = recuperandoPalavras();
		size_t qntdPalavra = palavras.size();

		srand((unsigned)time(NULL));
		int random = (rand() % qntdPalavra);

		string palavraEscolhida = palavras[random];

		return palavraEscolhida;
	}

	bool PossuiTentativasRestantes(int tentativasRestante) {
		if (tentativasRestante > 0)
			return true;
		else {
			cout << "Acabaram as tentativas restantes, você perdeu! " << endl;
			return false;
		}
	}

	void verificaLetrasChutadas(string palavraSecreta, string& palavraComMascara, char letra, int& tentativasRestante, string& letrasArriscadas) {
		bool achou = false;
		bool letraJaChutada = false;
		for (int i = 0; i < palavraSecreta.size(); i++) {
			if (palavraSecreta[i] == letra) {
				palavraComMascara[i] = palavraSecreta[i];
				achou = true;
			}
		}
		if (!achou){  //Se a letra não está na palavra secreta
			for (int i = 0; i < letrasArriscadas.size(); i++) {
				if (letra == letrasArriscadas[i]) //Verifica se ela já não foi chutada antes
					letraJaChutada = true;
			}
			if (!letraJaChutada) { //Se caso não foi, adiciona em letras arriscadas e diminui as tentativas restantes
				letrasArriscadas += letra;
				letrasArriscadas += ' ';
				tentativasRestante--;
			}
		}
	}

	void interfaceLoopJogoSolo(string palavraSecreta, string& palavraComMascara, int& tentativasRestante, char& letra, string& letrasArriscadas) {
		imprimirMascaraPalavraSecreta(palavraComMascara);
		cout << "Tentativas restantes : " << tentativasRestante << endl;
		cout << "Letras arriscadas : " << letrasArriscadas << endl;
		cout << "(1) para arriscar uma palavra inteira " << endl;
		cout << "(3) para reiniciar o jogo " << endl;
		cout << "Digite uma letra : ";
		lerLetra(letra);
		if (letra == '1') {
			arriscarPalavra(palavraSecreta, palavraComMascara);
		}
		if (letra == '3') {
			resetaJogo(palavraComMascara, tentativasRestante, letrasArriscadas);
			letra = 0;
			tentativasRestante++;
		}
		verificaLetrasChutadas(palavraSecreta, palavraComMascara, letra, tentativasRestante, letrasArriscadas);
		limpaTela();
	}

	void jogarSolo() {
	
		string palavraSecreta = retornaPalavraAleatoria();
		string palavraComMascara, letrasArriscadas = "";
		size_t tamanhoPalavraSecreta = palavraSecreta.size();
		int maxTentativas = 5, tentativasRestante = maxTentativas;
		char letra;

		mascararPalavraSecreta(palavraComMascara, tamanhoPalavraSecreta);

		while (PossuiTentativasRestantes(tentativasRestante) && !acertouTudo(palavraComMascara)) { //Enquanto possuir tentativas e não tiver acertado tudo, continua
			cout << "--- Jogo da forca ---" << endl;
			interfaceLoopJogoSolo(palavraSecreta, palavraComMascara, tentativasRestante, letra, letrasArriscadas); //Exibe interface do game, com as letras e opção de chute do jogador
		}
		cout << "A palavra secreta era : " << palavraSecreta << endl;
		cout << "Final do jogo!" << endl;
	}

	void imprimirMascaraPalavraSecreta(string& palavra) {
		for (int i = 0; i < palavra.size(); i++) {
			cout << palavra[i] << " ";
		}
		cout << endl;
	}

	void mascararPalavraSecreta(string& palavra, size_t tamanhoPalavraSecreta) {
		for (int i = 0; i < tamanhoPalavraSecreta; i++) {
			palavra += "_";
		}
	}

	bool acertouTudo(string palavraComMascara) {
		for (int i = 0; i < palavraComMascara.size(); i++) {
			if (palavraComMascara[i] == '_') {
				return false;
			}
		}
		cout << "Parabens você acertou!" << endl;
		cout << "Você deseja adicionar uma nova fruta?" << endl;
		cout << "(1) para adicionar" << endl;
		char opcao = 0;
		cin >> opcao;
		if (opcao == '1') {
			adicionarPalavra();
		}
		return true;
	}

	void menuInicialJogoForca(){
		int opcao = 0;

		while (opcaoInvalida(opcao)) { //Enquanto opção for invalida, continua lendo valores do úsuario
			interfaceInicial();
			lerNumero(opcao); //Lê número enviado pelo úsuario e trata os erros caso sejam enviados caracteres

			limpaTela();
			switch (opcao) {
			case 1:
				cout << "Inicia o jogo" << endl;
				jogarSolo();
				break;
			case 2:
				cout << "-------- Sobre o jogo --------" << endl;
				cout << "Jogo da forca desenvolvido por" << endl;
				cout << "------- Herbert Santos -------" << endl;
				cout << "--------- 1 - Voltar ---------" << endl;
				cout << "---------- 2 - Sair ----------" << endl;
				cin >> opcao;
				if (opcao == 1) {
					limpaTela();
					menuInicialJogoForca();
				}
				limpaTela();
				break;
			case 3:
				menuInicial();
				break;
			default:
				cout << "Escolha uma opção válida!\n" << endl;
				break;
			}
		}
	}
}