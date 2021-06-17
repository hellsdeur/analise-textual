#include <iostream>
#include <unordered_map>
#include <queue>

class No {
public:
	unsigned char dado;
	unsigned int freq;
	No* esq;
	No* dir;

	No(unsigned char, unsigned int);
};

inline No::No(unsigned char dado, unsigned int freq) {
	this->dado = dado;
	this->freq = freq;
	this->esq = this->dir = nullptr;
}

// ----------------------------------------------------------------------------

class Compare {
public:
	bool operator()(No* a, No* b) {
		return a->freq > b->freq;
	}
};

// ----------------------------------------------------------------------------

#define MAX_ALTURA 1000

class Huffman {
private:
	std::priority_queue<No*, std::vector<No*>, Compare> pq;

	No* construir();
	void print_codes(No* raiz, int [], int);

public:
	No* raiz;

	Huffman(std::unordered_map<unsigned char, unsigned int>);
	void print();
};

inline Huffman::Huffman(std::unordered_map<unsigned char, unsigned int> mapa_freq) {
	std::unordered_map<unsigned char, unsigned int>::const_iterator it;

	for (it = mapa_freq.begin(); it != mapa_freq.end(); it++) {
		No* novo = new No((*it).first, (*it).second);
		pq.push(novo);
	}

	this->raiz = construir();
}

inline No* Huffman::construir() {
	while (pq.size() != 1) {
		No* esq = pq.top();
		pq.pop();

		No* dir = pq.top();
		pq.pop();
		
		No* no = new No('$', esq->freq + dir->freq);

		no->esq = esq;
		no->dir = dir;

		pq.push(no);
	}
	return pq.top();
}

inline void Huffman::print_codes(No* raiz, int arr[], int top) {
	if (raiz->esq) {
		arr[top] = 0;
		print_codes(raiz->esq, arr, top + 1);
	}

	if (raiz->dir) {
		arr[top] = 1;
		print_codes(raiz->dir, arr, top + 1);
	}

	if (!raiz->esq && !raiz->dir) {
		std::cout << raiz->dado << " ";

		for (int i = 0; i < top; i++)
			std::cout << arr[i];
		std::cout << '\n';
	}
}

inline void Huffman::print() {
	int arr[MAX_ALTURA], top = 0;
	print_codes(this->raiz, arr, top);
}