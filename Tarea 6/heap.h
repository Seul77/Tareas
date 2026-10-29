#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <sstream>
#include <iostream>

template <class T>
class Heap{
    private:
    T *data;
    unsigned int tam;
    unsigned int count;
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);

    public:
	Heap(unsigned int) ;
	~Heap();
	bool empty() const;
    void push(T);
	void pop();
	unsigned int size() const;
	T top() const;
	std::string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int sze){
    tam = sze;
    count = 0;
    data = new T[tam];
}

template <class T>
Heap<T>::~Heap(){
	delete [] data;
	tam = 0;
	count = 0;
	data = 0;
}

template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le <= count && data[le] < data[min]) {
		min = le;
	}
	if (ri <= count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		T aux = data[pos];
		data[pos] = data[min];
		data[min] = aux;
		heapify(min);
	}
}

template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}

template <class T>
void Heap<T>::push(T val){
	int pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

template <class T>
void Heap<T>::pop(){
	count--;
	data[0] = data[count];
	heapify(0);
}

template <class T>
unsigned int Heap<T>::size() const{
	return count;
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return ((2 * pos) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return ((2 * pos) + 2);
}

template <class T>
T Heap<T>::top() const{
	return data[0];
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";
	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
		aux << data[i];
	}
	aux << "]";
	return aux.str();
}

#endif