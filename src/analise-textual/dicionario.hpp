#include <string>
#include <filesystem>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <vector>

namespace fs = std::filesystem;

class Dicionario {
	private:
		fs::path caminho;
		std::unordered_map<std::string, int> mapa;

	public:
		// construtor default, para o dicionário geral
		Dicionario() {}

		// construtor para os dicionários individuais
		Dicionario(fs::path caminho) {
			this->caminho = caminho;
		}

		void inserir(std::string);
		fs::path get_caminho();
		std::unordered_map<std::string, int> get_mapa();
		std::vector<std::pair<std::string, int>> rankear();
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

inline fs::path Dicionario::get_caminho() {
	return this->caminho;
}

inline std::unordered_map<std::string, int> Dicionario::get_mapa() {
	return this->mapa;
}

inline std::vector<std::pair<std::string, int>> Dicionario::rankear() {
	std::vector<std::pair<std::string, int>> ranking;
	std::unordered_map<std::string, int>::const_iterator it;

	for (it = this->mapa.begin(); it != this->mapa.end(); it++) {
		ranking.push_back(*it);
	}

	auto sortRuleLambda = [] (std::pair<std::string, int> const& s1, std::pair<std::string, int> const& s2) -> bool {
		return s1.second > s2.second;
	};

	std::sort(ranking.begin(), ranking.end(), sortRuleLambda);

	return ranking;
}
