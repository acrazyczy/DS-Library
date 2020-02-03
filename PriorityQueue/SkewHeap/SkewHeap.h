//
// Created by crazy_cloud on 2020/2/3.
//

#ifndef DSLIB_SKEWHEAP_H
#define DSLIB_SKEWHEAP_H

#include "PriorityQueue.h"
#include <utility>

template <class elemType , class compare = std::less<elemType> >
class SkewHeap : public PriorityQueue<elemType , compare>
{
private:
	struct Node
	{
		std::size_t tot;
		elemType val;
		Node *left , *right;
	}*root;

	Node *merge(Node * const & , Node * const &);
	Node *copy(const Node * const &);
	void clear(Node *&);
public:
	SkewHeap(Node *root_ = nullptr) : root(root_) {};
	SkewHeap(const SkewHeap<elemType , compare> &);
	SkewHeap<elemType , compare> &operator=(const SkewHeap<elemType , compare> &);

	virtual bool empty() const override;
	virtual std::size_t size() const override;

	virtual const elemType &top() const override;
	virtual void push(const elemType &) override;
	virtual void pop() override;

	void join(SkewHeap<elemType , compare> &);

	virtual ~SkewHeap();
};

template <class elemType , class compare>
SkewHeap<elemType , compare>::SkewHeap(const SkewHeap<elemType , compare> &rhs){root = copy(rhs.root);}

template <class elemType , class compare>
SkewHeap<elemType , compare> &SkewHeap<elemType , compare>::operator=(const SkewHeap<elemType , compare> &rhs)
{
	if (this == &rhs) return *this;
	clear(root) , root = copy(rhs.root);
	return *this;
}

template <class elemType , class compare>
bool SkewHeap<elemType , compare>::empty() const {return root == nullptr;}

template <class elemType , class compare>
std::size_t SkewHeap<elemType , compare>::size() const {return empty() ? 0 : root -> tot;}

template <class elemType , class compare>
const elemType &SkewHeap<elemType , compare>::top() const
{
	if (empty()) throw(OutOfBound());
	return root -> val;
}

template <class elemType , class compare>
void SkewHeap<elemType , compare>::push(const elemType &val)
{
	SkewHeap<elemType , compare> tmp(new Node);
	tmp.root -> tot = 1 , tmp.root -> val = val , tmp.root -> left = tmp.root -> right = nullptr;
	join(tmp);
}

template <class elemType , class compare>
void SkewHeap<elemType , compare>::pop()
{
	if (empty()) throw(OutOfBound());
	SkewHeap<elemType , compare> lst(root -> left) , rst(root -> right);
	delete root , lst.join(rst) , root = lst.root , lst.root = nullptr;
}

template <class elemType , class compare>
void SkewHeap<elemType , compare>::join(SkewHeap<elemType , compare> &rhs){root = merge(root , rhs.root) , rhs.root = nullptr;}

template <class elemType , class compare>
SkewHeap<elemType , compare>::~SkewHeap(){clear(root);}

template <class elemType , class compare>
typename SkewHeap<elemType , compare>::Node *SkewHeap<elemType , compare>::merge(typename SkewHeap<elemType , compare>::Node * const &lhs , typename SkewHeap<elemType , compare>::Node * const &rhs)
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

template <class elemType , class compare>
typename SkewHeap<elemType , compare>::Node *SkewHeap<elemType , compare>::copy(const typename SkewHeap<elemType , compare>::Node * const &rt)
{
	if (rt == nullptr) return nullptr;
	Node *ret = new Node;ret -> val = rt -> val , ret -> tot = rt -> tot;
	ret -> left = copy(rt -> left) , ret -> right = copy(rt -> right);
	return ret;
}

template <class elemType , class compare>
void SkewHeap<elemType , compare>::clear(SkewHeap<elemType , compare>::Node *&rt)
{
	if (rt == nullptr) return;
	clear(rt -> left) , clear(rt -> right) , delete rt , rt = nullptr;
}

#endif //DSLIB_SKEWHEAP_H
