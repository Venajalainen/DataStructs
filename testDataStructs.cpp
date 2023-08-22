// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;
//------------------------------------------------------------------------------------------------------------------------------------------//

template<class ValueType>
class Node {
protected:
	ValueType value;
public:

	Node<ValueType>(ValueType value) : value(value) {}
	ValueType getValue() { return this->value; }
	void setValue(ValueType value) { this->value = value; }

};

template<class KeyType, class ValueType>
class PairNode : protected Node<ValueType> {
protected:
	KeyType key;
public:
	PairNode<KeyType, ValueType>(KeyType key, ValueType value) : key(key), Node<ValueType>(value) {}
	KeyType getKey() { return this->key; }
	void setKey(KeyType key) { this->key = key; }
};

//------------------------------------------------------------------------------------------------------------------------------------------//

template<class ValueType>
class LNode : protected Node<ValueType> {
protected:
	LNode<ValueType>* neighbour;
public:

	LNode<ValueType>(ValueType value) : Node<ValueType>(value), neighbour(NULL) {}
	LNode<ValueType>(ValueType value, Node<ValueType>* neighbour) : Node<ValueType>(value), neighbour(neighbour) {}

	LNode<ValueType>* getNeighbour() { return neighbour; }
	void setNeighbour(LNode<ValueType>* neighbour) { this->neighbour = neighbour; }

};

//------------------------------------------------------------------------------------------------------------------------------------------//

template<class KeyType, class ValueType>
class TreeNode : protected PairNode<KeyType, ValueType> {
private:
	KeyType key;
	ValueType value;
	TreeNode<KeyType, ValueType>* left;
	TreeNode<KeyType, ValueType>* right;
	TreeNode<KeyType, ValueType>* up;
public:

	TreeNode<KeyType, ValueType>(KeyType key, ValueType value) : PairNode<KeyType, ValueType>(key, value), left(NULL), right(NULL), left(NULL) {}

	TreeNode<KeyType, ValueType>* getLeft() { return this->left; }
	TreeNode<KeyType, ValueType>* getRight() { return this->right; }
	TreeNode<KeyType, ValueType>* getUp() { return this->up; }

	void setLeft(TreeNode<KeyType, ValueType>* left) { this->left = left; }
	void setRight(TreeNode<KeyType, ValueType>* right) { this->right = right; }
	void setUp(TreeNode<KeyType, ValueType>* up) { this->up = up; }

};

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

	~LinkedList() {
		LNode<ValueType>* to_del = this->root;
		if (to_del == NULL) return;
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

	virtual LNode<ValueType>* pop() = 0;
	virtual LNode<ValueType>* remove(int index) = 0;
	virtual LNode<ValueType>* push(LNode<ValueType>* lnode) = 0;

	virtual LNode<ValueType>* operator[](int index) = 0;
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

	LNode<ValueType>* push(ValueType value) {
		return this->push(new LNode<ValueType>(value));
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

int main()
{
	RightLinkedList<int> test;
	test.push(3);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
