#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>

template <class T> class BST;

template <class T>
class Node {
private:
	T value;
	Node *left, *right;

public:
	Node(T);
	void add(T);
	void removeChilds();
	void preorder(std::stringstream&) const;
	void inorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	void Level(std::stringstream&, int) const;
	int height() const;

	friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} 
		else {
			left = new Node<T>(val);
		}
	} 
	else {
		if (right != 0) {
			right->add(val);
		} 
		else {
			right = new Node<T>(val);
		}
	}
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
void Node<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
}

template <class T>
void Node<T>::Level(std::stringstream &aux, int level) const {
	if (level == 1) {
		if (aux.tellp() != 1) {
			aux << " ";
		}
		aux << value;
	} 
	else {
		if (left != 0) {
			left->Level(aux, level - 1);
		}
		if (right != 0) {
			right->Level(aux, level - 1);
		}
	}
}

template <class T>
int Node<T>::height() const {
	int l = 0;
	int r = 0;

	if (left != 0) {
		l = left->height();
	}
	if (right != 0) {
		r = right->height();
	}

	if (l > r) {
		return 1 + l;
	} 
	else {
		return 1 + r;
	}
}

template <class T>
class BST {
private:
	Node<T> *root;

public:
	BST();
	~BST();
	void add(T);
	void removeAll();
	std::string visit() const;
	int height() const;
	std::string ancestors(T) const;
	int whatlevelamI(T) const;
    std::string preorder() const;
	std::string inorder() const;
	std::string postorder() const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
void BST<T>::add(T val) {
	if (root != 0) {
		root->add(val);
	}
	else {
		root = new Node<T>(val);
	}
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (root != 0) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (root != 0) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;

	aux << "[";
	if (root != 0) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::visit() const {
	std::stringstream aux;
	std::stringstream levels;

	levels << "[";
	if (root != 0) {
		int h = root->height();
		for (int i = 1; i <= h; i++) {
			root->Level(levels, i);
		}
	}
	levels << "]";

	aux << preorder() << "\n"
	    << inorder() << "\n"
	    << postorder() << "\n"
	    << levels.str();
	return aux.str();
}

template <class T>
int BST<T>::height() const {
    if (root == 0) {
		return 0;
	}
    return root->height();
}

template <class T>
std::string BST<T>::ancestors(T val) const {
	std::stringstream aux;
	Node<T> *p = root;

	aux << "[";
	while (p != 0) {
		if (val == p->value) {
			aux << "]";
			return aux.str();
		}
		if (aux.tellp() != 1) {
			aux << " ";
		}
		aux << p->value;
		if (val < p->value) {
			p = p->left;
		} 
		else {
			p = p->right;
		}
	}
	return "[]";
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
	Node<T> *p = root;
	int level = 1;

	while (p != 0) {
		if (val == p->value) {
			return level;
		}
		if (val < p->value) {
			p = p->left;
		} 
		else {
			p = p->right;
		}
		level++;
	}
	return -1;
}

#endif