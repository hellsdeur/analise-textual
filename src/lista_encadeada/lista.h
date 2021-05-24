#include "no.h"

class ListaEncadeada {
	private:
		No* ini;
		No* fim;
		int n;
	
	public:
		ListaEncadeada() {
			this->ini = NULL;
			this->fim = NULL;
			n = 0;
		}

		void inserir(std::string s) {
			No* q = new No;
			q->palavra = s;
			q->prox = NULL;

			if (this->ini == NULL) {
				this->ini = q;
				this->fim = q;
			} else {
				this->fim->prox = q;
				this->fim =  this->fim->prox;
			}
		}
};