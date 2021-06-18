#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "../analise-textual/catalogo.hpp"
#include "huffman.hpp"
#include <vector>
#include <sstream>
#include <bitset>

class Compactador {
private:
	Catalogo catalogo;
	std::vector<unsigned char> chars;
	std::unordered_map<unsigned char, unsigned int> mapa_freq;

	void preprocessar();
	void compactar();

public:
	Huffman huffman;
	std::string binario;
	Compactador() {}
	Compactador(Catalogo);
	void print();
};

inline Compactador::Compactador(Catalogo catalogo) {
	this->catalogo = catalogo;
	preprocessar();

	this->huffman = Huffman(this->mapa_freq);
	compactar();
}

inline void Compactador::preprocessar() {

	for (int i = 0; i < this->catalogo.tamanho(); i++) {
		std::ifstream arquivo;
		std::string s;

		arquivo.open(this->catalogo.get_caminho(i));

		while (std::getline(arquivo, s)) {
			std::unordered_map<unsigned char, unsigned int>::const_iterator it;

			for (int i = 0; i < s.size(); i++){
				this->chars.push_back(s[i]);

				it = this->mapa_freq.find(s[i]);
				if (it == this->mapa_freq.end())
					this->mapa_freq.insert(std::make_pair(s[i], 1));
				else
					this->mapa_freq[s[i]]++;
			}
		}
	}
}


inline void Compactador::compactar() {
	std::fstream arquivo;
	
	std::stringstream sstream;

	for (int i = 0; i < this->chars.size(); i++) {
		this->binario += this->huffman.codigos[chars[i]];
	}

	sstream = std::stringstream(this->binario);

	std::remove("../resultados/base_textos.cpt");

	arquivo.open("../resultados/base_textos.cpt", std::ios::out | std::ios::app);

	while(sstream.good()) {
		std::bitset<8> bits;
		unsigned char c;

		sstream >> bits;
		c = char(bits.to_ulong());

		arquivo << c;
	}

	arquivo.close();
}

inline void Compactador::print() {
	for (auto i : this->huffman.codigos) {
		std::cout << i.first << " : " << i.second << '\n';
	}
}

#endif