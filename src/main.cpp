#include "analisador.h"
#include <map>
#include <string>

int main() {

	Catalogo cat("../recursos/base_textos/");

	Analisador analisador(cat);

	int max_comuns = 50;

	analisador.exportar_dados(max_comuns);

	// analisador.inserir_texto("../textos/exemplo/01.txt", max_comuns);
}