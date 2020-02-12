//
// Created by crazy_cloud on 2020/2/1.
//

#ifndef DSLIB_STACK_H
#define DSLIB_STACK_H

#include "Array.h"

template <class valueType>
class Stack
{
private:
	Array<valueType> list;
public:
	Stack() = default;

	bool empty() const;
	std::size_t size() const;

	const valueType &top() const;
	valueType &top();

	void push(const valueType &);
	void pop();

	virtual ~Stack() = default;
};

template <class valueType>
bool Stack<valueType>::empty() const {return list.empty();}

template <class valueType>
std::size_t Stack<valueType>::size() const {return list.size();}

template <class valueType>
const valueType &Stack<valueType>::top() const {return list.back();}

template <class valueType>
valueType &Stack<valueType>::top(){return list.back();}

template <class valueType>
void Stack<valueType>::push(const valueType &val){list.push_back(val);}

template <class valueType>
void Stack<valueType>::pop(){list.pop_back();}

#endif //DSLIB_STACK_H