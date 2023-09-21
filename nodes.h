#include <iostream>

using namespace std;
//------------------------------------------------------------------------------------------------------------------------------------------//

template<class ValueType>
class Node {
private:
	ValueType value;
public:

	Node(ValueType value) : value(value) {}
	Node() : value(NULL) {}

	ValueType getValue() const { return value; }
	void setValue(ValueType value) { this->value = value; }

};

template<class KeyType, class ValueType>
class PairNode : public Node<ValueType> {
private:
	KeyType key;
public:

	PairNode(KeyType key, ValueType value) : key(key), Node<ValueType>(value) {}
	PairNode(KeyType key) : key(key), Node<ValueType>() {}


	KeyType getKey() const { return this->key; }
	void setKey(KeyType key) { this->key = key; }
};

//------------------------------------------------------------------------------------------------------------------------------------------//

template<class ValueType>
class LNode : public Node<ValueType> {
private:
	LNode<ValueType>* neighbour;
public:

	LNode() : neighbour(NULL) {}
	LNode(ValueType value) : Node<ValueType>(value), neighbour(NULL) {}
	LNode(ValueType value, Node<ValueType>* neighbour) : Node<ValueType>(value), neighbour(neighbour) {}

	LNode<ValueType>* getNeighbour() const { return neighbour; }
	void setNeighbour(LNode<ValueType>* neighbour) { this->neighbour = neighbour; }

};

template<class T>
ostream& operator<<(ostream& fout, LNode<T>& node) {
	fout << "| " << "Value: " << node.getValue() << " |" << "-------->" << "| " << "Neighbour: " << node.getNeighbour() << " |";
	return fout;
}

template<class ValueType>
class WNode : public Node<ValueType> {
private:
	WNode<ValueType>* right;
	WNode<ValueType>* left;
public:

	WNode() : right(NULL), left(NULL) {}
	WNode(ValueType value) : Node<ValueType>(value), right(NULL), left(NULL) {}
	WNode(ValueType value, WNode<ValueType>* left, WNode<ValueType>* right) : Node<ValueType>(value), left(left), right(right) {}

	WNode<ValueType>* getRight() const { return right; }
	WNode<ValueType>* getLeft() const { return left; }

	void setRight(WNode<ValueType>* right) { this->right = right; }
	void setLeft(WNode<ValueType>* left) { this->left = left; }

};

template<class T>
ostream& operator<<(ostream& fout, WNode<T>& node) {
	fout << "| " << "Value: " << node.getValue() << " |" << "-------->" << "| " << "LEFT: " << node.getLeft() << " | Right: " << node.getLeft() << " |";
	return fout;
}

//------------------------------------------------------------------------------------------------------------------------------------------//

template<class KeyType, class ValueType>
class TreeNode : public PairNode<KeyType, ValueType> {
private:
	TreeNode<KeyType, ValueType>* left;
	TreeNode<KeyType, ValueType>* right;
	TreeNode<KeyType, ValueType>* up;
public:

	TreeNode(KeyType key, ValueType value) : PairNode<KeyType, ValueType>(key, value), left(NULL), right(NULL), up(NULL) {}
	TreeNode() : PairNode<KeyType, ValueType>(), left(NULL), right(NULL), up(NULL) {}

	TreeNode<KeyType, ValueType>* getLeft() const { return this->left; }
	TreeNode<KeyType, ValueType>* getRight() const { return this->right; }
	TreeNode<KeyType, ValueType>* getUp() const { return this->up; }

	void setLeft(TreeNode<KeyType, ValueType>* left) { this->left = left; }
	void setRight(TreeNode<KeyType, ValueType>* right) { this->right = right; }
	void setUp(TreeNode<KeyType, ValueType>* up) { this->up = up; }

	virtual TreeNode<KeyType, ValueType>* successor() {


		if (right != NULL) {
			TreeNode<KeyType, ValueType>* ptr = right;
			for (; ptr->getLeft() != NULL; ptr = ptr->getLeft());
			return ptr;
		}

		TreeNode<KeyType, ValueType>* res = up;

		for (TreeNode<KeyType, ValueType>* current = this; res != NULL; current = current->getUp(), res = res->getUp())
			if (res->getLeft() == current) return res;

		return this;
	}

	virtual TreeNode<KeyType, ValueType>* predecessor() {
		if (left != NULL) {
			TreeNode<KeyType, ValueType>* ptr = left;
			for (; ptr->getRight() != NULL; ptr = ptr->getRight());
			return ptr;
		}

		TreeNode<KeyType, ValueType>* res = up;

		for (TreeNode<KeyType, ValueType>* current = this; res!= NULL; current = current->getUp(), res = res->getUp())
			if (res->getRight() == current) return res;

		return this; 
	}

};

template<class KeyType, class ValueType>
ostream& operator<<(ostream& fout, const TreeNode<KeyType, ValueType>& node) {
	fout << "Key: " << node.getKey() << " Value: " << node.getValue() << endl;
	fout << "Right: " << node.getRight() << " Left: " << node.getLeft() << " Up: " << node.getUp() << endl;
	return fout;
}
