//
// Created by crazy_cloud on 2020/2/2.
//

#ifndef DSLIB_LEFTISTTREE_H
#define DSLIB_LEFTISTTREE_H

#include "PriorityQueue.h"
#include <utility>

template <class valueType , class compare = std::less<valueType> >
class LeftistTree : public PriorityQueue<valueType , compare>
{
private:
	struct Node
	{
		std::size_t tot , d;
		valueType val;
		Node *left , *right;
	}*root;

	Node *merge(Node * const & , Node * const &);
	Node *copy(const Node * const &);
	void clear(Node *&);
public:
	LeftistTree(Node *root_ = nullptr) : root(root_) {};
	LeftistTree(const LeftistTree<valueType , compare> &);
	LeftistTree<valueType , compare> &operator=(const LeftistTree<valueType , compare> &);

	virtual bool empty() const override;
	virtual std::size_t size() const override;

	virtual const valueType &top() const override;
	virtual void push(const valueType &) override;
	virtual void pop() override;

	void join(LeftistTree<valueType , compare> &);

	virtual ~LeftistTree();
};

template <class valueType , class compare>
LeftistTree<valueType , compare>::LeftistTree(const LeftistTree<valueType , compare> &rhs){root = copy(rhs.root);}

template <class valueType , class compare>
LeftistTree<valueType , compare> &LeftistTree<valueType , compare>::operator=(const LeftistTree<valueType , compare> &rhs)
{
	if (this == &rhs) return *this;
	clear(root) , root = copy(rhs.root);
	return *this;
}

template <class valueType , class compare>
bool LeftistTree<valueType , compare>::empty() const {return root == nullptr;}

template <class valueType , class compare>
std::size_t LeftistTree<valueType , compare>::size() const {return empty() ? 0 : root -> tot;}

template <class valueType , class compare>
const valueType &LeftistTree<valueType , compare>::top() const
{
	if (empty()) throw(OutOfBound());
	return root -> val;
}

template <class valueType , class compare>
void LeftistTree<valueType , compare>::push(const valueType &val)
{
	LeftistTree<valueType , compare> tmp(new Node);
	tmp.root -> tot = 1 , tmp.root -> d = 0 , tmp.root -> val = val , tmp.root -> left = tmp.root -> right = nullptr;
	join(tmp);
}

template <class valueType , class compare>
void LeftistTree<valueType , compare>::pop()
{
	if (empty()) throw(OutOfBound());
	LeftistTree<valueType , compare> lst(root -> left) , rst(root -> right);
	delete root , lst.join(rst) , root = lst.root , lst.root = nullptr;
}

template <class valueType , class compare>
void LeftistTree<valueType , compare>::join(LeftistTree<valueType , compare> &rhs){root = merge(root , rhs.root) , rhs.root = nullptr;}

template <class valueType , class compare>
LeftistTree<valueType , compare>::~LeftistTree(){clear(root);}

template <class valueType , class compare>
typename LeftistTree<valueType , compare>::Node *LeftistTree<valueType , compare>::merge(typename LeftistTree<valueType , compare>::Node * const &lhs , typename LeftistTree<valueType , compare>::Node * const &rhs)
{
	if (lhs == nullptr) return rhs;
	if (rhs == nullptr) return lhs;
	Node *rt;
	if (compare()(lhs -> val , rhs -> val)) rhs -> right = merge(lhs , rhs -> right) , rt = rhs;
	else lhs -> right = merge(rhs , lhs -> right) , rt = lhs;
	rt -> tot = (rt -> left == nullptr ? 0 : rt -> left -> tot) + (rt -> right == nullptr ? 0 : rt -> right -> tot) + 1;
	if ((int)(rt -> left == nullptr ? -1 : rt -> left -> d) < (int)(rt -> right == nullptr ? -1 : rt -> right -> d)) std::swap(rt -> left , rt -> right);
	rt -> d = (rt -> right == nullptr ? -1 : rt -> right -> d) + 1;
	return rt;
}

template <class valueType , class compare>
typename LeftistTree<valueType , compare>::Node *LeftistTree<valueType , compare>::copy(const typename LeftistTree<valueType , compare>::Node * const &rt)
{
	if (rt == nullptr) return nullptr;
	Node *ret = new Node;ret -> val = rt -> val , ret -> tot = rt -> tot , ret -> d = rt -> d;
	ret -> left = copy(rt -> left) , ret -> right = copy(rt -> right);
	return ret;
}

template <class valueType , class compare>
void LeftistTree<valueType , compare>::clear(LeftistTree<valueType , compare>::Node *&rt)
{
	if (rt == nullptr) return;
	clear(rt -> left) , clear(rt -> right) , delete rt , rt = nullptr;
}

#endif //DSLIB_LEFTISTTREE_H