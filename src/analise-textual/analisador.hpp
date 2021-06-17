#include <cstdlib>
#include <string>
#include <list>
#include <regex>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include "catalogo.hpp"
#include "stopwords.hpp"
#include "dicionario.hpp"

class Analisador {
private:
	Catalogo catalogo;					// caminhos para os arquivos da base
	int max_comuns;						// max de palavras a analisar
	Stop_Words stop_words;				// manipulador de stop words
	Dicionario dic;						// dic geral, todas as pal
	std::vector<Dicionario> vec_dic;	// vetor de dics, pal de cada texto
	std::vector<std::pair<std::string, int>> ranking;
	std::unordered_map<unsigned char, unsigned int> frequencias;

	Dicionario processar(fs::path, Dicionario);
	void analisar_cada_texto();
	void analisar_todos_textos();
	void escrever_linha(std::fstream&, Dicionario);

public:
	Analisador(Catalogo catalogo, int max_comuns) {
		this->catalogo = catalogo;
		this->max_comuns = max_comuns;
		analisar_cada_texto();
		analisar_todos_textos();
		this->ranking = this->dic.rankear();
	}

	void print(int i);
	void print_geral();
	void exportar_dados();
	void inserir_texto(fs::path);
	std::unordered_map<unsigned char, unsigned int> get_frequencias();
};

// --------------------------- MÉTODOS PRIVADOS ---------------------------

inline Dicionario Analisador::processar(fs::path caminho, Dicionario dicionario) {

    std::ifstream arquivo;
    std::string s;
	bool catalogado = this->catalogo.buscar(caminho);

    arquivo.open(caminho);
	
	// para cada linha no arquivo
    while (std::getline(arquivo, s)) {
		// se catalogado, registra cada unsigned char no umap de frequencias
		if (catalogado) {
			std::unordered_map<unsigned char, unsigned int>::const_iterator it_umap;
			for (int i = 0; i < s.size(); i++) {
				it_umap = this->frequencias.find(s[i]);

				if (it_umap == this->frequencias.end())
					this->frequencias.insert(std::make_pair(s[i], 1));
				else
					this->frequencias[s[i]]++;
			}
		}
    	// aplica regex para quebrar palavras por espaços
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
		Dicionario d(this->catalogo.get_caminho(i));

		d = processar(this->catalogo.get_caminho(i), d);
		this->vec_dic.push_back(d);
    }
}

inline void Analisador::analisar_todos_textos() {

	for (int i = 0; i < 30; i++) {
        this->dic = processar(this->catalogo.get_caminho(i), this->dic);
    }
}

// --------------------------- MÉTODOS PÚBLICOS ---------------------------

inline void Analisador::print(int i) {
	for (auto i: this->vec_dic[i].get_mapa()) {
		std::cout << i.first << ": " << i.second << '\n';
	}
}

inline void Analisador::print_geral() {
	for (auto i: this->dic.get_mapa()) {
		std::cout << i.first << ": " << i.second << '\n';
	}
}

inline void Analisador::exportar_dados() {
	std::fstream fpalavras, fcontagem;
	int n = 0;

	std::remove("../resultados/palavras_comuns.txt");
	std::remove("../resultados/contagem_comuns.csv");

	fpalavras.open("../resultados/palavras_comuns.txt", std::ios::out | std::ios::app);
	fcontagem.open("../resultados/contagem_comuns.csv", std::ios::out | std::ios::app);

	fcontagem << "ARQUIVO, ";
	std::vector<std::pair<std::string, int>>::const_iterator it;
	for (it = this->ranking.begin(); it != this->ranking.end(); it++) {
		fpalavras << it->first;
		fcontagem << it->first;
		if (n < this->max_comuns) {
			fpalavras << '\n';
			fcontagem << ", ";
		}
		else break;
		n++;
	}
	fpalavras.close();
	fcontagem << '\n';

	for (int i = 0; i < 30; i++) {
		escrever_linha(fcontagem, this->vec_dic[i]);	
	}

	fcontagem.close();
}

inline void Analisador::inserir_texto(fs::path caminho) {
	Dicionario d(caminho);
	std::fstream fcontagem;

	fcontagem.open("../resultados/contagem_comuns.csv", std::ios::out | std::ios::app);
	
	d = processar(caminho, d);

	escrever_linha(fcontagem, d);

	fcontagem.close();
}

inline void Analisador::escrever_linha(std::fstream &fcontagem, Dicionario d) {
	int n = 0;
	fcontagem << d.get_caminho().filename() << ", ";

	std::vector<std::pair<std::string, int>>::const_iterator it;
	for (it = this->ranking.begin(); it != this->ranking.end(); it++) {
		fcontagem << d.get_mapa()[it->first];
		if (n < this->max_comuns)
			fcontagem << ", ";
		else break;
		n++;
	}
	fcontagem << '\n';
}

inline std::unordered_map<unsigned char, unsigned int> Analisador::get_frequencias() {
	return this->frequencias;
}