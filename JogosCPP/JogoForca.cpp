#include "JogoForca.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdlib.h>
#include <time.h>

using namespace std;

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

void resetaJogo(string& palavraComMascara, int& tentativasRestante) {
	tentativasRestante = 5;
	size_t tamPalavra = palavraComMascara.size();
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

void interfaceInicial() {
	cout << "Bem vindo ao Jogo da Forca\n" << endl;
	cout << "1 - Jogar" << endl;
	cout << "2 - Sobre" << endl;
	cout << "3 - Sair." << endl;
	cout << "\nEscolha uma opção e tecle ENTER " << endl;
}

string retornaPalavraAleatoria() {
	vector<string> palavras = { "abacaxi", "manga", "morango", "limao" };
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

void verificaLetrasChutadas(string palavraSecreta, string& palavraComMascara, char letra, int& tentativasRestante) {
	bool achou = false;
	for (int i = 0; i < palavraSecreta.size(); i++) {
		if (palavraSecreta[i] == letra) {
			palavraComMascara[i] = palavraSecreta[i];
			achou = true;
		}
	}
	if (!achou)
		tentativasRestante--;
}

void interfaceLoopJogoSolo(string palavraSecreta, string& palavraComMascara, int& tentativasRestante, char& letra) {
	imprimirMascaraPalavraSecreta(palavraComMascara);
	cout << "Tentativas restantes : " << tentativasRestante << endl;
	cout << "(1) para arriscar uma palavra inteira " << endl;
	cout << "(3) para reiniciar o jogo " << endl;
	cout << "Digite uma letra : ";
	lerLetra(letra);
	if (letra == '1') {
		arriscarPalavra(palavraSecreta, palavraComMascara);
	}
	if (letra == '3') {
		resetaJogo(palavraComMascara, tentativasRestante);
	}
	verificaLetrasChutadas(palavraSecreta, palavraComMascara, letra, tentativasRestante);
	limpaTela();
}

void jogarSolo() {
	
	string palavraSecreta = retornaPalavraAleatoria();
	string palavraComMascara;
	size_t tamanhoPalavraSecreta = palavraSecreta.size();
	int maxTentativas = 5, tentativasRestante = maxTentativas;
	char letra;

	mascararPalavraSecreta(palavraComMascara, tamanhoPalavraSecreta);

	while (PossuiTentativasRestantes(tentativasRestante) && !acertouTudo(palavraComMascara)) { //Enquanto possuir tentativas e não tiver acertado tudo, continua
		cout << "--- Jogo da forca ---" << endl;
		interfaceLoopJogoSolo(palavraSecreta, palavraComMascara, tentativasRestante, letra); //Exibe interface do game, com as letras e opção de chute do jogador
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
	return true;
}

void menuInicial(){
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
			cout << "Sobre o jogo" << endl;
			break;
		case 3:
			cout << "Sair do jogo" << endl;
			break;
		default:
			cout << "Escolha uma opção válida!\n" << endl;
			break;
		}
	}
}