#include <string>
#include <unordered_map>
#include <utility>
class Dicionario {
	private:
		std::string nome_arquivo;
		std::unordered_map<std::string, int> mapa;
	
	public:
		// construtor default, para o dicionário geral
		Dicionario() {}

		// construtor para os dicionários individuais
		Dicionario(std::string nome_arquivo) {
			this->nome_arquivo = nome_arquivo;
		}

		void inserir(std::string);
		std::string get_nome_arquivo();
		std::unordered_map<std::string, int> get_mapa();
};

inline void Dicionario::inserir(std::string palavra) {
	std::unordered_map<std::string, int>::const_iterator it;

	// procura palavra no dicionário
	it = this->mapa.find(palavra);

	// palavra não inclusa no dicionário, adicionar nova ocorrência
	if (it == this->mapa.end())
		this->mapa.insert(std::make_pair<std::string, int>(palavra.c_str(), 1));
	// palavra inclusa no dicionário, incrementar contador
	else
		this->mapa[palavra]++;
}

inline std::string Dicionario::get_nome_arquivo() {
	return this->nome_arquivo;
}

inline std::unordered_map<std::string, int> Dicionario::get_mapa() {
	return this->mapa;
}