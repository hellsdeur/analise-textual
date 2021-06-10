#include <string>
#include <list>
#include <regex>
#include <fstream>
#include <iostream>
#include <vector>
#include "catalogo.h"
#include "stopwords.h"
#include "dicionario.h"

class Analisador {
	private:
		Catalogo catalogo;					// caminhos para os arquivos da base
		Stop_Words stop_words;				// manipulador de stop words
		Dicionario dic;						// dic geral, todas as pal
		std::vector<Dicionario> vec_dic;	// vec de dics, pal de cada texto
		std::list<std::pair<std::string, int>> lista;

		Dicionario processar(std::string, Dicionario);
		void analisar_cada_texto();
		void analisar_todos_textos();

	public:
		Analisador(Catalogo catalogo) {
			this->catalogo = catalogo;
			analisar_cada_texto();
			analisar_todos_textos();
			ranking();
		}

		void ranking();
		void print(int i);
		void print_geral();
		void exportar_dados(int);
};

// --------------------------- MÉTODOS PRIVADOS ---------------------------

inline Dicionario Analisador::processar(std::string caminho_arquivo, Dicionario dicionario) {

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

				// extrai o match da regex, cast para string e troca letras para minúsculas
				match = *it_re;
				palavra = match.str();
				std::for_each(palavra.begin(), palavra.end(), [](char &c) {
					c = ::tolower(c);
				});

				// se palavra não for stop word, insira no dicionário
				if (!stop_words.is_stopword(palavra))
					dicionario.inserir(palavra);
			}
    }
	arquivo.close();

	return dicionario;
}

inline void Analisador::analisar_cada_texto() {

	for (int i = 0; i < 30; i++) {
		std::string nome_arquivo = this->catalogo.get_nome(i);
		Dicionario d(nome_arquivo);

		d = processar(this->catalogo.get_nome(i), d);
		this->vec_dic.push_back(d);
    }
}

inline void Analisador::analisar_todos_textos() {

	for (int i = 0; i < 30; i++) {
        this->dic = processar(this->catalogo.get_nome(i), this->dic);
    }
}

// --------------------------- MÉTODOS PÚBLICOS ---------------------------

inline void Analisador::ranking() {
	std::unordered_map<std::string, int>::const_iterator it;
	std::list<std::pair<std::string, int>>::const_iterator it2;

	std::unordered_map<std::string, int> d = this->dic.get_mapa();

	for (it = d.begin(); it != d.end(); it++) {
		this->lista.push_back(*it);
	}

	auto sortRuleLambda = [] (std::pair<std::string, int> const& s1, std::pair<std::string, int> const& s2) -> bool {
		return s1.second > s2.second;
	};

	this->lista.sort(sortRuleLambda);
}

// inline void Analisador::print(int i) {
// 	for (auto i: this->vec_dic[i].get_mapa()) {
// 		std::cout << i.first << ": " << i.second << '\n';
// 	}
// }

// inline void Analisador::print_geral() {
// 	for (auto i: this->dic.get_mapa()) {
// 		std::cout << i.first << ": " << i.second << '\n';
// 	}
// }

inline void Analisador::exportar_dados(int q_palavras) {
	std::fstream csv;
	int n = q_palavras;
	
	std::remove("../resultados/dados_extraidos.csv");

	csv.open("../resultados/dados_extraidos.csv", std::ios::out | std::ios::app);

	csv << "Nome, ";
	
	std::list<std::pair<std::string, int>>::const_iterator it;
	for (it = this->lista.begin(); it != this->lista.end(); it++) {
		csv << it->first;
		if (n != 0) csv << ", ";
		if (n == 0) break;
		n--;
	}
	
	csv << '\n';

	for (int i = 0; i < 30; i++) {
		csv << this->vec_dic[i].get_nome_arquivo().substr(15) << ", ";

		n = q_palavras;
	
		std::list<std::pair<std::string, int>>::const_iterator it2;
		for (it2 = this->lista.begin(); it2 != this->lista.end(); it2++) {
			csv << this->vec_dic[i].get_mapa()[it2->first];
			if (n != 0) csv << ", ";
			if (n == 0) break;
			n--;
		}

		csv << '\n';

	}

	csv.close();
}