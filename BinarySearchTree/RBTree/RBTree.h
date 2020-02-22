//
// Created by crazy_cloud on 2020/2/20.
//

#ifndef DSLIB_RBTREE_H
#define DSLIB_RBTREE_H

#include "Exception.h"
#include "Iterator.h"
#include <functional>
#include <cstdlib>

template <class keyType , class valueType , class compare = std::less<keyType> >
class RBTree
{
	enum colorType {RED , BLACK};
private:
	struct Node
	{
		keyType key;
		valueType value;
		colorType color;
		Node *son[2] , *parent;

		Node() : key() , value() , colorType(BLACK) , son{nullptr , nullptr} , parent(nullptr) {}
	}*root , *leftmost;

	std::size_t tot;
	compare cmp;

	Node *get_leftmost(const Node *&);

	bool side(const Node * const &) const;
	colorType color(const Node * const &) cosnt;

	Node *rotate(Node * , const bool &);
	void fix_insert(Node *);
	void fix_erase(Node *);

	Node *find(const keyType &) const;
	Node *insert(const keyType & , const valueType &);
	void erase(Node * const &);
	Node *copy(const Node * const &);
	void clear(Node *&);
public:
	class iterator
	{
		friend class RBTree<keyType , valueType , compare>;
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

	RBTree() : root(new Node) , leftmost(root) , tot(0) , cmp() {}
	RBTree(const RBTree<keyType , valueType , compare> &);
	RBTree<keyType , valueType , compare> &operator=(const RBTree<keyType , valueType , compare> &);

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

