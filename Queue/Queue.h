//
// Created by crazy_cloud on 2020/2/1.
//

#ifndef DSLIB_QUEUE_H
#define DSLIB_QUEUE_H

#include "LinkedList.h"

template <class valueType>
class Queue
{
private:
	LinkedList<valueType> list;
public:
	Queue() = default;

	bool empty() const;
	std::size_t size() const;

	const valueType &front() const;
	valueType &front();
	const valueType &back() const;
	valueType &back();

	void push(const valueType &);
	void pop();

	virtual ~Queue() = default;
};

template <class valueType>
bool Queue<valueType>::empty() const {return list.empty();}

template <class valueType>
std::size_t Queue<valueType>::size() const {return list.size();}

template <class valueType>
const valueType &Queue<valueType>::front() const {return list.front();}

template <class valueType>
valueType &Queue<valueType>::front(){return list.front();}

template <class valueType>
const valueType &Queue<valueType>::back() const {return list.back();}

template <class valueType>
valueType &Queue<valueType>::back(){return list.back();}

template <class valueType>
void Queue<valueType>::push(const valueType &val){list.push_back(val);}

template <class valueType>
void Queue<valueType>::pop(){list.pop_front();}

#endif //DSLIB_QUEUE_H