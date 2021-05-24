#include "catalogo.h"
#include <fstream>

int main() {

	// GerenciadorArquivos gerarq("../base_textos/");

	std::ifstream arquivos[30];
	
	Catalogo cat("../base_textos/");

	for (int i = 0; i < 30; i++) {
		arquivos[i].open(cat.get_nome(i));
	}

}