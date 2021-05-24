#include <cstring>		// strcmp
#include <fstream>		// std::ifstream
#include <dirent.h>		// dirent

#define MAX_N 30

class GerenciadorArquivos {
	private:
		std::string caminho;
		std::string nomes_arquivos[MAX_N];
		std::ifstream arquivos[MAX_N];

		// preeenche vetor de nomes de arquivos
		void preencher_nomes_arquivos() {
			char diretorio[this->caminho.length()];
			DIR* p;
			struct dirent* d;

			strcpy(diretorio, caminho.c_str());

			p = opendir(diretorio);

			if (p == NULL) {
				perror("Diretório não encontrado");
				exit(-1);
			}

			int i = 0;
			while ((d = readdir(p)) != NULL) {
				if ((strcmp(d->d_name, ".") != 0) && (strcmp(d->d_name, "..") != 0)) {
					std::string nome_arquivo(d->d_name);
					nomes_arquivos[i] = nome_arquivo;
					i++;
				}
			}
		}

		// preenche array de ifstreams, baseado nos nomes dos arquivos
		void abrir_arquivos() {
			for (int i = 0; i < MAX_N; i++) {
				arquivos[i].open(nomes_arquivos[i]);
			}
		}

		// fecha os arquivos abertos contidos no array de ifstreams
		void fechar_arquivos() {
			for (int i = 0; i < MAX_N; i++) {
				arquivos[i].close();
			}
		}

	public:
		GerenciadorArquivos(std::string caminho) {
			this->caminho = caminho;
			preencher_nomes_arquivos();
			abrir_arquivos();
		}
};