#include "BatalhaNaval.h"
#include "main.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

namespace BatalhaNaval {
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
		cout << "Bem vindo ao Batalha Naval\n" << endl;
		cout << "1 - Jogar" << endl;
		cout << "2 - Sobre" << endl;
		cout << "3 - Voltar." << endl;
		cout << "\nEscolha uma opção e tecle ENTER " << endl;
	}

	void menuInicialBatalhaNaval() {
		int opcao = 0;

		while (opcaoInvalida(opcao)) { //Enquanto opção for invalida, continua lendo valores do úsuario
			interfaceInicial();
			lerNumero(opcao); //Lê número enviado pelo úsuario e trata os erros caso sejam enviados caracteres

			limpaTela();
			switch (opcao) {
			case 1:
				cout << "Inicia o jogo" << endl;
				//jogar();
				break;
			case 2:
				cout << "-------- Sobre o jogo --------" << endl;
				cout << "Batalha Naval desenvolvido por" << endl;
				cout << "------- Herbert Santos -------" << endl;
				cout << "--------- 1 - Voltar ---------" << endl;
				cout << "---------- 2 - Sair ----------" << endl;
				cin >> opcao;
				if (opcao == 1) {
					limpaTela();
					menuInicialBatalhaNaval();
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