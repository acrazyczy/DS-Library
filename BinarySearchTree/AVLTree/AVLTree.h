//
// Created by crazy_cloud on 2020/2/8.
//

#ifndef DSLIB_AVLTREE_H
#define DSLIB_AVLTREE_H

#include "Exception.h"
#include "Iterator.h"
#include <functional>
#include <cstdlib>

template <class keyType , class valueType , class compare = std::less<keyType> >
class AVLTree
{
private:
	struct Node
	{
		keyType key;
		valueType value;
		std::size_t height;
		Node *son[2] , *parent;

		Node() : key() , value() , height(0) , son{nullptr , nullptr} , parent(nullptr) {}
	}*root , *leftmost;

	std::size_t tot;

	int height(const Node * const &) const;
	void get_leftmost();
	void update(Node * const &);
	Node *rotate(Node * , const bool &);
	void maintain(Node *&);

	Node *find(const Node * const & , const keyType &) const;
	Node *insert(Node *& , const keyType & , const valueType &);
	void erase(Node *& , const keyType &);
	Node *copy(const Node * const &);
	void clear(Node *&);
public:
	class iterator
	{
		friend class AVLTree<keyType , valueType , compare>;
	private:
		Node *ptr;
	public:
		typedef valueType _valueType;
		typedef Node * _ptrType;

		explicit iterator(Node *ptr_ = nullptr) : ptr(ptr_) {}

		valueType &operator*() const;
		bool operator==(const iterator &) const;
		bool operator!=(const iterator &) const;

		iterator &operator++();
		iterator operator++(int);
		iterator operator+(const int &) const;

		iterator &operator--();
		iterator operator--(int);
		iterator operator-(const int &) const;
	};

	typedef Const_Iterator<iterator> const_iterator;
	typedef Reverse_Iterator<iterator> reverse_iterator;
	typedef Const_Reverse_Iterator<iterator> const_reverse_iterator;

	AVLTree() : root(new Node) , leftmost(root) , tot(0) {}
	AVLTree(const AVLTree<keyType , valueType , compare> &);
	AVLTree<keyType , valueType , compare> &operator=(const AVLTree<keyType , valueType , compare> &);

	bool empty() const;
	std::size_t size() const;

	std::pair<iterator , bool> insert(const keyType & , const valueType &);
	bool erase(const keyType &);
	void erase(const const_iterator &);
	const_iterator find(const keyType &) const;
	iterator find(const keyType &);
	void clear();

	const_iterator cbegin() const;
	iterator begin();
	const_reverse_iterator crbegin() const;
	reverse_iterator rbegin();
	const_iterator cend() const;
	iterator end();
	const_reverse_iterator crend() const;
	reverse_iterator rend();

	~AVLTree();
};

template <class keyType , class valueType , class compare>
valueType &AVLTree<keyType , valueType , compare>::iterator::operator*() const {return ptr -> value;}

template <class keyType , class valueType , class compare>
bool AVLTree<keyType , valueType , compare>::iterator::operator==(const iterator &it) const {return ptr == it.ptr;}

