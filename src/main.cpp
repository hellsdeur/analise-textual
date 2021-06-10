#include "analisador.h"
#include <map>
#include <string>

int main() {

	Catalogo cat("../recursos/base_textos/");

	Analisador analisador(cat);

	analisador.exportar_dados(50);
}