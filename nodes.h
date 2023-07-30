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

	//virtual Node<KeyType, ValueType>* successor() = 0;
	//virtual Node<KeyType, ValueType>* predecessor() = 0;
};

template<class KeyType, class ValueType>
class Node : protected Node<ValueType>{
protected:
	KeyType key;
public:
	Node<KeyType, ValueType>(KeyType key, ValueType value) : key(key), value(value) {}
	KeyType getKey() { return this->key; }
	void setKey(KeyType key) { this->key = key; }
};

//------------------------------------------------------------------------------------------------------------------------------------------//

template<class ValueType>
class LNode : protected Node<class ValueType> {
protected:
	LNode<ValueType>* neighbour;
public:

	LNode<ValueType>* getNeighbour() { return neighbour; }
	void setNeighbour(LNode<ValueType>* neighbour) { this->neighbour = neighbour; }

};


template<class KeyType, class ValueType>
class LNode : protected Node<class KeyType, class ValueType> {
protected:
	LNode<KeyType, ValueType>* neighbour;
public:

	LNode<KeyType, ValueType>* getNeighbour() { return neighbour; }
	void setRight(LNode<KeyType, ValueType>* neighbour) { this->neighbour = neighbour; }

};

//------------------------------------------------------------------------------------------------------------------------------------------//

template<class KeyType, class ValueType>
class TreeNode : protected Node<KeyType, ValueType> {
private:
	KeyType key;
	ValueType value;
	TreeNode<KeyType, ValueType>* left;
	TreeNode<KeyType, ValueType>* right;
	TreeNode<KeyType, ValueType>* up;
public:

	TreeNode<KeyType, ValueType>(KeyType key, ValueType value) : Node<KeyType, ValueType>(key, value), left(NULL), right(NULL), left(NULL) {}
	TreeNode<KeyType, ValueType>(KeyType key, ValueType value) : Node<KeyType, ValueType>(key, value), left(NULL), right(NULL), left(NULL) {}

	TreeNode<KeyType, ValueType>* getLeft() { return this->left; }
	TreeNode<KeyType, ValueType>* getRight() { return this->right }
	TreeNode<KeyType, ValueType>* getUp() { return this->up; }

	void setLeft(TreeNode<KeyType, ValueType>* left) { this->left = left; }
	void setRight(TreeNode<KeyType, ValueType>* right) { this->right = right; }
	void setUp(TreeNode<KeyType, T2ValueType* up) { this->up = up; }
	/*
	TreeNode<KeyType, ValueType>* successor() {
		TreeNode<KeyType, ValueType>* res = this->right;
		if (res != NULL) {
			for (; res->left != NULL; res = res->left);
			return res
		}
		if (this->up == NULL) return NULL;
		if (res->up->left == res) return this->up;
	}
	TreeNode<KeyType, ValueType>* predecessor() {
		TreeNode<KeyType, ValueType>* res = this->left;
		if (res != NULL) {
			for (; res->right != NULL; res = res->right);
			return res
		}
		if (this->up == NULL) return NULL;
		if (res->up->right == res) return this->up;
	}
	*/
};