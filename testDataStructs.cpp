// testDataStructs.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

template<class T1, class T2>
class Node{
protected:
	T1 key;
	T2 value;
public:

	Node<T1, T2>(T1 key, T2 value) : key(key), value(value) {}

	T1 getKey() { return this->key; }
	T2 getValue() { return this->value; }

	void setKey(T1 key) { this->key = key; }
	void setValue(T2 value) { this->value = value; }

	virtual Node<T1, T2>* successor() = 0
	virtual Node<T1, T2>* predecessor() = 0;
};

template<class T1, class T2>
class TreeNode : protected Node<T1,T2>{
private:
	T1 key;
	T2 value;
	TreeNode<T1, T2>* left;
	TreeNode<T1, T2>* right;
	TreeNode<T1, T2>* up;
public:

	TreeNode<T1, T2>(T1 key, T2 value) : Node<T1, T2>(key, value), left(NULL), right(NULL), left(NULL) {}
	TreeNode<T1, T2>(T1 key, T2 value) : Node<T1, T2>(key, value), left(NULL), right(NULL), left(NULL) {}     

	TreeNode<T1, T2>* getLeft() { return this->left; }
	TreeNode<T1, T2>* getRight() { return this->right }
	TreeNode<T1, T2>* getUp() { return this->up; }

	void setLeft(TreeNode<T1, T2>* left) { this->left = left; }
	void setRight(TreeNode<T1, T2>* right) { this->right = right; }
	void setUp(TreeNode<T1, T2>* up) { this->up = up; }

	TreeNode<T1, T2>* successor() {
		TreeNode<T1, T2>* res = this->right;
		if (res != NULL) {
			for (; res->left != NULL; res = res->left);
			return res
		}
		if (this->up == NULL) return NULL;
		if (res->up->left == res) return this->up;
	}
	TreeNode<T1, T2>* predecessor() {
		TreeNode<T1, T2>* res = this->left;
		if (res != NULL) {
			for (; res->right != NULL; res = res->right);  
			return res
		}
		if (this->up == NULL) return NULL;
		if (res->up->right == res) return this->up;
	}
};


template<class KeyType, class ValueType>
class Tree{
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

int main()
{
    std::cout << "Hello World!\n";
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
