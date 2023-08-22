#include <nodes.h>

using namespace std;

template<class ValueType>
class LinkedList {
private:
	LNode<ValueType>* root;
	int capacity;
	int len;
public:

	LinkedList<ValueType>() : root(NULL), capacity(1000), len(0) {}
	LinkedList<ValueType>(LNode<ValueType>* root) : capacity(1000), len(1) { this->root = root; }
	LinkedList<ValueType>(int len) : root(NULL), capacity(1000), len(len) { this->root = root; }

	~LinkedList() {
		LNode<ValueType>* to_del = this->root;
		for (LNode<ValueType>* next = to_del->getNeighbour(); next != NULL; next = next->getNeighbour()) {
			delete to_del;
			to_del = next;
		}
		delete to_del;
		cout << endl << "Destructor has worked" << endl;
	}

	int getCapacity() { return capacity; }
	int getLength() { return len; }
	LNode<ValueType>* getRoot() { return root; }

	LNode<ValueType>* pop() = 0;
	LNode<ValueType>* remove(int index) = 0;
	LNode<ValueType>* push(LNode<ValueType>* lnode) = 0;

	LNode<ValueType>* operator[](int index) = 0;
};

template<class ValueType>
class RightLinkedList : protected LinkedList<ValueType> {
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
		LNode<ValueType>* res = this->operator[](this->getLength() - 2);
		if (this->getLength() == 0) LinkedList<ValueType>::root = NULL;
		return res;
	}

};

template<class ValueType>
class LeftLinkedList : protected LinkedList<ValueType> {
public:

	LeftLinkedList<ValueType>() : LinkedList<ValueType>() {}
	LeftLinkedList<ValueType>(LNode<ValueType>* root) : LinkedList<ValueType>(root) {}
	LeftLinkedList<ValueType>(int len) : LinkedList<ValueType>(len) {}

	LNode<ValueType>* operator[](int index) {
		if (index < 0 || index >= this->getLength()) return NULL;
		LNode<ValueType>* res = this->getRoot();
		for (int n = this->getLength(); n > index; index--, res = res->getNeighbour());
		return res;
	}

	LNode<ValueType>* push(LNode<ValueType>* lnode) {
		if (this->getLength() + 1 > this->getCapacity()) return NULL;
		LinkedList<ValueType>::len++;
		lnode->setNeighbour(this->getRoot());
		LinkedList<ValueType>::root = lnode;
		return lnode;
	}

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
		LNode<ValueType>* res = this->getRoot();
		LinkedList<ValueType>::root = res->getNeighbour();
		return res;
	}

};