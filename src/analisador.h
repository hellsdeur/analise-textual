#include "catalogo.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>
#include <utility>
#include <iostream>
#include <list>

class Analisador {
	private:
		Catalogo c;
		std::unordered_map<std::string, int> dicionario;
		std::list<std::pair<std::string, int>> lista;

	public:
		Analisador(Catalogo c) {
			this->c = c;
			analisar();
		}

		void analisar() {
			std::ifstream arquivos[30];

			for (int i = 0; i < 30; i++) {
				std::string s;
				arquivos[i].open(this->c.get_nome(i));

				while (std::getline(arquivos[i], s)) {
					std::regex r(R"([a-zA-Z_]+(?:['_-][a-zA-Z_]+)*)");
					std::sregex_iterator i;

					for (i = std::sregex_iterator(s.begin(), s.end(), r);
					i != std::sregex_iterator();
					++i) {
    					std::smatch m = *i;
						std::unordered_map<std::string, int>::const_iterator it = this->dicionario.find(m.str());

						if (it == this->dicionario.end()) {
							std::pair<std::string, int> palavra(m.str(), 1);
							this->dicionario.insert(palavra);
						} else {
							int contador = it->second;
							this->dicionario.erase(m.str());
							std::pair<std::string, int> palavra(m.str(), contador+1);
							this->dicionario.insert(palavra);
						}

					}
				}
			}
		}

        void print() {
			for (auto i: this->dicionario) {
				std::cout << i.first << ": " << i.second << '\n';
			}
		}

		void ranking(){
		    std::unordered_map<std::string, int>::const_iterator it;
            for(it = dicionario.begin(); it != dicionario.end(); it++){
                lista.push_back(*it);
                std::cout << lista.back().first << std::endl;
            }

		}

};
