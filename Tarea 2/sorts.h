#ifndef SORTS_H
#define SORTS_H

#include <vector>

template <class T>
class Sorts{
    private:
    void swap(std::vector<T>&, int, int);
    void mergeSort(std::vector<T> &vec, int start, int end);
    void merge(std::vector<T> &vec, int start, int mid, int end);

    public:
    void ordenaSeleccion(std::vector<T> &vec);
    void ordenaBurbuja(std::vector<T> &vec);
    void ordenaMerge(std::vector<T> &vec);
    int busqSecuencial(std::vector<T> &vec, T val);
    int busqBinaria(std::vector<T> &vec, T val);
    
};

template <class T>
void Sorts<T>::swap(std::vector<T> &vec, int i, int j) {
	T aux = vec[i];
	vec[i] = vec[j];
	vec[j] = aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &vec){
	int pos;
	for (int i = vec.size()- 1; i > 0; i--){
		pos = 0;
		for (int j = 1; j <= i; j++){
			if (vec[j] >vec[pos]) {
				pos =j;
			}
		}

		if (pos != i) {
			swap(vec, i, pos);
		}
	}
}


template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &vec){
	for (int i = vec.size() - 1; i >0; i--) {
		for (int j= 0; j < i; j++) {
			if (vec[j]> vec[j + 1]) {
				swap(vec, j, j + 1);
			}
		}
	}
}

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &vec){
    mergeSort(vec, 0, vec.size() - 1);    
}

template <class T>
void Sorts<T>::mergeSort(std::vector<T> &vec, int start, int end){
    if (start < end){
        int mid = (start + end) / 2;
        mergeSort(vec, start, mid);
        mergeSort(vec, mid + 1, end);
        merge(vec, start, mid, end);
    }
}

template <class T>
void Sorts<T>::merge(std::vector<T> &vec, int start, int mid, int end){
    int i, j, k;
    std::vector<T> aux(vec.size());

	i = start;
	j = mid + 1;
	k = start;

	while (i <= mid &&j <= end) {
		if (vec[i] < vec[j]) {
			aux[k] = vec[i];
			i++;
		} 
        else {
			aux[k] = vec[j];
			j++;
		}
		k++;
	}

	if (i > mid) {
		for (; j <= end; j++) {
			aux[k++] = vec[j];
		}
	} 
    else {
		for (; i <= mid; i++) {
			aux[k++] = vec[i];
		}
	}

    for (k=start; k<=end; k++){
        vec[k]=aux[k];
    }
}

template <class T>
int Sorts<T>::busqSecuencial(std::vector<T> &vec, T val){
    for (int i=0; i<vec.size(); i++){
        if (vec[i]==val){
            return i;
        }
    }
    return -1;

}

template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &vec, T val){
    int high = vec.size()-1;
    int low = 0;
    while (low<=high){
        int mid = (high + low) / 2;
        if (vec[mid]==val){
            return mid;
        }
        else if (val<vec[mid]){
            high = mid - 1;
        }
        else if (val>vec[mid]){
            low = mid + 1;
        }
    }
    return -1;
}


#endif