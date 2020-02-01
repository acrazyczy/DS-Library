//
// Created by crazy_cloud on 2020/2/1.
//

#ifndef DSLIB_STACK_H
#define DSLIB_STACK_H

#include "Array.h"

template <class elemType>
class Stack
{
private:
	Array<elemType> list;
public:
	bool empty() const;
	std::size_t size() const;

	const elemType &top() const;
	elemType &top();

	void push(const elemType &);
	void pop();
};

template <class elemType>
bool Stack<elemType>::empty() const {return list.empty();}

template <class elemType>
std::size_t Stack<elemType>::size() const {return list.size();}

template <class elemType>
const elemType &Stack<elemType>::top() const {return list.back();}

template <class elemType>
elemType &Stack<elemType>::top(){return list.back();}

template <class elemType>
void Stack<elemType>::push(const elemType &val){list.push_back(val);}

template <class elemType>
void Stack<elemType>::pop(){list.pop_back();}

#endif //DSLIB_STACK_H