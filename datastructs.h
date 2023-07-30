#include <nodes.h>

using namespace std;

/*template<class KeyType, class ValueType>
class Tree {
private:
	TreeNode<KeyType, ValueType>* root;
	int size;
public:
	int getSize() { return size; }
	bool push(KeyType key, ValueTpye value) {
		Node<KeyType, ValueType>* current = this->root;
		while (current != NULL)
			if (current->key < key)
				current = current->left;
			else
				current = current->right;

	}
};
*/
template<class ValueType>
class RightLinkedList {
private:
	LNode<ValueType>* root;
	int capacity;
	int len;
public:

	RightLinkedList<ValueType>() : root(NULL), capacity(1000), len(0) {}
	RightLinkedList<ValueType>(LNode<ValueType>* root) : capacity(1000), len(1) { this->root = root; }
	RightLinkedList<ValueType>(int capacity) : root(NULL), capacity(capacity), len(0) { this->root = root; }

	bool setCapacity(int capacity) {
		this->capacity = capcity;
		return true;
	}

	int getCapacity() { return capacity; }
	int getLength() { return len; }
	LNode<ValueType>* getRoot() { return root; }

	LNode<ValueType>* operator[](int index) {
		if (index < 0 || index >= len) return NULL;
		LNode<ValueType>* res = root;
		for (; index > 0; index--, res = res->getNeighbour());
		return res;
	}

	LNode<ValueType>* push(LNode<ValueType>* lnode) {
		if (len + 1 > capacity) return NULL;
		len++;
		if (root == NULL) { root = lnode; return lnode; }
		LNode<ValueType>* last = this->operator[](len - 2);
		last->setNeighbour(lnode);
		return lnode;
	}

};