#include "analisador.h"
#include <string>
#include <regex>
#include <iostream>

int main() {

	Catalogo cat("../base_textos/");

	Analisador analisador(cat);

	analisador.ranking(50);

	// analisador.print(0);
	// analisador.print(0);
}
