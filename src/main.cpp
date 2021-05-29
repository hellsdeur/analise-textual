#include "analisador.h"
#include <string>
#include <regex>
#include <iostream>

int main() {

	Catalogo cat("../base_textos/");

	Analisador analisador(cat);

	analisador.ranking();

	//analisador.print();
}
