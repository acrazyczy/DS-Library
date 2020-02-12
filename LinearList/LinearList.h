//
// Created by crazy_cloud on 2020/1/29.
//

#ifndef DSLIB_LINEARLIST_H
#define DSLIB_LINEARLIST_H

#include "Exception.h"
#include "Iterator.h"
#include <cstdlib>

template <class valueType>
class LinearList
{
public:
	LinearList() = default;

	virtual void clear() = 0;
	virtual bool empty() const = 0;
	virtual std::size_t size() const = 0;

	virtual const valueType &front() const = 0;
	virtual valueType &front() = 0;
	virtual const valueType &operator[](const int &) const = 0;
	virtual valueType &operator[](const int &) = 0;
	virtual const valueType &back() const = 0;
	virtual valueType &back() = 0;

	virtual ~LinearList() = default;
};

#endif //DSLIB_LINEARLIST_H