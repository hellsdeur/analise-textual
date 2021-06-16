#include <cstdlib>
#include <unordered_map>

class NoMinHeap {
public:
	char dado;
	unsigned freq;
	NoMinHeap* esq, * dir;
};

class MinHeap {
private:
	unsigned tamanho;		// tamanho atual
	unsigned capacidade;	// tamanho limite
	NoMinHeap** array;		// ponteiro para minheaps

public:
	NoMinHeap* novo_no(char caractere, unsigned frequencia) {
		NoMinHeap* temp = (NoMinHeap*) malloc(sizeof(NoMinHeap));

		temp->esq = temp->dir = NULL;
		temp->dado = caractere;
		temp->freq = frequencia;

		return temp;
	}

	MinHeap* criar_minheap(unsigned capacidade) {
		MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));

		minHeap->tamanho = 0;

		minHeap->capacidade = capacidade;

		minHeap->array = (NoMinHeap**) malloc(minHeap->capacidade * sizeof(NoMinHeap*));

		return minHeap;
	}

	void permutar(NoMinHeap** a, NoMinHeap** b) {
		NoMinHeap* t = *a;

		*a = *b;
		*b = t;
	}
};

class Huffman {
private:

public:
	NoMinHeap* construir(std::unordered_map<unsigned char, int>);
};

inline NoMinHeap* Huffman::construir (std::unordered_map<unsigned char, int> frequencias) {
	NoMinHeap* esq, *dir, *top;

	NoMinHeap* minheap;
}