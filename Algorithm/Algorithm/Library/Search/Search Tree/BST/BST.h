#pragma once

template <typename T>
struct Node
{
	Node();
	Node(T data);
	Node(T data, Node *left, Node *right);
	Node *_left;
	Node *_right;
	T _data;
};

template <typename T>
Node<T>::Node()
	:_left(nullptr), _right(nullptr)
{

}

template <typename T>
Node<T>::Node(T data)
	:_data(data), _left(nullptr), _right(nullptr)
{

}

template <typename T>
Node<T>::Node(T data, Node *left, Node *right)
	:_data(data), _left(left), _right(right)
{
}

template <typename T>
class BST
{
public:
	BST();
	BST(Node<T> *root);

	Node<T> * SearchNode(T target);
	bool Search(T target);				//Checking exist
	bool AddNode(T data);				//if add success true, fail false
	bool DeleteNode(T data);			//if delete success true, fail false

private:
	Node<T> *_root;

	bool CanSearch(T data, Node<T> *&node);
	Node<T> * ReturnNode(T data, Node<T> *node);
	bool ReturnFind(T data, Node<T> *node);
	bool IsReft(T data, Node<T> *node);
	bool IsRight(T data, Node<T> *node);
	bool CanInsert(T data, Node<T> *&node);
	void InsertNewNode(T data, Node<T> *node);
	bool HaveNoNode(Node<T> *node);
	bool HaveLeftNode(Node<T> *node);
	bool HaveRightNode(Node<T> *node);
	void ReplaceNode(Node<T> *&origianl, Node<T> *&replace);		//Replace Original to replace
	void HaveTwoNodeDelete(Node<T> *&node);							//Delete Function if node to delete has two nodes
	Node<T> * FindRightMinimum(Node<T> *node);
};

template <typename T>
BST<T>::BST()
{
	_root = new Node<T>();
}

template <typename T>
BST<T>::BST(Node<T> *root)
{
	_root = root;
}

template <typename T>
Node<T> * BST<T>::SearchNode(T target)
{
	Node<T> *node = _root;

	while (CanSearch(target, node));

	return ReturnNode(target, node);
}

template <typename T>
bool BST<T>::Search(T target)
{
	Node<T> *node = _root;

	while (CanSearch(target, node));

	return ReturnFind(target, node);
}

template <typename T>
bool BST<T>::AddNode(T data)
{
	Node<T> *node = _root;

	while (!CanInsert(data, node));

	if (data == node->_data)	return false;

	InsertNewNode(data, node);

	return true;
}

template <typename T>
bool BST<T>::DeleteNode(T data)
{
	Node<T> *node = SearchNode(data);

	if (node == nullptr)		return false;
	if (HaveNoNode(node))		delete node;
	else if (HaveLeftNode)		ReplaceNode(node, node->_left);
	else if (HaveRightNode)		ReplaceNode(node, node->_right);
	else						HaveTwoNodeDelete(node);

	return true;
}

template <typename T>
bool BST<T>::CanSearch(T data, Node<T> *&node)
{
	if (data == node->_data)	return false;
	if (data < node->_data)	node = node->_left;
	else	node = node->_right;

	return true;
}

template <typename T>
Node<T> * BST<T>::ReturnNode(T data, Node<T> *node)
{
	if (data == node->_data)	return node;
	return nullptr;
}

template <typename T>
bool BST<T>::ReturnFind(T data, Node<T> *node)
{
	if (data == node->_data)	return true;
	return false;
}

template <typename T>
bool BST<T>::IsReft(T data, Node<T> *node)
{
	if (data > node->_data)			return false;
	if (node->_left == nullptr)		return false;
	return true;
}

template <typename T>
bool BST<T>::IsRight(T data, Node<T> *node)
{
	if (data < node->_data)			return false;
	if (node->_right == nullptr)	return false;
	return true;
}

template <typename T>
bool BST<T>::CanInsert(T data, Node<T> *&node)
{
	if (data == node->_data)		return true;
	if (IsReft(data, node))			node = node->_left;
	else if (IsRight(data, node))	node = node->_right;
	else							return true;

	return false;
}

template <typename T>
void BST<T>::InsertNewNode(T data, Node<T> *node)
{
	Node<T> *new_node = new Node<T>(data, nullptr, nullptr);

	if (data < node->_data)	node->_left = new_node;
	else node->_right = new_node;
}

template <typename T>
bool BST<T>::HaveNoNode(Node<T> *node)
{
	if (node->_right != nullptr) return false;
	if (node->_left != nullptr) return false;
	return true;
}

template <typename T>
bool BST<T>::HaveLeftNode(Node<T> *node)
{
	if (node->_right != nullptr) return false;
	if (node->_left == nullptr) return false;
	return true;
}

template <typename T>
bool BST<T>::HaveRightNode(Node<T> *node)
{
	if (node->_left != nullptr) return false;
	if (node->_right == nullptr) return false;
	return true;
}

template <typename T>
void BST<T>::ReplaceNode(Node<T> *&original, Node<T> *&replace)
{
	Node<T> *temp = replace;
	delete original;
	original = replace;
}

template <typename T>
void BST<T>::HaveTwoNodeDelete(Node<T> *&node)
{
	Node<T> *right_minimum = FindRightMinimum(node);

	node->_data = right_minimum->_data;

	if (right_minimum->_right == nullptr)	delete right_minimum;
	else									ReplaceNode(right_minimum, right_minimum->_right);
}

template <typename T>
Node<T> * BST<T>::FindRightMinimum(Node<T> *node)
{
	node = node->_right;
	while (node->_left != nullptr)	node = node->_left;
	return node;
}