#include <experimental/filesystem>
#include <string>
#include <iostream>

namespace fs = std::experimental::filesystem;

class Catalogo {
private:
	int n;
	fs::path diretorio;
	std::vector<fs::path> arquivos;
	void preencher_nomes_arquivos();

public:
	Catalogo(std::string diretorio) {
		n = 0;
		this->diretorio = diretorio;
		preencher_nomes_arquivos();
	}

	Catalogo() {}

	std::string get_nome(int);
};

inline void Catalogo::preencher_nomes_arquivos() {
	for (auto &p : fs::directory_iterator(this->diretorio)) {
		if (fs::is_regular_file(p.status())) {
			arquivos.push_back(p.path());
			n++;
		}
	}	
}

inline std::string Catalogo::get_nome(int i) {
	return arquivos[i].filename();
}