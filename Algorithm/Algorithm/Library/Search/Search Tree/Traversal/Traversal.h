#pragma once
#include "../Node/Node.h"
#include <iostream>

template<class ForwardIterator, class type>
void PreorderTree(
	ForwardIterator &iter,
	ForwardIterator last, 
	Node<type> *node)
{
	if (iter == last)	return;
	
	*iter = node->_data;
	if (node->_left != nullptr)
		PreorderTree(++iter, last, node->_left);
	if (node->_right != nullptr)
		PreorderTree(++iter, last, node->_right);
}