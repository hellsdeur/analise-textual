#include "catalogo.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>
#include <iostream>
#include <list>
#include <utility>

class Analisador {
	private:
		Catalogo catalogo;
		std::unordered_map<std::string, int> dicionario, arr_dicionario[30];
		std::list<std::pair<std::string, int>> lista;
		std::list<std::string> stop_words;

		void preencher_stop_words();
		bool is_stopword(std::string);
		void analisar();
		void processar(std::string caminho_arquivo, std::unordered_map<std::string, int> dicionario);
		void analisar_cada_texto();
		void analisar_todos_textos();


	public:
		Analisador(Catalogo catalogo) {
			this->catalogo = catalogo;
			preencher_stop_words();
	//		analisar();
            analisar_cada_texto();
            analisar_todos_textos();
		}

	//	void print();
		void ranking(int);
		void print(int i);
};

inline void Analisador::preencher_stop_words() {
	std::ifstream arquivo;
	arquivo.open("../recursos/stop_words_improved.txt");
	std::string s;

	while (std::getline(arquivo, s))
		this->stop_words.push_back(s);
}

inline bool Analisador::is_stopword(std::string s) {
	std::list<std::string>::const_iterator it_sw;

	for (it_sw = this->stop_words.begin(); it_sw != this->stop_words.end(); it_sw++)
		if (s == *it_sw) return true;
	return false;
}

inline void Analisador::analisar() {
	std::ifstream arquivos[30];

	// varre e abre os 30 arquivos
	for (int i = 0; i < 30; i++) {
		std::string s;

		arquivos[i].open(this->catalogo.get_nome(i));

		// para cada linha, aplica regex para quebrar palavras por espaços
		while (std::getline(arquivos[i], s)) {
			std::regex r(R"([a-zA-Z_]+(?:['_-][a-zA-Z_]+)*)");
			std::sregex_iterator it_re;

			// iterando sobre cada padrão da regex
			for (it_re = std::sregex_iterator(s.begin(), s.end(), r); it_re != std::sregex_iterator(); it_re++) {
  				std::smatch match;
				std::string palavra;
				std::unordered_map<std::string, int>::const_iterator it_di;

				// extrai o match da regex, cast para string e troca letras para minúsculas
				match = *it_re;
				palavra = match.str();
				std::for_each(palavra.begin(), palavra.end(), [](char &c) {
					c = ::tolower(c);
				});

				// se palavra não for stop word, insira no dicionário
				if (!is_stopword(palavra)) {
					// procura palavra no dicionário
					it_di = this->dicionario.find(palavra);

					// palavra não inclusa no dicionário
					if (it_di == this->dicionario.end())
						this->dicionario.insert(std::make_pair<std::string, int>(palavra.c_str(), 1));
					// palavra inclusa no dicionário
					else
						this->dicionario[palavra]++;
				}
			}
		}
	}
}

inline void Analisador::processar(std::string caminho_arquivo, std::unordered_map<std::string, int> dicionario){

    std::ifstream arquivo;
    std::string s;

    arquivo.open(caminho_arquivo);

    // para cada linha, aplica regex para quebrar palavras por espaços
    while (std::getline(arquivo, s)) {
			std::regex r(R"([a-zA-Z_]+(?:['_-][a-zA-Z_]+)*)");
			std::sregex_iterator it_re;

			// iterando sobre cada padrão da regex
			for (it_re = std::sregex_iterator(s.begin(), s.end(), r); it_re != std::sregex_iterator(); it_re++) {
  				std::smatch match;
				std::string palavra;
				std::unordered_map<std::string, int>::const_iterator it_di;

				// extrai o match da regex, cast para string e troca letras para minúsculas
				match = *it_re;
				palavra = match.str();
				std::for_each(palavra.begin(), palavra.end(), [](char &c) {
					c = ::tolower(c);
				});

				// se palavra não for stop word, insira no dicionário
				if (!is_stopword(palavra)) {
					// procura palavra no dicionário
					it_di = dicionario.find(palavra);

					// palavra não inclusa no dicionário
					if (it_di == dicionario.end())
						dicionario.insert(std::make_pair<std::string, int>(palavra.c_str(), 1));
					// palavra inclusa no dicionário
					else
						dicionario[palavra]++;
				}
			}
    }
}

inline void Analisador::analisar_cada_texto(){

    std::ifstream arquivos[30];,

    // varre e abre os 30 arquivos
	for (int i = 0; i < 30; i++) {
        processar(this->catalogo.get_nome(i), this->arr_dicionario[i]);
    }
}


inline void Analisador::analisar_todos_textos(){

    std::ifstream arquivos[30];

	// varre e abre os 30 arquivos
	for (int i = 0; i < 30; i++) {
        processar(this->catalogo.get_nome(i), this->dicionario);
    }
}

inline void Analisador::print(int i) {
	for (auto i: this->arr_dicionario[i]) {
		std::cout << i.first << ": " << i.second << '\n';
	}
}

inline void Analisador::ranking(int count) {
	std::unordered_map<std::string, int>::const_iterator it;
	std::list<std::pair<std::string, int>>::const_iterator it2;

	for (it = dicionario.begin(); it != dicionario.end(); it++) {
		lista.push_back(*it);
	}

	auto sortRuleLambda = [] (std::pair<std::string, int> const& s1, std::pair<std::string, int> const& s2) -> bool {
		return s1.second > s2.second;
	};

	lista.sort(sortRuleLambda);

	for (it2 = lista.begin(); it2 != lista.end(); it2++) {
		std::cout << (*it2).first << "-" << (*it2).second << std::endl;
		count--;
		if (count == 0) break;
    }
}
