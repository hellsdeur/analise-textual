#include "../analise-textual/catalogo.hpp"
#include "huffman.hpp"
#include <vector>

class Compactador {
private:
	Catalogo catalogo;
	std::vector<unsigned char> chars;
	std::unordered_map<unsigned char, unsigned int> mapa_freq;
	Huffman huffman;

	void preprocessar();
	void compactar();

public:
	Compactador(Catalogo);
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
			std::unordered_map<unsigned char, unsigned int>::const_iterator it_umap;

			for (int i = 0; i < s.size(); i++){
				this->chars.push_back(s[i]);

				it_umap = this->mapa_freq.find(s[i]);
				if (it_umap == this->mapa_freq.end())
					this->mapa_freq.insert(std::make_pair(s[i], 1));
				else
					this->mapa_freq[s[i]]++;
			}
		}
	}
}
