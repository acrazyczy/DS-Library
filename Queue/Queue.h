//
// Created by crazy_cloud on 2020/2/1.
//

#ifndef DSLIB_QUEUE_H
#define DSLIB_QUEUE_H

#include "LinkedList.h"

template <class elemType>
class Queue
{
private:
	LinkedList<elemType> list;
public:
	bool empty() const;
	std::size_t size() const;

	const elemType &front() const;
	elemType &front();
	const elemType &back() const;
	elemType &back();

	void push(const elemType &);
	void pop();
};

template <class elemType>
bool Queue<elemType>::empty() const {return list.empty();}

template <class elemType>
std::size_t Queue<elemType>::size() const {return list.size();}

template <class elemType>
const elemType &Queue<elemType>::front() const {return list.front();}

template <class elemType>
elemType &Queue<elemType>::front(){return list.front();}

template <class elemType>
const elemType &Queue<elemType>::back() const {return list.back();}

template <class elemType>
elemType &Queue<elemType>::back(){return list.back();}

template <class elemType>
void Queue<elemType>::push(const elemType &val){list.push_back(val);}

template <class elemType>
void Queue<elemType>::pop(){list.pop_front();}

#endif //DSLIB_QUEUE_H