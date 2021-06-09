#include "analisador.h"

int main() {

	Catalogo cat("../base_textos/");

	Analisador analisador(cat);

	analisador.exportar_dados(50);
}
