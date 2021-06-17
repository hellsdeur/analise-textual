#include <cstdlib>
#include<iostream>
#include <unordered_map>

#define MAX_ALTURA 100

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

	void minHeapify(MinHeap *minHeap, int idx){
        int menor = idx;
        int esq = 2*idx + 1;
        int dir = 2*idx + 2;

        if(esq < minHeap->tamanho && minHeap->array[esq]->freq < minHeap->array[menor]->freq)
            menor = esq;
        if(dir < minHeap->tamanho && minHeap->array[dir]->freq < minHeap->array[menor]->freq)
            menor = dir;
        if(menor != idx){
            permutar(&minHeap->array[menor], &minHeap->array[idx]);
            minHeapify(minHeap, menor);
        }
	}

    int tamanhoIgualUm(MinHeap *minHeap){
        return(minHeap->tamanho == 1);
    }

    NoMinHeap *extrairMinimo(MinHeap *minHeap){
        NoMinHeap *temp = minHeap->array[0];
        minHeap->array[0] = minHeap->array[minHeap->tamanho - 1];
        --minHeap->tamanho;
        minHeapify(minHeap, 0);
        return temp;
    }

    void inserir(MinHeap *minHeap, NoMinHeap *noMinHeap){
        ++minHeap->tamanho;
        int i = minHeap->tamanho - 1;

        while(i && noMinHeap->freq < minHeap->array[(i - 1)/2]->freq){
            minHeap->array[i] = minHeap->array[(i - 1)/2];
            i = (i - 1)/2;
        }
        minHeap->array[i] = noMinHeap;
    }

    void construirMinHeap(MinHeap *minHeap){
        int n = minHeap->tamanho - 1;
        int i;

        for(i = (n - 1)/2; i >= 0; --i)
            minHeapify(minHeap, i);
    }

    void imprimeArr(int arr[], int n){
        int i;
        for(i = 0; i < n; i++)
            std::cout << arr[i];
        std::cout << "\n";
    }

    bool folha(NoMinHeap *raiz){
        return !(raiz->esq) && !(raiz->dir);
    }

    MinHeap *criaEConstroiMinHeap(std::unordered_map<unsigned char, int> frequencias){
        MinHeap *minHeap = criar_minheap(frequencias.size());

        std::unordered_map<unsigned char, int>::const_iterator it;
        int i = 0;
        for(it = frequencias.begin(); it != frequencias.end(); it++)
            minHeap->array[i] = novo_no((*it).first, (*it).second);
        minHeap->tamanho = frequencias.size();
        construirMinHeap(minHeap);

        return minHeap;
    }
};

class Huffman {
private:

public:
    Huffman(std::unordered_map<unsigned char, int> frequencias){
        NoMinHeap *raiz = construir(frequencias);
        int arr[MAX_ALTURA], top = 0;
        imprimirCodigos(raiz, arr, top);
    }
	NoMinHeap* construir(std::unordered_map<unsigned char, int>);
	void imprimirCodigos(NoMinHeap *raiz, int arr[], int top);
};

inline NoMinHeap* Huffman::construir (std::unordered_map<unsigned char, int> frequencias) {
	NoMinHeap* esq, *dir, *top;

	MinHeap* minHeap;
	minHeap->criaEConstroiMinHeap(frequencias);

	while(!minHeap->tamanhoIgualUm(minHeap)){
        esq = minHeap->extrairMinimo(minHeap);
        dir = minHeap->extrairMinimo(minHeap);

        top = minHeap->novo_no('$', esq->freq + dir->freq);

        top->esq = esq;
        top->dir = dir;

        minHeap->inserir(minHeap, top);
	}
	return minHeap->extrairMinimo(minHeap);
}

inline void Huffman::imprimirCodigos(NoMinHeap *raiz, int arr[], int top){
    MinHeap *minHeap;
    if(raiz->esq){
        arr[top] = 0;
        imprimirCodigos(raiz->esq, arr, top + 1);
    }

    if(raiz->dir){
        arr[top] = 1;
        imprimirCodigos(raiz->dir, arr, top + 1);
    }

    if(minHeap->folha(raiz)){
        std::cout << raiz->dado << ": ";
        minHeap->imprimeArr(arr, top);
    }
}

