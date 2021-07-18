#pragma once


template<class ForwardIterator, class Type>
bool SequentialSearch(
	ForwardIterator first,
	ForwardIterator last,
	const Type& value)
{
	for (auto i = first; i != last; ++i)
		if (*i == value)	return true;
	return false;
}

template<class ForwardIterator, class Type>
ForwardIterator GetSequentialSearch(
	ForwardIterator first,
	ForwardIterator last,
	const Type& value)
{
	for (auto i = first; i != last; ++i)
		if (*i == value)	return i;
	return last;
}