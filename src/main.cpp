#include <iostream>
#include "analise-textual/analisador.hpp"
#include "compressao/compactador.hpp"
#include "analise-desempenho/buscador.hpp"

int main() {
	// Tarefa 1 e 2
	Catalogo catalogo("../recursos/base_textos/");
	Analisador analisador(catalogo,101);
	// analisador.exportar_dados();

	// Tarefa 3
	analisador.inserir_texto("../recursos/textos_alternativos/alt1.txt");

	// Tarefa 4
	Compactador compactador(catalogo);
	compactador.print();

	// Tarefa 5
	Buscador buscador(catalogo, compactador);
	buscador.buscar_comprimido("Lenses");
	buscador.buscar_nao_comprimido("Lenses");
}