template <class keyType , class valueType , class compare>
bool AVLTree<keyType , valueType , compare>::iterator::operator!=(const iterator &it) const {return ptr != it.ptr;}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator &AVLTree<keyType , valueType , compare>::iterator::operator++()
{
	if (ptr -> son[1] == nullptr)
	{
		for (;ptr != nullptr && ptr -> parent -> son[1] == ptr;ptr = ptr -> parent);
		ptr = ptr -> parent;
	}
	else for (ptr = ptr -> son[1];ptr -> son[0] != nullptr;ptr = ptr -> son[0]);
	if (ptr == nullptr) throw(OutOfBound());
	return *this;
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator AVLTree<keyType , valueType , compare>::iterator::operator++(int x)
{
	iterator tmp = *this;
	++ (*this);
	return tmp;
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator AVLTree<keyType , valueType , compare>::iterator::operator+(const int &x) const
{
	if (x < 0) return operator-(-x);
	iterator tmp = *this;
	for (int i = 0;i < x;++ i) tmp = ++ tmp;
	return tmp;
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator &AVLTree<keyType , valueType , compare>::iterator::operator--()
{
	if (ptr -> son[0] == nullptr)
	{
		for (;ptr != nullptr && ptr -> parent -> son[0] == ptr;ptr = ptr -> parent);
		ptr = ptr -> parent;
	}
	else for (ptr = ptr -> son[0];ptr -> son[1] != nullptr;ptr = ptr -> son[1]);
	if (ptr == nullptr) throw(OutOfBound());
	return *this;
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator AVLTree<keyType , valueType , compare>::iterator::operator--(int x)
{
	iterator tmp = *this;
	-- (*this);
	return tmp;
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator AVLTree<keyType , valueType , compare>::iterator::operator-(const int &x) const
{
	if (x < 0) return operator+(-x);
	iterator tmp = *this;
	for (int i = 0;i < x;++ i) tmp = -- tmp;
	return tmp;
}

template <class keyType , class valueType , class compare>
AVLTree<keyType , valueType , compare>::AVLTree(const AVLTree<keyType , valueType , compare> &rhs)
{
	root = copy(rhs.root) , tot = rhs.tot , get_leftmost();
}

template <class keyType , class valueType , class compare>
AVLTree<keyType , valueType , compare> &AVLTree<keyType , valueType , compare>::operator=(const AVLTree<keyType , valueType , compare> &rhs)
{
	if (this == &rhs) return *this;
	clear() , delete root , root = copy(rhs.root) , tot = rhs.tot , get_leftmost();
}

template <class keyType , class valueType , class compare>
bool AVLTree<keyType , valueType , compare>::empty() const {return !tot;}

template <class keyType , class valueType , class compare>
std::size_t AVLTree<keyType , valueType , compare>::size() const {return tot;}

template <class keyType , class valueType , class compare>
std::pair<typename AVLTree<keyType , valueType , compare>::iterator , bool> AVLTree<keyType , valueType , compare>::insert(const keyType &key , const valueType &value)
{
	Node *pos = find(root -> son[0] , key);
	std::pair<iterator , bool> ret = pos == root ? std::make_pair(iterator(insert(root -> son[0] , key , value)) , true) : std::make_pair(iterator(pos) , false);
	if (ret.second) root -> son[0] -> parent = root;
	return get_leftmost() , ret;
}

template <class keyType , class valueType , class compare>
bool AVLTree<keyType , valueType , compare>::erase(const keyType &key)
{
	Node *pos = find(root -> son[0] , key);
	if (pos == root) return 0;
	erase(root -> son[0] , key) , get_leftmost();
	return 1;
}

template <class keyType , class valueType , class compare>
void AVLTree<keyType , valueType , compare>::erase(const typename AVLTree<keyType , valueType , compare>::const_iterator &pos)
{
	erase(root -> son[0] , pos.ptr -> key) , get_leftmost();
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::const_iterator AVLTree<keyType , valueType , compare>::find(const keyType &key) const
{
	return const_iterator(find(root -> son[0] , key));
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator AVLTree<keyType , valueType , compare>::find(const keyType &key)
{
	return iterator(static_cast<const AVLTree<keyType , valueType , compare> &>(*this).find(key).ptr);
}

template <class keyType , class valueType , class compare>
void AVLTree<keyType , valueType , compare>::clear()
{
	clear(root -> son[0]) , tot = 0;
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::const_iterator AVLTree<keyType , valueType , compare>::cbegin() const {return const_iterator(leftmost);}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator AVLTree<keyType , valueType , compare>::begin(){return iterator(leftmost);}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::const_reverse_iterator AVLTree<keyType , valueType , compare>::crbegin() const {return const_reverse_iterator(root);}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::reverse_iterator AVLTree<keyType , valueType , compare>::rbegin(){return reverse_iterator(root);}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::const_iterator AVLTree<keyType , valueType , compare>::cend() const {return const_iterator(root);}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::iterator AVLTree<keyType , valueType , compare>::end(){return iterator(root);}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::const_reverse_iterator AVLTree<keyType , valueType , compare>::crend() const {return const_reverse_iterator(leftmost);}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::reverse_iterator AVLTree<keyType , valueType , compare>::rend(){return reverse_iterator(leftmost);}

template <class keyType , class valueType , class compare>
AVLTree<keyType , valueType , compare>::~AVLTree()
{
	clear() , delete root;
}

template <class keyType , class valueType , class compare>
int AVLTree<keyType , valueType , compare>::height(const typename AVLTree<keyType , valueType , compare>::Node * const &rt) const
{
	return rt == nullptr ? -1 : rt -> height;
}

template <class keyType , class valueType , class compare>
void AVLTree<keyType , valueType , compare>::get_leftmost()
{
	for (leftmost = root;leftmost -> son[0] != nullptr;leftmost = leftmost -> son[0]);
}

template <class keyType , class valueType , class compare>
void AVLTree<keyType , valueType , compare>::update(typename AVLTree<keyType , valueType , compare>::Node * const &rt)
{
	rt -> height = std::max(height(rt -> son[0]) , height(rt -> son[1])) + 1;
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::Node *AVLTree<keyType , valueType , compare>::rotate(typename AVLTree<keyType , valueType , compare>::Node *y , const bool &s)
{
	Node *x = y -> son[s];
	x -> parent = y -> parent;
	y -> son[s] = x -> son[s ^ 1];
	if (x -> son[s ^ 1] != nullptr) x -> son[s ^ 1] -> parent = y;
	x -> son[s ^ 1] = y , y -> parent = x;
	update(y) , update(x);
	return x;
}

template <class keyType , class valueType , class compare>
void AVLTree<keyType , valueType , compare>::maintain(typename AVLTree<keyType , valueType , compare>::Node *&rt)
{
	int delta = height(rt -> son[0]) - height(rt -> son[1]);
	if (delta == 2)
		if (height(rt -> son[0] -> son[0]) == height(rt -> son[1]) + 1) rt = rotate(rt , 0);
		else rt -> son[0] = rotate(rt -> son[0] , 1) , rt = rotate(rt , 0);
	else if (delta == -2)
		if (height(rt -> son[1] -> son[1]) == height(rt -> son[0]) + 1) rt = rotate(rt , 1);
		else rt -> son[1] = rotate(rt -> son[1] , 0) , rt = rotate(rt , 1);
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::Node *AVLTree<keyType , valueType , compare>::find(const typename AVLTree<keyType , valueType , compare>::Node * const &rt , const keyType &key) const
{
	if (rt == nullptr) return root;
	if (rt -> key == key) return const_cast<Node *>(rt);
	return find(rt -> son[compare()(rt -> key , key)] , key);
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::Node *AVLTree<keyType , valueType , compare>::insert(typename AVLTree<keyType , valueType , compare>::Node *&rt , const keyType &key , const valueType &value)
{
	if (rt == nullptr)
	{
		rt = new Node , rt -> key = key , rt -> value = value , ++ tot;
		return rt;
	}
	Node *ret = insert(rt -> son[compare()(rt -> key , key)] , key , value);
	rt -> son[compare()(rt -> key , key)] -> parent = rt , update(rt) , maintain(rt);
	return ret;
}

template <class keyType , class valueType , class compare>
void AVLTree<keyType , valueType , compare>::erase(typename AVLTree<keyType , valueType , compare>::Node *&rt , const keyType &key)
{
	keyType _key = rt -> key , aim_key = key;
	valueType _value = rt -> value;
	if (rt -> key == key)
		if (rt -> son[0] == nullptr || rt -> son[1] == nullptr)
		{
			Node *rt_ = rt;
			rt = rt -> son[0] == nullptr ? rt -> son[1] : rt -> son[0] , delete rt_ , -- tot;
			return;
		}
		else
		{
			Node *rp = rt -> son[1];
			for (;rp -> son[0] != nullptr;rp = rp -> son[0]);
			aim_key = _key = rp -> key , _value = rp -> value;
		}
	erase(rt -> son[compare()(rt -> key , aim_key)] , aim_key);
	if (rt -> son[compare()(rt -> key , aim_key)] != nullptr) rt -> son[compare()(rt -> key , aim_key)] -> parent = rt;
	rt -> key = _key , rt -> value = _value;
	update(rt) , maintain(rt);
}

template <class keyType , class valueType , class compare>
typename AVLTree<keyType , valueType , compare>::Node *AVLTree<keyType , valueType , compare>::copy(const typename AVLTree<keyType , valueType , compare>::Node * const &rt)
{
	if (rt == nullptr) return nullptr;
	Node *node = new Node;
	node -> key = rt -> key , node -> value = rt -> value , node -> height = rt -> height;
	for (std::size_t t = 0;t < 2;++ t)
	{
		node -> son[t] = copy(rt -> son[t]);
		if (node -> son[t] != nullptr) node -> son[t] -> parent = node;
	}
	return node;
}

template <class keyType , class valueType , class compare>
void AVLTree<keyType , valueType , compare>::clear(typename AVLTree<keyType , valueType , compare>::Node *&rt)
{
	if (rt == nullptr) return;
	clear(rt -> son[0]) , clear(rt -> son[1]) , delete rt , rt = nullptr;
}

#endif //DSLIB_AVLTREE_H