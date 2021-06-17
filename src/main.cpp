#include <iostream>
// #include "analise-textual/analisador.hpp"
#include "compressao/compactador.hpp"

int main() {

	Catalogo catalogo("../recursos/base_textos/");

	// Analisador analisador(catalogo, 101);

	//analisador.exportar_dados();

	Compactador compactador(catalogo);

	// std::fstream kkk;
	// kkk.open("zzz.txt", std::ios::out | std::ios::app);
	// for (auto i : f) {
	// 	kkk << i.first << " : " << i.second << '\n';
	// }
	// kkk.close();

	//analisador.inserir_texto("../recursos/textos_alternativos/alt1.txt");
}
