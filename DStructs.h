#include <iostream>
#include "Nodes.h"

using namespace std;

template<class ValueType>
class LinkedList {
protected:
	LNode<ValueType>* root;
	int capacity;
	int len;
public:

	LinkedList<ValueType>() : root(NULL), capacity(1000), len(0) {}
	LinkedList<ValueType>(LNode<ValueType>* root) : capacity(1000), len(1) { this->root = root; }
	LinkedList<ValueType>(int len) : root(NULL), capacity(1000), len(len) { this->root = root; }

	virtual ~LinkedList() {
		LNode<ValueType>* to_del = this->root;
		if (to_del == NULL) return;
		for (LNode<ValueType>* next = to_del->getNeighbour(); next != NULL; next = next->getNeighbour()) {
			delete to_del;
			to_del = next;
		}
		delete to_del;
		cout << endl << "Destructor has worked" << endl;
	}

	int getCapacity() const { return capacity; }
	int getLength() const { return len; }
	LNode<ValueType>* getRoot() const { return root; }

	virtual LNode<ValueType>* pop() = 0;
	virtual LNode<ValueType>* remove(int index) = 0;
	virtual LNode<ValueType>* push(LNode<ValueType>* lnode) = 0;

	virtual LNode<ValueType>* operator[](int index) = 0;

	template<class T>
	friend ostream& operator<<(ostream& fout, LinkedList<T>& list);
};

template<class T>
ostream& operator<<(ostream& fout, LinkedList<T>& list) {
	fout << "Length: " << list.len << endl;
	for (LNode<T>* res = list.root; res != NULL; res = res->getNeighbour())
		fout << *res << endl;
	return fout;
}


template<class ValueType>
class RightLinkedList : public LinkedList<ValueType> {
// root->o->o->...->o
public:

	RightLinkedList<ValueType>() : LinkedList<ValueType>() {}
	RightLinkedList<ValueType>(LNode<ValueType>* root) : LinkedList<ValueType>(root) {}
	RightLinkedList<ValueType>(int len) : LinkedList<ValueType>(len) {}


	LNode<ValueType>* operator[](int index) {
		if (index < 0 || index >= this->getLength()) return NULL;
		LNode<ValueType>* res = this->getRoot();
		for (; index > 0; index--, res = res->getNeighbour());
		return res;
	}



	LNode<ValueType>* push(LNode<ValueType>* lnode) {
		if (this->getLength() + 1 > this->getCapacity()) return NULL;
		LinkedList<ValueType>::len++;
		if (this->getRoot() == NULL) { LinkedList<ValueType>::root = lnode; return lnode; }
		LNode<ValueType>* last = this->operator[](this->getLength() - 2);
		last->setNeighbour(lnode);
		return lnode;
	}

	LNode<ValueType>* push(ValueType value) { return this->push(new LNode<ValueType>(value)); }

	LNode<ValueType>* remove(int index) {
		LNode<ValueType>* res = this->operator[](index);
		if (index - 1 < 0)
			LinkedList<ValueType>::root = res->getNeighbour();
		else
			this->operator[](index - 1)->setNeighbour(res->getNeighbour());
		LinkedList<ValueType>::len--;
		return res;
	}

	LNode<ValueType>* pop() {

		LinkedList<ValueType>::len--;
		LNode<ValueType>* res = this->getRoot();

		if (this->getLength() == 0) {
			LinkedList<ValueType>::root = NULL;
			return res;
		}

		LNode<ValueType>* prev = this->operator[](this->getLength() - 1);
		res = prev->getNeighbour();
		prev->setNeighbour(NULL);

		return res;
	}
};

template<class ValueType>
class LeftLinkedList : public LinkedList<ValueType> {
// o<-o<-o<-...<-root
// 1  2  3  ...   n
public:

	LeftLinkedList<ValueType>() : LinkedList<ValueType>() {}
	LeftLinkedList<ValueType>(LNode<ValueType>* root) : LinkedList<ValueType>(root) {}
	LeftLinkedList<ValueType>(int len) : LinkedList<ValueType>(len) {}

	LNode<ValueType>* operator[](int index) {
		if (index < 0 || index >= this->getRoot()) return NULL;
		LNode<ValueType>* res = this->getRoot();
		for (int i = this->getLength(); i != index; i--) res = res->getNeighbour();
		return res;
	}

