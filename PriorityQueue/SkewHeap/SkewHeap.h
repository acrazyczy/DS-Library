//
// Created by crazy_cloud on 2020/2/3.
//

#ifndef DSLIB_SKEWHEAP_H
#define DSLIB_SKEWHEAP_H

#include "PriorityQueue.h"
#include <utility>

template <class valueType , class compare = std::less<valueType> >
class SkewHeap : public PriorityQueue<valueType , compare>
{
private:
	struct Node
	{
		std::size_t tot;
		valueType val;
		Node *left , *right;
	}*root;

	Node *merge(Node * const & , Node * const &);
	Node *copy(const Node * const &);
	void clear(Node *&);
public:
	SkewHeap(Node *root_ = nullptr) : root(root_) {};
	SkewHeap(const SkewHeap<valueType , compare> &);
	SkewHeap<valueType , compare> &operator=(const SkewHeap<valueType , compare> &);

	virtual bool empty() const override;
	virtual std::size_t size() const override;

	virtual const valueType &top() const override;
	virtual void push(const valueType &) override;
	virtual void pop() override;

	void join(SkewHeap<valueType , compare> &);

	virtual ~SkewHeap();
};

template <class valueType , class compare>
SkewHeap<valueType , compare>::SkewHeap(const SkewHeap<valueType , compare> &rhs){root = copy(rhs.root);}

template <class valueType , class compare>
SkewHeap<valueType , compare> &SkewHeap<valueType , compare>::operator=(const SkewHeap<valueType , compare> &rhs)
{
	if (this == &rhs) return *this;
	clear(root) , root = copy(rhs.root);
	return *this;
}

template <class valueType , class compare>
bool SkewHeap<valueType , compare>::empty() const {return root == nullptr;}

template <class valueType , class compare>
std::size_t SkewHeap<valueType , compare>::size() const {return empty() ? 0 : root -> tot;}

template <class valueType , class compare>
const valueType &SkewHeap<valueType , compare>::top() const
{
	if (empty()) throw(OutOfBound());
	return root -> val;
}

template <class valueType , class compare>
void SkewHeap<valueType , compare>::push(const valueType &val)
{
	SkewHeap<valueType , compare> tmp(new Node);
	tmp.root -> tot = 1 , tmp.root -> val = val , tmp.root -> left = tmp.root -> right = nullptr;
	join(tmp);
}

template <class valueType , class compare>
void SkewHeap<valueType , compare>::pop()
{
	if (empty()) throw(OutOfBound());
	SkewHeap<valueType , compare> lst(root -> left) , rst(root -> right);
	delete root , lst.join(rst) , root = lst.root , lst.root = nullptr;
}

template <class valueType , class compare>
void SkewHeap<valueType , compare>::join(SkewHeap<valueType , compare> &rhs){root = merge(root , rhs.root) , rhs.root = nullptr;}

template <class valueType , class compare>
SkewHeap<valueType , compare>::~SkewHeap(){clear(root);}

template <class valueType , class compare>
typename SkewHeap<valueType , compare>::Node *SkewHeap<valueType , compare>::merge(typename SkewHeap<valueType , compare>::Node * const &lhs , typename SkewHeap<valueType , compare>::Node * const &rhs)
{
	if (lhs == nullptr) return rhs;
	if (rhs == nullptr) return lhs;
	Node *rt;
	if (compare()(lhs -> val , rhs -> val)) rhs -> right = merge(lhs , rhs -> right) , rt = rhs;
	else lhs -> right = merge(rhs , lhs -> right) , rt = lhs;
	rt -> tot = (rt -> left == nullptr ? 0 : rt -> left -> tot) + (rt -> right == nullptr ? 0 : rt -> right -> tot) + 1;
	std::swap(rt -> left , rt -> right);
	return rt;
}

template <class valueType , class compare>
typename SkewHeap<valueType , compare>::Node *SkewHeap<valueType , compare>::copy(const typename SkewHeap<valueType , compare>::Node * const &rt)
{
	if (rt == nullptr) return nullptr;
	Node *ret = new Node;ret -> val = rt -> val , ret -> tot = rt -> tot;
	ret -> left = copy(rt -> left) , ret -> right = copy(rt -> right);
	return ret;
}

template <class valueType , class compare>
void SkewHeap<valueType , compare>::clear(SkewHeap<valueType , compare>::Node *&rt)
{
	if (rt == nullptr) return;
	clear(rt -> left) , clear(rt -> right) , delete rt , rt = nullptr;
}

#endif //DSLIB_SKEWHEAP_H
