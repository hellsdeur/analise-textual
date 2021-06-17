#include "../estruturas-de-dados/minheap.hpp"
#include <unordered_map>

#define MAX_ALTURA 100

class Huffman {
private:
	No criar_huffman(std::unordered_map<unsigned char, unsigned int>);
	int arr[MAX_ALTURA];
	int top;

	void print_arr(int [], int n);
	void print_codes(No, int [], int);

public:
	No raiz;

	Huffman(std::unordered_map<unsigned char, unsigned int>);
	void print();
};

inline Huffman::Huffman(std::unordered_map<unsigned char, unsigned int> mapa_freq) {
	this->raiz = criar_huffman(mapa_freq);
	this->top = 0;
}

inline No Huffman::criar_huffman(std::unordered_map<unsigned char, unsigned int> mapa_freq) {
	MinHeap* minheap = new MinHeap(mapa_freq);

	while (!minheap->heap_unitario()) {
		No esq = minheap->extrair_min();
		No dir = minheap->extrair_min();
		No top('$', esq.freq + dir.freq);
		
		top.esq = &esq;
		top.dir = &dir;

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
	print_codes(this->raiz, this->arr, this->top);
}