	LNode<ValueType>* push(LNode<ValueType>* lnode) {
		if (this->getLength() + 1 > this->getCapacity()) return NULL;
		lnode->setNeighbour(this->root);
		LinkedList<ValueType>::len++;
		LinkedList<ValueType>::root = lnode;
		return lnode;
	}

	LNode<ValueType>* push(ValueType value) { return this->push(new LNode<ValueType>(value)); }

	LNode<ValueType>* pop() {

		if (this->getLength() == 0) return NULL;

		LinkedList<ValueType>::len--;
		LNode<ValueType>* res = this->getRoot();

		if (this->getLength() == 0)
			LinkedList<ValueType>::root = NULL;
		else
			LinkedList<ValueType>::root = res->getNeighbour();
		return res;
	}

	LNode<ValueType>* remove(int index) {
		if (index >= this->getLength()) return NULL;
		if (index == this->getLength()-1) return this->pop();
		LNode<ValueType>* next = this->operator[](index + 1);
		LNode<ValueType>* res = next->getNeighbour();
		next->setNeighbour(NULL);
		LinkedList<ValueType>::len--;
		return res;
	}
};

template<class ValueType>
class DoubleLinkedList {
protected:
	WNode<ValueType>* root;
	WNode<ValueType>* crown;
	int len;
	int capacity;
public:

};

template<class KeyType, class ValueType>
class Tree {
private:

	TreeNode<KeyType, ValueType>* root;
	int len;

	void delRecursively(TreeNode<KeyType, ValueType>* node) {
		if (node->getRight() != NULL) delRecursively(node->getRight());
		if(node->getLeft()!=NULL) delRecursively(node->getLeft());
		delete node;
	}

public:

	Tree() : root(), len(0) {}
	Tree(int n) : root(), len(1) {}
	Tree(TreeNode<KeyType, ValueType> root) : root(root), len(0) {}

	~Tree() {
		if (root != NULL)
			delRecursively(root);
	}

	TreeNode<KeyType, ValueType>* getRoot() const { return root; }
	int getLength() const { return len; }

	virtual TreeNode<KeyType, ValueType>* push(TreeNode<KeyType, ValueType>* node) {

		len++;

		if (root == NULL) {
			root = node;
			return root;
		}

		TreeNode<KeyType, ValueType>* current = root;
		TreeNode<KeyType, ValueType>* next = root;

		while (next != NULL) {
			current = next;
			if (node->getKey() >= current->getKey())
				next = current->getRight();
			else
				next = current->getLeft();
		}

		node->setUp(current);
		if (node->getKey() >= current->getKey())
			current->setRight(node);
		else
			current->setLeft(node);

		return node;
	}

	virtual TreeNode<KeyType, ValueType>* push(KeyType key, ValueType value) {
		return push(new TreeNode<KeyType, ValueType>(key, value));
	}

	virtual TreeNode<KeyType, ValueType>* remove(TreeNode<KeyType, ValueType>* node) {

		if (node == NULL) return NULL;

		if (node->getRight() == NULL && node->getLeft() == NULL) {
			len--;
			if (node == root) {
				root = NULL;
				return root;
			}
			if (node->getUp()->getRight() == node)
				node->getUp()->setRight(NULL);
			else
				node->getUp()->setLeft(NULL);
			return node;
		 }

		TreeNode<KeyType, ValueType>* next;

		if (node->getRight() != NULL && node->getLeft() != NULL)
			next = node->successor();
		else
			if (node->getRight() != NULL)
				next = node->getRight();
			else
				next = node->getLeft();

		node->setKey(next->getKey());
		node->setValue(next->getValue());
		return remove(next);
	}

	void inOrder(TreeNode<KeyType, ValueType>* node = NULL) const {
		if (node == NULL) node = root;

		if (node->getLeft() != NULL)
			inOrder(node->getLeft());
		cout << *node << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		if (node->getRight() != NULL)
			inOrder(node->getRight());
	}

	TreeNode<KeyType, ValueType>* Min(TreeNode<KeyType, ValueType>* node = NULL) const {
		if (node == NULL) node = root;
		TreeNode<KeyType, ValueType>* res = node;
		for (; res->getLeft() != NULL; res = res->getLeft());
		return res;
	}

	TreeNode<KeyType, ValueType>* Max(TreeNode<KeyType, ValueType>* node = NULL) const {
		if (node == NULL) node = root;
		TreeNode<KeyType, ValueType>* res = node;
		for (; res->getRight() != NULL; res = res->getRight());
		return res;
	}

};