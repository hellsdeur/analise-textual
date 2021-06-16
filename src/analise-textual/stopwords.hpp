#include <fstream>
#include "../estruturas-algoritmos/trie.hpp"

class Stop_Words {
private:
	Trie trie;
	
	void preencher_stop_words(std::string);
	
public:
	Stop_Words() {
		preencher_stop_words("../recursos/stop_words.txt");
	}
	bool is_stopword(std::string);
};

inline void Stop_Words::preencher_stop_words(std::string caminho) {
	std::ifstream arquivo;
	std::string s;

	arquivo.open(caminho);

	while (std::getline(arquivo, s)) {
		this->trie.inserir(s);
	}
}

inline bool Stop_Words::is_stopword(std::string s) {
	return this->trie.buscar(s);
}