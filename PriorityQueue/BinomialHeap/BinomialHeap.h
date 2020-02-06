//
// Created by crazy_cloud on 2020/2/4.
//

#ifndef DSLIB_BINOMIALHEAP_H
#define DSLIB_BINOMIALHEAP_H

#include "PriorityQueue.h"
#include "LinkedList.h"

template <class elemType , class compare = std::less<elemType> >
class BinomialHeap : public PriorityQueue<elemType , compare>
{
private:
	struct Node
	{
		elemType val;
		std::size_t depth;
		LinkedList<Node *> dec;
	};

	std::size_t tot;
	LinkedList<Node *> root;

	Node *merge(Node * const & , Node * const &);
	Node *copy(const Node * const &);
	void clear(Node *&);
	void clear();
public:
	BinomialHeap() : tot(0) {};
	BinomialHeap(Node *);
	BinomialHeap(const BinomialHeap &);
	BinomialHeap<elemType , compare> &operator=(const BinomialHeap<elemType , compare> &);

	virtual bool empty() const override;
	virtual std::size_t size() const override;

	virtual const elemType &top() const override;
	virtual void push(const elemType &) override;
	virtual void pop() override;

	void join(BinomialHeap<elemType , compare> &);

	virtual ~BinomialHeap();
};

template <class elemType , class compare>
BinomialHeap<elemType , compare>::BinomialHeap(Node *root_) : tot(1) {root.push_back(root_);}

template <class elemType , class compare>
BinomialHeap<elemType , compare>::BinomialHeap(const BinomialHeap<elemType , compare> &rhs)
{
	for (typename LinkedList<Node *>::const_iterator it = rhs.root.cbegin();it != rhs.root.cend();++ it) root.push_back(copy(*it));
	tot = rhs.tot;
}

template <class elemType , class compare>
BinomialHeap<elemType , compare> &BinomialHeap<elemType , compare>::operator=(const BinomialHeap<elemType , compare> &rhs)
{
	if (this == &rhs) return *this;
	clear();
	for (typename LinkedList<Node *>::const_iterator it = rhs.root.cbegin();it != rhs.root.cend();++ it) root.push_back(copy(*it));
	tot = rhs.tot;
	return *this;
}

template <class elemType , class compare>
bool BinomialHeap<elemType , compare>::empty() const {return !tot;}

template <class elemType , class compare>
std::size_t BinomialHeap<elemType , compare>::size() const {return tot;}

template <class elemType , class compare>
const elemType &BinomialHeap<elemType , compare>::top() const
{
	if (empty()) throw(OutOfBound());
	elemType ret = root.front() -> val;typename LinkedList<Node *>::const_iterator rt = root.cbegin();
	for (typename LinkedList<Node *>::const_iterator it = root.cbegin();it != root.cend();++ it)
		if (compare()(ret , (*it) -> val))
			ret = (*it) -> val , rt = it;
	return (*rt) -> val;
}

template <class elemType , class compare>
void BinomialHeap<elemType , compare>::push(const elemType &val)
{
	Node *node = new Node;node -> val = val , node -> depth = 0;
	BinomialHeap<elemType , compare> tmp(node);
	join(tmp);
}

template <class elemType , class compare>
void BinomialHeap<elemType , compare>::pop()
{
	if (empty()) throw(OutOfBound());
	typename LinkedList<Node *>::const_iterator rt = root.cend();
	for (typename LinkedList<Node *>::const_iterator it = root.cbegin();it != root.cend();++ it)
		if (rt == root.cend() || compare()((*rt) -> val , (*it) -> val)) rt = it;
	tot -= 1 << (*rt) -> depth;
	BinomialHeap<elemType , compare> tmp;tmp.tot = (1 << (*rt) -> depth) - 1;
	for (typename LinkedList<Node *>::iterator it = (*rt) -> dec.begin();it != (*rt) -> dec.end();++ it) tmp.root.push_back(*it);
	root.erase(rt) , join(tmp);
}

template <class elemType , class compare>
void BinomialHeap<elemType , compare>::join(BinomialHeap<elemType , compare> &rhs)
{
	LinkedList<Node *> root_;
	for (;!root.empty() || !rhs.root.empty();)
	{
		if (root.empty() && (root_.empty() || rhs.root.front() -> depth != root_.back() -> depth)) root_.merge(rhs.root);
		else if (rhs.root.empty() && (root_.empty() || root.front() -> depth != root_.back() -> depth)) root_.merge(root);
		if (root.empty() && rhs.root.empty()) continue;
		Node *tmp = nullptr;
		if (root.empty() || !rhs.root.empty() && rhs.root.front() -> depth < root.front() -> depth) tmp = rhs.root.front() , rhs.root.pop_front();
		else if (rhs.root.empty() || !root.empty() && root.front() -> depth < rhs.root.front() -> depth) tmp = root.front() , root.pop_front();
		else tmp = merge(root.front() , rhs.root.front()) , root.pop_front() , rhs.root.pop_front();
		if (!root_.empty() && root_.back() -> depth == tmp -> depth) root_.back() = merge(root_.back() , tmp);
		else root_.push_back(tmp);
	}
	root = root_ , tot += rhs.tot , rhs.tot = 0;
}

template <class elemType , class compare>
BinomialHeap<elemType , compare>::~BinomialHeap(){clear();}

template <class elemType , class compare>
typename BinomialHeap<elemType , compare>::Node *BinomialHeap<elemType , compare>::merge(typename BinomialHeap<elemType , compare>::Node * const &lhs , typename BinomialHeap<elemType , compare>::Node * const &rhs)
{
	if (compare()(lhs -> val , rhs -> val))
	{
		rhs -> dec.push_back(lhs) , ++ rhs -> depth;
		return rhs;
	}
	else
	{
		lhs -> dec.push_back(rhs) , ++ lhs -> depth;
		return lhs;
	}
}

template <class elemType , class compare>
typename BinomialHeap<elemType , compare>::Node *BinomialHeap<elemType , compare>::copy(const typename BinomialHeap<elemType , compare>::Node * const &rt)
{
	if (rt == nullptr) return nullptr;
	Node *ret = new Node;ret -> val = rt -> val , ret -> depth = rt -> depth;
	for (typename LinkedList<Node *>::const_iterator it = rt -> dec.cbegin();it != rt -> dec.cend();++ it) ret -> dec.push_back(copy(*it));
	return ret;
}

template <class elemType , class compare>
void BinomialHeap<elemType , compare>::clear(Node *&rt)
{
	for (typename LinkedList<Node *>::iterator it = rt -> dec.begin();it != rt -> dec.end();++ it) clear(*it);
	delete rt , rt = nullptr;
}

template <class elemType , class compare>
void BinomialHeap<elemType , compare>::clear()
{
	for (typename LinkedList<Node *>::iterator it = root.begin();it != root.end();++ it) clear(*it);
	root.resize(0) , tot = 0;
}

#endif //DSLIB_BINOMIALHEAP_H