//
// Created by crazy_cloud on 2020/2/2.
//

#ifndef DSLIB_PRIORITYQUEUE_H
#define DSLIB_PRIORITYQUEUE_H

#include <functional>
#include <cstdlib>

template <class elemType , class compare = std::less<elemType> >
class PriorityQueue
{
public:
	PriorityQueue() = default;

	virtual bool empty() const = 0;
	virtual std::size_t size() const = 0;

	virtual const elemType &top() const = 0;
	virtual void push(const elemType &) = 0;
	virtual void pop() = 0;

	virtual ~PriorityQueue() = default;
};

#endif //DSLIB_PRIORITYQUEUE_H