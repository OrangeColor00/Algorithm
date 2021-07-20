#pragma once
#include "../Node/Node.h"

enum State
{
	LEFT,
	RIGHT,
	NULLPTR,
	CONTINUE
};

template <typename T>
class BST
{
public:
	BST();
	BST(Node<T> *root);

	Node<T> * SearchNode(T target);				//Search node and get node
	Node<T> ** SearchNodePtr(T target);			//Search node and get node pointer
	bool Search(T target);						//Checking exist
	bool AddNode(T data);						//if add success true, fail false
	bool DeleteNode(T data);					//if delete success true, fail false
	Node<T> * GetRoot();						//Get root node

private:
	Node<T> *_root;

	State GetNodeState(T data, Node<T> **node);					
	void DeleteNode(Node<T> **node);						//free node memory and fill nullptr
	void CopyNode(Node<T> *original, Node<T> *copy);		//deep copy node
	bool CanSearch(T data, Node<T> *&node);					//Search node and return can search
	State SearchPtr(T data, Node<T> **node);				//Search node and return node state
	Node<T> * ReturnNode(Node<T> *node);					//Get node
	Node<T> ** ReturnNodePtr(Node<T> *node, State state);	//Get node pointer
	bool ReturnIsSearch(Node<T> *node);						//is node searched
	bool IsLeft(T data, Node<T> *node);						//is data left node (for InsertNode)
	bool IsRight(T data, Node<T> *node);					//is data right node (for InserNode)
	bool CanInsert(T data, Node<T> *&node);					//can insert node
	void InsertNewNode(T data, Node<T> *node);				//insert new node 
	bool HaveNoNode(Node<T> *node);							//s node having no node
	bool HaveLeftNode(Node<T> *node);						//is node having only left node
	bool HaveRightNode(Node<T> *node);						//is node having only right node
	void ReplaceNode(Node<T> *origianl, Node<T> **replace);		//Replace original node to replace node
	void DeleteHaveTwoNode(Node<T> *&node);						//Delete node if node to delete has two nodes
	Node<T> ** FindRightMinimum(Node<T> *node);					//Find Smallest node on the right
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
Node<T> ** BST<T>::SearchNodePtr(T target)
{
	Node<T> *node = _root;
	State state = CONTINUE;

	while (state == CONTINUE)
		state = SearchPtr(target, &node);

	return ReturnNodePtr(node, state);
}

template <typename T>
Node<T> * BST<T>::SearchNode(T target)
{
	Node<T> *node = _root;

	while (CanSearch(target, node));

	return ReturnNode(node);
}

template <typename T>
bool BST<T>::Search(T target)
{
	Node<T> *node = _root;

	while (CanSearch(target, node));

	return ReturnIsSearch(node);
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
	Node<T> ** node = SearchNodePtr(data);

	if (node == nullptr)		return false;
	if (HaveNoNode(*node))		DeleteNode(node);
	else if (HaveLeftNode(*node))		ReplaceNode(*node, &(node[0]->_left));
	else if (HaveRightNode(*node))		ReplaceNode(*node, &(node[0]->_right));
	else								DeleteHaveTwoNode(*node);

	return true;
}

template <typename T>
Node<T> * BST<T>::GetRoot()
{
	return _root;
}

template <typename T>
State BST<T>::GetNodeState(T data, Node<T> ** node)
{
	if (*node == nullptr)	return NULLPTR;
	if (node[0]->_left != nullptr)
		if (data == node[0]->_left->_data)	return LEFT;
	if (node[0]->_right != nullptr)
		if (data == node[0]->_right->_data)	return RIGHT;
	return CONTINUE;
}

template <typename T>
void BST<T>::DeleteNode(Node<T> ** node)
{
	delete *node;
	*node = nullptr;
}

template <typename T>
void BST<T>::CopyNode(Node<T> *original, Node<T> *copy)
{
	original->_data = copy->_data;
	original->_left = copy->_left;
	original->_right = copy->_right;
}

template <typename T>
bool BST<T>::CanSearch(T data, Node<T> *&node)
{
	if (node == nullptr)		return false;
	if (data == node->_data)	return false;
	if (data < node->_data)	node = node->_left;
	else	node = node->_right;
	return true;
}

template <typename T>
State BST<T>::SearchPtr(T data, Node<T> **node)
{
	State state = GetNodeState(data, node);
	if (state != CONTINUE)		return state;
	if (data < node[0]->_data)	*node = node[0]->_left;
	else	*node = node[0]->_right;

	return CONTINUE;
}

template <typename T>
Node<T> ** BST<T>::ReturnNodePtr(Node<T> *node, State state)
{
	Node<T> **node_ptr = nullptr;
	if (state == NULLPTR) return nullptr;
	if (state == LEFT)	node_ptr = &(node->_left);
	else if (state == RIGHT)	node_ptr = &(node->_right);

	return node_ptr;
}

template <typename T>
Node<T> * BST<T>::ReturnNode(Node<T> *node)
{
	if (node == nullptr)		return nullptr;
	return node;
}

template <typename T>
bool BST<T>::ReturnIsSearch(Node<T> *node)
{
	if (node == nullptr)		return false;
	return true;
}

template <typename T>
bool BST<T>::IsLeft(T data, Node<T> *node)
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
	if (IsLeft(data, node))			node = node->_left;
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
void BST<T>::ReplaceNode(Node<T> *original, Node<T> **replace)
{
	CopyNode(original, *replace);
	DeleteNode(replace);
}

template <typename T>
void BST<T>::DeleteHaveTwoNode(Node<T> *&node)
{
	Node<T> **right_minimum = FindRightMinimum(node);

	node->_data = right_minimum[0]->_data;

	if (right_minimum[0]->_right == nullptr)	DeleteNode(right_minimum);
	else			ReplaceNode(*right_minimum, &(right_minimum[0]->_right));
}

template <typename T>
Node<T> ** BST<T>::FindRightMinimum(Node<T> *node)
{
	if (node->_right->_left == nullptr)	return &(node->_right);
	node = node->_right;
	while (node->_left->_left != nullptr) node = node->_left;
	return &(node->_left);
}