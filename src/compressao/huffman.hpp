#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include <fstream>

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
	void gerar_codigos(No* raiz, int [], int);

public:
	No* raiz;
	std::unordered_map<unsigned char, std::string> codigos;

	Huffman() {}
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
	int arr[MAX_ALTURA], top = 0;
	gerar_codigos(this->raiz, arr, top);
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

inline void Huffman::gerar_codigos(No* raiz, int arr[], int top) {
	if (raiz->esq) {
		arr[top] = 0;
		gerar_codigos(raiz->esq, arr, top + 1);
	}

	if (raiz->dir) {
		arr[top] = 1;
		gerar_codigos(raiz->dir, arr, top + 1);
	}

	if (!raiz->esq && !raiz->dir) {
		std::string s;

		for (int i = 0; i < top; i++)
			s += std::to_string(arr[i]);
		
		this->codigos.insert(std::make_pair(raiz->dado, s));
	}
}

inline void Huffman::print() {
	std::unordered_map<unsigned char, std::string>::const_iterator it;
	
	for (it = this->codigos.begin(); it != this->codigos.end(); it++) {
		std::cout << (*it).first << " : " << (*it).second << '\n';
	}
}

#endif