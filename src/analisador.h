#include "catalogo.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>
#include <utility>
#include <iostream>
#include <list>
#include<algorithm>

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
            }

            auto sortRuleLambda = [] (std::pair<std::string, int> const& s1, std::pair<std::string, int> const& s2) -> bool
            {
                return s1.second > s2.second;
            };

            lista.sort(sortRuleLambda);
            std::list<std::pair<std::string, int>>::const_iterator it2;
            int cnt = 0;
            for(it2 = lista.begin(); it2 != lista.end(); it2++){
                cnt++;
                std::cout << (*it2).first << "-" << (*it2).second << std::endl;
                if(cnt > 20) break;
            }
		}

};
