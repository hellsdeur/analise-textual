#include <fstream>
#include <vector>
#include <string>

class Stop_Words {
	private:
		std::vector<std::string> stop_words;
		
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
		this->stop_words.push_back(s);
	}
}

inline bool Stop_Words::is_stopword(std::string s) {
	std::vector<std::string>::const_iterator it_sw;

	for (it_sw = this->stop_words.begin(); it_sw != this->stop_words.end(); it_sw++)
		if (s == *it_sw) return true;
	return false;
}