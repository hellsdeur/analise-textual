#include <string>		// std::string
#include <cstring>		// strcmp
#include <dirent.h>		// dirent

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
		if ((strcmp(d->d_name, ".") != 0) && (strcmp(d->d_name, "..") != 0)) {
			std::string nome_arquivo(d->d_name);
			nomes_arquivos[i] = caminho + nome_arquivo;
			i++;
		}
	}
}

inline std::string Catalogo::get_nome(int i) {
	return this->nomes_arquivos[i];
}