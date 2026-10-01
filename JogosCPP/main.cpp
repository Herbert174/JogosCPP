#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>

#include "main.h"
#include "JogoForca.h"
#include "BatalhaNaval.h"

using namespace std;
using namespace JogoForca;
//using namespace BatalhaNaval;

void interfaceInicio() {
	cout << "Bem vindo a coletanea de jogos C++\n" << endl;
	cout << "1 - Jogo da forca" << endl;
	cout << "2 - Batalha naval" << endl;
	cout << "3 - Jogo da velha" << endl;
	cout << "4 - Sair." << endl;
	cout << "\nEscolha uma opção e tecle ENTER " << endl;
}

void menuInicial() {
	int opcao = 0;
	while (opcaoInvalida(opcao)) {
		interfaceInicio();
		lerNumero(opcao);
		limpaTela();

		switch (opcao) {
		case 1:
			menuInicialJogoForca();
			break;

		case 2:
			BatalhaNaval::menuInicialBatalhaNaval();
			break;
		case 3:
			break;

		case 4:
			exit(1);
			break;

		default:
			cout << "Escolha uma opção válida!\n" << endl;
			break;
		}
	}
}

int main() {
	setlocale(LC_ALL, "en_US.UTF-8");

	menuInicial();

	return 0;
}