#include <string>
#include <cstring>
#include <dirent.h>
#include <iostream>

#define MAX_N 30

class Catalogo {
private:
	std::string caminho;
	std::string nomes_arquivos[MAX_N];

	void preencher_nomes_arquivos();

public:
	Catalogo(std::string caminho) {
		this->caminho = caminho;
		preencher_nomes_arquivos();
	}

	Catalogo() {}

	std::string get_nome(int);
	bool buscar(std::string);
};

inline void Catalogo::preencher_nomes_arquivos() {
	char diretorio[this->caminho.length()];
	DIR* p;
	struct dirent* d;
	int i;

	strcpy(diretorio, caminho.c_str());
	p = opendir(diretorio);
	if (p == NULL) {
		perror("Diretório não encontrado");
		exit(-1);
	}
	
	i = 0;
	while ((d = readdir(p)) != NULL) {
		if (d->d_type == DT_REG) {
			std::string nome_arquivo(d->d_name);
			nomes_arquivos[i] = caminho + nome_arquivo;
			i++;
		}
	}
}

inline std::string Catalogo::get_nome(int i) {
	return this->nomes_arquivos[i];
}

inline bool Catalogo::buscar(std::string caminho) {
	for (int i = 0; i < MAX_N; i++) {
		if (this->nomes_arquivos[i] == caminho) {
			std::cout << this->nomes_arquivos[i] << " = " << caminho << '\n';
			return true;
		}
	}
	return false;
}