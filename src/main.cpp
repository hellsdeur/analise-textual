#include <iostream>
#include "analise-textual/analisador.hpp"
#include "compressao/compactador.hpp"
#include "analise-desempenho/buscador.hpp"

int main() {

	Catalogo catalogo("../recursos/base_textos/");

	// Analisador analisador(catalogo, 101);


	//analisador.exportar_dados();

	Compactador compactador(catalogo);
	// compactador.print();

	Buscador buscador(catalogo, compactador);
	// buscador.buscar_comprimido("bankability");
	// buscador.buscar_nao_comprimido("bankability");

	//analisador.inserir_texto("../recursos/textos_alternativos/alt1.txt");
}
