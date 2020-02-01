//
// Created by crazy_cloud on 2020/1/29.
//

#ifndef DSLIB_LINEARLIST_H
#define DSLIB_LINEARLIST_H

#include <cstdlib>

class OutOfBound{};

template <class elemType>
class LinearList
{
public:
	LinearList() = default;

	virtual void clear() = 0;
	virtual bool empty() const = 0;
	virtual std::size_t size() const = 0;

	virtual const elemType &front() const = 0;
	virtual elemType &front() = 0;
	virtual const elemType &operator[](const int &) const = 0;
	virtual elemType &operator[](const int &) = 0;
	virtual const elemType &back() const = 0;
	virtual elemType &back() = 0;

	virtual ~LinearList() = default;
};

#endif //DSLIB_LINEARLIST_H