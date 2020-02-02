//
// Created by crazy_cloud on 2020/2/2.
//

#ifndef DSLIB_BINARYHEAP_H
#define DSLIB_BINARYHEAP_H

#include "PriorityQueue.h"
#include "Array.h"
#include <utility>

template <class elemType , class compare = std::less<elemType> >
class BinaryHeap : public PriorityQueue<elemType , compare>
{
private:
	Array<elemType> list;
public:
	BinaryHeap() = default;

	virtual bool empty() const override;
	virtual std::size_t size() const override;

	virtual const elemType &top() const override;
	virtual void push(const elemType &) override;
	virtual void pop() override;

	void join(BinaryHeap<elemType> &);

	~BinaryHeap() = default;
};

template <class elemType , class compare>
bool BinaryHeap<elemType , compare>::empty() const {return list.empty();}

template <class elemType , class compare>
std::size_t BinaryHeap<elemType , compare>::size() const {return list.size();}

template <class elemType , class compare>
const elemType &BinaryHeap<elemType , compare>::top() const {return list.front();}

template <class elemType , class compare>
void BinaryHeap<elemType , compare>::push(const elemType &val)
{
	list.push_back(val);
	std::size_t son = size() - 1;
	for (std::size_t fa;son;son = fa)
	{
		fa = (son + 1 >> 1) - 1;
		if (compare()(list[son] , list[fa])) break;
		std::swap(list[son] , list[fa]);
	}
}

template <class elemType , class compare>
void BinaryHeap<elemType , compare>::pop()
{
	list.front() = list.back() , list.pop_back();
	std::size_t fa = 0 , tot = size();
	for (std::size_t son;fa + 1 << 1 <= tot;fa = son)
	{
		son = (fa + 1 << 1) - 1;
		if (son + 1 < tot && compare()(list[son] , list[son + 1])) ++ son;
		if (compare()(list[son] , list[fa])) break;
		std::swap(list[son] , list[fa]);
	}
}

template <class elemType , class compare>
void BinaryHeap<elemType , compare>::join(BinaryHeap<elemType> &rhs){for (;!rhs.empty();rhs.pop()) push(rhs.top());}

#endif //DSLIB_BINARYHEAP_H