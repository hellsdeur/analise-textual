#ifndef BUSCADOR_H
#define BUSCADOR_H

#include "../analise-textual/catalogo.hpp"
#include "../compressao/compactador.hpp"
#include "../compressao/huffman.hpp"
#include <fstream>

#define MAXCHAR         256
#define NUMMAXERROS     10

class Buscador {
private:
	Compactador compactador;
	Catalogo catalogo;

	void shift_and_exato(std::string, std::string);
	void BMH(std::string, std::string);
	std::string concatenar_textos();

public:
	Buscador(Catalogo, Compactador);
	std::string textos_concatenados;

	void buscar_nao_comprimido(std::string);
	void buscar_comprimido(std::string);
};

inline Buscador::Buscador(Catalogo catalogo, Compactador compactador) {
	this->compactador = compactador;
	this->catalogo = catalogo;
	this->textos_concatenados = concatenar_textos();

	std::cout << textos_concatenados.size();
}

inline std::string Buscador::concatenar_textos() {
	std::ifstream arquivo;
	std::string geral;

	for (int i = 0; i < this->catalogo.tamanho(); i++) {
		std::string s;

		arquivo.open(this->catalogo.get_caminho(i));

		while (std::getline(arquivo, s)) {
			geral += s;
		}

		arquivo.close();
	}

	return geral;
}

inline void Buscador::buscar_nao_comprimido(std::string chave) {
	BMH(this->textos_concatenados, chave);
}

inline void Buscador::buscar_comprimido(std::string chave) {
	std::string binario_chave;

	for (int i = 0; i < chave.size(); i++) {
		binario_chave += this->compactador.huffman.codigos[chave[i]];
	}

	BMH(this->compactador.binario, binario_chave);
}

void Buscador::BMH(std::string T, std::string P) {
	long n = T.size();
	long m = P.size();

	long i, j, k, d[MAXCHAR + 1];
	for (j = 0; j <= MAXCHAR; j++) d[j] = m;
	for (j = 1; j < m; j++) d[P[j-1]] = m - j;
	i = m;
	while (i <= n) {
		k = i;
		j = m;
		while (T[k-1] == P[j-1] && j > 0) { k--; j--; }
			if (j == 0) 
				printf("Casamento na posicao: %3ld\n", k + 1);
			i += d[T[i-1]];
    }
}

#endif