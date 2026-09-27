#include "JogoForca.h"

#include <iostream>
#include <stdlib.h>

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

void interfaceInicial() {
	cout << "Bem vindo ao Jogo da Forca\n" << endl;
	cout << "1 - Jogar" << endl;
	cout << "2 - Sobre" << endl;
	cout << "3 - Sair." << endl;
	cout << "\nEscolha uma opção e tecle ENTER " << endl;
}

void menuInicial(){
	int opcao = 0;

	while (opcaoInvalida(opcao)) {
		interfaceInicial();
		lerNumero(opcao); //Lê número enviado pelo úsuario e trata os erros caso sejam enviados caracteres

		limpaTela();
		switch (opcao) {
		case 1:
			cout << "Inicia o jogo" << endl;
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