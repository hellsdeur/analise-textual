#include <iostream>
#include "analise-textual/analisador.hpp"
#include <unordered_map>
#include "compressao/huffman2.hpp"

int main() {

	Catalogo catalogo("../recursos/base_textos/");

	Analisador analisador(catalogo, 100);

	//analisador.exportar_dados();

	std::unordered_map<unsigned char, unsigned int> f =  analisador.get_frequencias();
	Huffman huffman(f);
	huffman.print();

	//  for (auto i : f) std::cout << i.first << " : " << i.second << '\n';

	//analisador.inserir_texto("../recursos/textos_alternativos/alt1.txt");
}
