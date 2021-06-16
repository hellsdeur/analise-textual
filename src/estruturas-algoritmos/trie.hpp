#include <cstdlib>
#include <string>

#define N_ALFABETO 127

class Trie {
private:
	bool fim;
	Trie* filhos[N_ALFABETO];
	Trie* criar_no();

public:
	Trie* raiz;

	Trie() {
		this->raiz = criar_no();
	} 
	void inserir(std::string);
	bool buscar(std::string);
};

inline Trie* Trie::criar_no() {
	Trie* t = (Trie*) malloc(sizeof(Trie));
	for (int i = 0; i < N_ALFABETO; i++) {
		t->filhos[i] = nullptr;
	}
	t->fim = false;

	return t;
}

inline void Trie::inserir(std::string chave) {
	Trie* r = this->raiz;

	for (int i = 0; i < chave.size(); i++) {
		if (r->filhos[chave[i]] == nullptr)
			r->filhos[chave[i]] = criar_no();
		r = r->filhos[chave[i]];
	}

	r->fim = true;
}

inline bool Trie::buscar(std::string chave) {
	if (this->raiz == nullptr)
		return false;

	Trie* r = this->raiz;

	for (int i = 0; i < chave.size(); i++) {
		r = r->filhos[chave[i]];
		if (r == nullptr)
			return false;
	}
	return r->fim;
}
