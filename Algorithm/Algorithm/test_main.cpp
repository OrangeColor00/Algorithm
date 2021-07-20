#include "Library/Search/Search Tree/BST/BST.h"
#include "Library/Search/Search Tree/Traversal/Traversal.h"
#include <iostream>
#include <list>
#include <algorithm>

int main()
{
	
	Node<int> *left = new Node<int>(30);
	Node<int> *right = new Node<int>(100);
	Node<int> *root = new Node<int>(90, left, right);

	BST<int> *bst = new BST<int>(root);
	std::list<int> a;
	a.resize(10);

	bst->AddNode(10);
	bst->AddNode(20);
	bst->AddNode(60);
	bst->AddNode(70);
	bst->AddNode(40);
	bst->AddNode(50);
	bst->AddNode(45);
	
	bst->SearchNode(0);

	bst->DeleteNode(50);

	auto iter = a.begin();
//	bst->GetRoot()->_right = nullptr;
	if (bst->GetRoot()->_right == nullptr)
		int abc = 150;

	PreorderTree(iter, a.end(), bst->GetRoot());

	std::for_each(a.begin(), a.end(), [&](auto &i) {std::cout << i << std::endl; });
	return 0;
}