	~RBTree();
};

template <class keyType , class valueType , class compare>
RBTree<keyType , valueType , compare>::RBTree(const RBTree<keyType , valueType , compare> &rhs)
{
	root = copy(rhs.root) , tot = rhs.tot , leftmost = get_leftmost(root);
}

template <class keyType , class valueType , class compare>
RBTree<keyType , valueType , compare> &RBTree<keyType , valueType , compare>::operator=(const RBTree<keyType , valueType , compare> &rhs)
{
	if (this == &rhs) return *this;
	clear() , delete root , root = copy(rhs.root) , tot = rhs.tot , leftmost = get_leftmost(root);
}

template <class keyType , class valueType , class compare>
bool RBTree<keyType , valueType , compare>::empty() const {return !tot;}

template <class keyType , class valueType , class compare>
std::size_t RBTree<keyType , valueType , compare>::size() const {return tot;}

template <class keyType , class valueType , class compare>
std::pair<typename RBTree<keyType , valueType , compare>::iterator , bool> RBTree<keyType , valueType , compare>::insert(const keyType &key , const valueType &value)
{
}

template <class keyType , class valueType , class compare>
bool RBTree<keyType , valueType , compare>::erase(const keyType &key)
{
}

template <class keyType , class valueType , class compare>
void RBTree<keyType , valueType , compare>::erase(const RBTree<keyType , valueType , compare>::const_iterator &it)
{
}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::const_iterator RBTree<keyType , valueType , compare>::find(const keyType &key) const
{
}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::iterator RBTree<keyType , valueType , compare>::find(const keyType &key)
{
}

template <class keyType , class valueType , class compare>
void RBTree<keyType , valueType , compare>::clear()
{
	clear(root -> son[0]) , tot = 0;
}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::const_iterator RBTree<keyType , valueType , compare>::cbegin() const {return const_iterator(leftmost);}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::iterator RBTree<keyType , valueType , compare>::begin(){return iterator(leftmost);}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::const_reverse_iterator RBTree<keyType , valueType , compare>::crbegin() const {return const_reverse_iterator(root);}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::reverse_iterator RBTree<keyType , valueType , compare>::rbegin(){return reverse_iterator(root);}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::const_iterator RBTree<keyType , valueType , compare>::cend() const {return const_iterator(root);}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::iterator RBTree<keyType , valueType , compare>::end(){return iterator(root);}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::const_reverse_iterator RBTree<keyType , valueType , compare>::crend() const {return const_reverse_iterator(leftmost);}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::reverse_iterator RBTree<keyType , valueType , compare>::rend(){return reverse_iterator(leftmost);}

template <class keyType , class valueType , class compare>
RBTree<keyType , valueType , compare>::~RBTree()
{
	clear() , delete root;
}

template <class keyType , class valueType , class compare>
bool RBTree<keyType , valueType , compare>::side(const typename RBTree<keyType , valueType , compare>::Node * const &x) const {return x == x -> parent -> son[1];}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::colorType *RBTree<keyType , valueType , compare>::color(const typename RBTree<keyType , valueType , compare>::Node * const &x) const {return x == nullptr ? BLACK : x -> color;};

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::Node *RBTree<keyType , valueType , compare>::rotate(typename RBTree<keyType , valueType , compare>::Node * , const bool &)
{
}

template <class keyType , class valueType , class compare>
void RBTree<keyType , valueType , compare>::fix_insert(typename RBTree<keyType , valueType , compare>::Node *x)
{
	while (color(x -> parent) == RED)
	{
		bool s = side(x -> parent);
		Node *y = x -> parent -> parent -> son[s ^ 1];
		if (color(y) == RED)
		{
			x -> parent -> color = y -> color = BLACK;
			y -> parent -> color = RED;
			x = y -> parent;
		}
		else
		{
			bool s_ = side(x);
			if (s ^ s_) rotate(x) , x = x -> son[s_ ^ 1];
			y = x -> parent -> parent , rotate(x -> parent);
			x -> parent -> color = BLACK , y -> color = RED;
		}
	}
	root -> son[0] -> color = BLACK;
}

template <class keyType , class valueType , class compare>
void RBTree<keyType , valueType , compare>::fix_erase(typename RBTree<keyType , valueType , compare>::Node *&)
{
}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::Node *RBTree<keyType , valueType , compare>::find(const keyType &key) const
{
	Node *node = root -> son[0];
	for (;node != nullptr && node -> keyType != key;node = node -> son[cmp(node -> key , key)]);
	return node == nullptr ? root : node;
}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::Node *RBTree<keyType , valueType , compare>::insert(const keyType &key , const valueType &value)
{
	Node *node = root -> son[0] , par = root;
	for (;node != nullptr;par = node , node = node -> son[cmp(node -> key , key)]);
	par -> son[cmp(node -> key , key)] = node = new Node , node -> parent = par;
	node -> key = key , node -> value = value , node -> color = RED;
	++ tot;
	if (leftmost == par) leftmost = node;
	fix_insert(node);
}

template <class keyType , class valueType , class compare>
void RBTree<keyType , valueType , compare>::erase(const Node *&node)
{
	colorType original_color = node -> color;
	Node *x;
	if (node -> son[0] == nullptr)
	{
		node -> parent -> son[side(node)] = x = node -> son[1];
		if (x != nullptr) x -> parent = node -> parent;
		delete node;
	}
	else if (node -> son[1] == nullptr)
	{
		node -> parent -> son[side(node)] = x = node -> son[0];
		if (x != nullptr) x -> parent = node -> parent;
		delete node;
	}
	else
	{
		Node *y = get_leftmost(node -> son[1]);
		original_color = y -> color;
		x = y -> son[1];
	}
	if (original_color == BLACK) fix_erase(x);
	-- tot;
}

template <class keyType , class valueType , class compare>
typename RBTree<keyType , valueType , compare>::Node *copy(const typename RBTree<keyType , valueType , compare>::Node * const &)
{
	if (rt == nullptr) return nullptr;
	Node *node = new Node;
	node -> key = rt -> key , node -> value = rt -> value , node -> color = rt -> color;
	for (std::size_t t = 0;t < 2;++ t)
	{
		node -> son[t] = copy(rt -> son[t]);
		if (node -> son[t] != nullptr) node -> son[t] -> parent = node;
	}
	return node;
}

template <class keyType , class valueType , class compare>
void RBTree<keyType , valueType , compare>::clear(typename RBTree<keyType , valueType , compare>::Node *&)
{
	if (rt == nullptr) return;
	clear(rt -> son[0]) , clear(rt -> son[1]) , delete rt , rt = nullptr;
}

#endif //DSLIB_RBTREE_H