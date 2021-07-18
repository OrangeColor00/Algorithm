#include "Library/Search/Search Tree/BST/BST.h"
#include <iostream>
#include <vector>

int main()
{
	Node<int> *root = new Node<int>();
	Node<int> *left = new Node<int>();
	Node<int> *right = new Node<int>();

	root->_data = 7;
	left->_data = 5;
	right->_data = 9;

	root->_left = left;
	root->_right = right;

	BST<int> *bst = new BST<int>(root);
	std::cout<<bst->SearchNode(9)->_data;
	return 0;
}