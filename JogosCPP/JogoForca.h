#pragma once

#include <string>

using namespace std;

void limpaTela();
bool opcaoInvalida(int opcao);
void lerNumero(int& numero);
void lerLetra(char& letra);
bool lerPalavra(string palavraSecreta);
void arriscarPalavra(string palavraSecreta, string& palavraComMascara);
void interfaceInicial();
string retornaPalavraAleatoria();
void menuInicial();
void jogarSolo();
void imprimirMascaraPalavraSecreta(string& palavra);
void mascararPalavraSecreta(string& palavra, size_t tamanhoPalavraSecreta);
bool acertouTudo(string palavraComMascara);
bool PossuiTentativasRestantes(int tentativasRestante);
void interfaceLoopJogoSolo(string palavraSecreta, string& palavraComMascara, int& tentativasRestante, char& letra);
void verificaLetrasChutadas(string palavraSecreta, string& palavraComMascara, char letra);
void resetaJogo(string& palavraComMascara, int& tentativasRestante);