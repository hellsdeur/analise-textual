#include "../estruturas-de-dados/minheap.hpp"
#include <unordered_map>

#define MAX_ALTURA 10000

class Huffman {
private:
	std::unordered_map<unsigned char, unsigned int> mapa_freq;
	No* criar_huffman();
	int arr[MAX_ALTURA];
	int top;

	void print_arr(int [], int);
	void print_codes(No, int [], int);

public:
	No* raiz;

	Huffman(std::unordered_map<unsigned char, unsigned int>);
	void print();
};

inline Huffman::Huffman(std::unordered_map<unsigned char, unsigned int> mapa_freq) {
	this->mapa_freq = mapa_freq;
	this->raiz = criar_huffman();
	this->top = 0;
}

inline No* Huffman::criar_huffman() {
	No* esq, * dir, * top;
	MinHeap* minheap = new MinHeap(this->mapa_freq);

	while (!minheap->heap_unitario()) {
		esq = minheap->extrair_min();
		dir = minheap->extrair_min();
		top = minheap->novo_no('$', esq->freq + dir->freq);
		
		top->esq = esq;
		top->dir = dir;

		minheap->inserir(top);
	}
	return minheap->extrair_min();	
}

inline void Huffman::print_arr(int arr[], int n) {
	for (int i = 0; i < n; i++)
		std::cout << arr[i];
	std::cout << '\n';
}

inline void Huffman::print_codes(No raiz, int arr[], int top) {
	if (raiz.esq) {
		arr[top] = 0;
		print_codes(*raiz.esq, arr, top + 1);
	}

	if (raiz.dir) {
		arr[top] = 1;
		print_codes(*raiz.dir, arr, top + 1);
	}

	if (raiz.folha()) {
		std::cout << raiz.dado << ": ";
		print_arr(arr, top);
	}
}

inline void Huffman::print() {
	print_codes(*this->raiz, this->arr, this->top);
}