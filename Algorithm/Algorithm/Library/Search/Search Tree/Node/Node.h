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