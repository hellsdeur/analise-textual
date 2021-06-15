#include "analisador.hpp"

int main() {

	Catalogo catalogo("../recursos/base_textos/");

	Analisador analisador(catalogo, 100);

	analisador.exportar_dados();

	// analisador.inserir_texto("../textos/exemplo/01.txt", max_comuns);
}