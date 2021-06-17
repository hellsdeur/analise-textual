#include <iostream>
#include <cstdlib>
#include <unordered_map>

class No {
public:
	unsigned char dado;
	unsigned int freq;
	No* esq, * dir;

	bool folha();
};

inline bool No::folha() {
	return !(this->esq) && !(this->dir);
}

class MinHeap {
private:
	unsigned tamanho;
	unsigned capacidade;
	No** array;

	void permutar(No**, No**);
	void min_heapify(MinHeap*, int);
	void construir();

public:
	MinHeap* raiz;

	MinHeap(std::unordered_map<unsigned char, unsigned int> mapa_freq) {
		this->raiz = (MinHeap*) malloc(sizeof(MinHeap));
		this->raiz->capacidade = mapa_freq.size();
		this->raiz->array = (No**) malloc(mapa_freq.size() * sizeof(No*));

		int i = 0;
		std::unordered_map<unsigned char, unsigned int>::const_iterator it;
		for (it = mapa_freq.begin(); it != mapa_freq.end(); it++) {
			this->raiz->array[i] = novo_no((*it).first, (*it).second);
			i++;
		}
		this->raiz->tamanho = tamanho;
		construir();
	}

	No* novo_no(unsigned char, unsigned);
	bool heap_unitario();
	No* extrair_min();
	void inserir(No*);
	void print_arr(int [], int);
};

inline No* MinHeap::novo_no(unsigned char dado, unsigned freq) {
	No* temp = (No*) malloc(sizeof(No));

	temp->dado = dado;
	temp->freq = freq;
	temp->esq = temp->dir = nullptr;

	return temp;
}

inline void MinHeap::permutar(No** a, No** b) {
	No* temp = *a;
	*a = *b;
	*b = temp;
}

inline void MinHeap::min_heapify(MinHeap* minheap, int index) {
	int menor = index;
	int esq = 2 * index + 1;
	int dir = 2 * index + 2;

	if (esq < minheap->tamanho && minheap->array[esq]->freq < minheap->array[menor]->freq)
		menor = esq;
	
	if (dir < minheap->tamanho && minheap->array[dir]->freq < minheap->array[menor]->freq)
		menor = dir;

	if (menor != index) {
		permutar(&minheap->array[menor], &minheap->array[index]);
		min_heapify(minheap, menor);
	}

}

inline bool MinHeap::heap_unitario() {
	return this->raiz->tamanho == 1;
}

inline No* MinHeap::extrair_min() {
	No* temp = this->raiz->array[0];

	this->raiz->array[0] = this->raiz->array[this->raiz->tamanho - 1];
	this->raiz->tamanho--;
	min_heapify(this->raiz, 0);

	return temp;
}

inline void MinHeap::inserir(No* no) {
	this->raiz->tamanho++;

	int i = this->raiz->tamanho - 1;

	while (i && no->freq < this->raiz->array[(i - 1) / 2]->freq) {
		this->raiz->array[i] = this->raiz->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	this->raiz->array[i] = no;
}

inline void MinHeap::construir() {
	int n = this->raiz->tamanho - 1;

	for (int i = (n - 1) / 2; i >= 0; i--)
		min_heapify(this->raiz, i);
}