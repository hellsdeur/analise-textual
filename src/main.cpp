#include "analisador.hpp"
#include <unordered_map>

int main() {

	Catalogo catalogo("../recursos/base_textos/");

	Analisador analisador(catalogo, 100);

	// analisador.exportar_dados();

	std::unordered_map<unsigned char, int> f =  analisador.get_frequencias();
	
	for (auto i : f) {
		std::cout << i.first << " : " << i.second << '\n';
	}
	// analisador.inserir_texto("../textos/exemplo/01.txt", max_comuns);
}