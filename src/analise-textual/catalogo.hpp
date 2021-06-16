#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

class Catalogo {
private:
	int n;
	fs::path diretorio;
	std::vector<fs::path> caminhos_arquivos;
	void preencher_caminhos_arquivos();

public:
	Catalogo(std::string diretorio) {
		n = 0;
		this->diretorio = diretorio;
		preencher_caminhos_arquivos();
	}

	Catalogo() {}

	fs::path get_caminho(int);
	bool buscar(fs::path);
};

inline void Catalogo::preencher_caminhos_arquivos() {
	for (auto &p : fs::directory_iterator(this->diretorio)) {
		if (fs::is_regular_file(p.status())) {
			this->caminhos_arquivos.push_back(p.path());
			n++;
		}
	}
}

inline fs::path Catalogo::get_caminho(int i) {
	return this->caminhos_arquivos[i];
}

inline bool Catalogo::buscar(fs::path arquivo) {
	if (std::find(this->caminhos_arquivos.begin(), this->caminhos_arquivos.end(), arquivo) != this->caminhos_arquivos.end()) {
		return true;
	}
	return false;
}
