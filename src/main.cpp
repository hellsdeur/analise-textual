#include "catalogo.h"
#include "lista_encadeada/lista.h"
#include <fstream>
#include <string>
#include <regex>
#include <iostream>

int main() {

	std::ifstream arquivos[30];
	ListaEncadeada lista;
	
	Catalogo cat("../base_textos/");

	for (int i = 0; i < 30; i++) {
		std::string s;

		arquivos[i].open(cat.get_nome(i));

		while (std::getline(arquivos[i], s)) {
			std::regex r(R"([a-zA-Z_]+(?:['_-][a-zA-Z_]+)*)");
			std::sregex_iterator i;

			for (i = std::sregex_iterator(s.begin(), s.end(), r);
				i != std::sregex_iterator();
				++i) {
    			std::smatch m = *i;
				lista.inserir(m.str());
			}
			// std::regex_match(s, m, r);
			// for (unsigned i = 0; i < m.size(); i++) {
			// 	std::cout << m[i] << '\n';
			// 	lista.inserir(m[i]);
			// }
			
		}
	}

}