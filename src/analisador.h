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
		std::list<std::string> stop_words;

	public:
		Analisador(Catalogo c) {
			this->c = c;
			preencher_stop_words();
			analisar();
		}

		void preencher_stop_words() {
			std::ifstream arquivo;
			arquivo.open("stop_words.txt");
			std::string s;

			while (std::getline(arquivo, s)) {
				this->stop_words.push_back(s);
			}
		}

		void print_stop_words() {
			std::cout << "Largura da lista de stop words = " << this->stop_words.size() << '\n';
			for (auto i: this->stop_words) {
				std::cout << i << '\n';
			}
		}

		void analisar() {
			std::ifstream arquivos[30];

			// varre e abre os 30 arquivos
			for (int i = 0; i < 30; i++) {
				std::string s;
				arquivos[i].open(this->c.get_nome(i));

				// para cada arquivo, ler as linhas na string s
				while (std::getline(arquivos[i], s)) {
					std::regex r(R"([a-zA-Z_]+(?:['_-][a-zA-Z_]+)*)");
					std::sregex_iterator it1; // regex

					// aplica a regex e verifica se a palavra não é stop word
					for (it1 = std::sregex_iterator(s.begin(), s.end(), r);
					it1 != std::sregex_iterator();
					++it1) {
    					std::smatch m = *it1;
						std::unordered_map<std::string, int>::const_iterator it = this->dicionario.find(m.str());

						if (it == this->dicionario.end()) {
								std::pair<std::string, int> palavra(m.str(), 1);
								this->dicionario.insert(palavra);
                        }
							// palavra estiver inclusa no dicionário
                        else {
								//int contador = it->second;
								this->dicionario[m.str()]++;
								//this->dicionario.erase(m.str());
								//std::pair<std::string, int> palavra(m.str(), contador+1);
								//this->dicionario.insert(palavra);
                        }

						//bool is_stopword = false;

						// verifica se a palavra é stop word
//						std::list<std::string>::const_iterator it2; // lista
//						for (it2 = this->stop_words.begin();
//							 it2 != this->stop_words.end();
//							 it2++) {
//								 std::cout << m.str() << " | " << *it2 << '\n';
//								 if (m.str() == *it2) {
//									std::cout << "ENTROU!!!!!!!!!!" << '\n';
//									is_stopword = true;
//									break;
//								 }
//							 }
//                        for(auto it2: this->stop_words){
//                            std::cout << m.str() << " | " << it2 << '\n';
//							if (m.str() == it2) {
//							std::cout << "ENTROU!!!!!!!!!!" << '\n';
//							is_stopword = true;
//							break;
//                            }
//                        }
						//for (int j = 0; j < 200; j++) {
						//	if (m.str() != arr[j]) {
						//		if (it == this->dicionario.end()) {
						//			std::pair<std::string, int> palavra(m.str(), 1);
						//			this->dicionario.insert(palavra);
						//		}
						//		// palavra estiver inclusa no dicionário
						//		else {
						//			int contador = it->second;
						//			this->dicionario.erase(m.str());
						//			std::pair<std::string, int> palavra(m.str(), contador+1);
						//			this->dicionario.insert(palavra);
						//		}
						//	}
						//}

//						if (!is_stopword) {
//							// palavra não inclusa no dicionário
//							if (it == this->dicionario.end()) {
//								std::pair<std::string, int> palavra(m.str(), 1);
//								this->dicionario.insert(palavra);
//							}
//							// palavra estiver inclusa no dicionário
//							else {
//								//int contador = it->second;
//								this->dicionario[m.str()]++;
//								//this->dicionario.erase(m.str());
//								//std::pair<std::string, int> palavra(m.str(), contador+1);
//								//this->dicionario.insert(palavra);
//							}
//						}

					}
				}
			}
		}

        void print() {
			for (auto i: this->dicionario) {
				std::cout << i.first << ": " << i.second << '\n';
			}
		}

		bool verificarStopWords(std::string s){
            for(auto i: this->stop_words){
                if(s == i) return true;
            }
            return false;
		}

		void ranking(){
		    std::unordered_map<std::string, int>::const_iterator it;
            for(it = dicionario.begin(); it != dicionario.end(); it++){
                if(!verificarStopWords((*it).first)) lista.push_back(*it);
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
