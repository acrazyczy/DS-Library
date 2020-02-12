//
// Created by crazy_cloud on 2020/2/2.
//

#ifndef DSLIB_BINARYHEAP_H
#define DSLIB_BINARYHEAP_H

#include "PriorityQueue.h"
#include "Array.h"
#include <utility>

template <class valueType , class compare = std::less<valueType> >
class BinaryHeap : public PriorityQueue<valueType , compare>
{
private:
	Array<valueType> list;
public:
	BinaryHeap() = default;

	virtual bool empty() const override;
	virtual std::size_t size() const override;

	virtual const valueType &top() const override;
	virtual void push(const valueType &) override;
	virtual void pop() override;

	void join(BinaryHeap<valueType , compare> &);

	virtual ~BinaryHeap() = default;
};

template <class valueType , class compare>
bool BinaryHeap<valueType , compare>::empty() const {return list.empty();}

template <class valueType , class compare>
std::size_t BinaryHeap<valueType , compare>::size() const {return list.size();}

template <class valueType , class compare>
const valueType &BinaryHeap<valueType , compare>::top() const {return list.front();}

template <class valueType , class compare>
void BinaryHeap<valueType , compare>::push(const valueType &val)
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

template <class valueType , class compare>
void BinaryHeap<valueType , compare>::pop()
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

template <class valueType , class compare>
void BinaryHeap<valueType , compare>::join(BinaryHeap<valueType , compare> &rhs){for (;!rhs.empty();rhs.pop()) push(rhs.top());}

#endif //DSLIB_BINARYHEAP_H