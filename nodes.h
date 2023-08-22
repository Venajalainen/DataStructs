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
	PairNode<KeyType, ValueType>(KeyType key, ValueType value) : key(key), Node(value) {}
	KeyType getKey() { return this->key; }
	void setKey(KeyType key) { this->key = key; }
};

//------------------------------------------------------------------------------------------------------------------------------------------//

template<class ValueType>
class LNode : protected Node<ValueType> {
protected:
	LNode<ValueType>* neighbour;
public:

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