#ifndef LIST_H
#define LIST_H

#include <sstream>
#include <string>
using namespace std;

template <class T> class List;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	T value;
	Link<T> *next;

	friend class List<T>;
};


template <class T>
class List {
private:
    Link<T> *head;
    int size;
public:
	List();
    ~List();

	void insertion(T);        
	int search(T) const;    
	void update(int, T);      
	void deleteAt(int);
	void clear(); 
	bool empty() const;     
	std::string toString() const;
 

};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}
 
template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}
 
template <class T>
List<T>::List() : head(0), size(0) {}
 
template <class T>
List<T>::~List() {
	clear();
}
 
template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}
 
template <class T>
void List<T>::insertion(T val){
    Link<T> *newLink;
    newLink = new Link<T>(val);
 
    if (empty()){
		head = newLink;
	} 
	else {
        Link<T> *p = head;
        while (p->next != 0) {
			p = p->next;
		}
        p->next = newLink;
    }
    size++;
}
 
template <class T>
int List<T>::search(T val) const {
    Link<T> *p = head;
    int pos = 0;
 
    while (p != 0) {
        if (p->value == val) {
			return pos;
		}
        p = p->next;
        pos++;
    }
    return -1;
}
 
template <class T>
void List<T>::update(int ind, T val) {
	if (ind < 0 || ind >= size) {
		return;
	}
    Link<T> *p = head;
    int i = 0;
    while (i < ind) {
        p = p->next;
        i++;
    }
    p->value = val;
}
 
template <class T>
void List<T>::deleteAt(int ind) {
	if (ind < 0 || ind >= size) {
		return;
	}
    if (ind == 0) {
        Link<T> *p = head;
        head = head->next;
        delete p;
    } 
	else {
        Link<T> *p = head;
        int i = 0;
        while (i < ind - 1) {
            p = p->next;
            i++;
        }
        Link<T> *q = p->next;
        p->next = q->next;
        delete q;
    }
    size--;
}
 
#endif