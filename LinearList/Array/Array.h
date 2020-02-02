//
// Created by crazy_cloud on 2020/1/29.
//

#ifndef DSLIB_ARRAY_H
#define DSLIB_ARRAY_H

#include "LinearList.h"

template <class elemType>
class Array : public LinearList<elemType>
{
private:
	elemType *array;
	std::size_t maxsize , tot;

	void extend();
public:
	typedef const elemType* const_iterator;
	typedef elemType* iterator;

	Array() : LinearList<elemType>() , array(new elemType [1]) , maxsize(1) , tot(0) {}
	Array(const Array<elemType> &);
	Array<elemType> &operator=(const Array<elemType> &);

	virtual void clear() override;
	virtual bool empty() const override;
	void resize(std::size_t);
	void resize(std::size_t , const elemType &);
	virtual std::size_t size() const override;
	iterator insert(const_iterator , const elemType &);
	iterator erase(const_iterator);
	const_iterator find(const elemType &) const;
	iterator find(const elemType &);

	void push_front(const elemType &);
	void pop_front();
	void push_back(const elemType &);
	void pop_back();

	const_iterator begin() const;
	iterator begin();
	const_iterator end() const;
	iterator end();

	virtual const elemType &front() const override;
	virtual elemType &front() override;
	virtual const elemType &operator[](const int &) const override;
	virtual elemType &operator[](const int &) override;
	virtual const elemType &back() const override;
	virtual elemType &back() override;

	virtual ~Array();
};

template <class elemType>
Array<elemType>::Array(const Array<elemType> &rhs)
{
	array = new elemType [rhs.maxsize];
	for (std::size_t i = 0;i < rhs.tot;++ i) array[i] = rhs.array[i];
	maxsize = rhs.maxsize , tot = rhs.tot;
}

template <class elemType>
Array<elemType> &Array<elemType>::operator=(const Array<elemType> &rhs)
{
	if (this == &rhs) return *this;
	delete [] array;
	array = new elemType [rhs.maxsize];
	for (std::size_t i = 0;i < rhs.tot;++ i) array[i] = rhs.array[i];
	maxsize = rhs.maxsize , tot = rhs.tot;
	return *this;
}

template <class elemType>
void Array<elemType>::clear(){tot = 0;}

template <class elemType>
bool Array<elemType>::empty() const {return !tot;}

template <class elemType>
void Array<elemType>::resize(std::size_t n)
{
	Array<elemType> tmp;
	for (std::size_t i = 0;i < n && i < tot;++ i) tmp.push_back(array[i]);
	for (std::size_t i = tot;i < n;++ i) tmp.push_back(elemType());
	operator=(tmp);
}

template <class elemType>
void Array<elemType>::resize(std::size_t n , const elemType &val)
{
	Array<elemType> tmp;
	for (std::size_t i = 0;i < n && i < tot;++ i) tmp.push_back(array[i]);
	for (std::size_t i = tot;i < n;++ i) tmp.push_back(val);
	operator=(tmp);
}

template <class elemType>
std::size_t Array<elemType>::size() const {return tot;}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::insert(Array<elemType>::const_iterator pos , const elemType &val)
{
	Array<elemType> tmp;const_iterator it = begin();iterator ret;
	for (;it != pos && it != end();++ it) tmp.push_back(*it);
	if (it == end() && pos != end()) throw(OutOfBound());
	ret = tmp.end() , tmp.push_back(val);
	for (it = pos;it != end();++ it) tmp.push_back(*it);
	operator=(tmp);
	return ret;
}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::erase(Array<elemType>::const_iterator pos)
{
	Array<elemType> tmp;const_iterator it = begin();iterator ret;
	for (;it != pos && it != end();++ it) tmp.push_back(*it);
	if (it == end() && pos != end()) throw(OutOfBound());
	ret = tmp.end();
	for (it = pos + 1;it != end();++ it) tmp.push_back(*it);
	operator=(tmp);
	return ret;
}

template <class elemType>
typename Array<elemType>::const_iterator Array<elemType>::find(const elemType &val) const
{
	const_iterator it = begin();
	for (;it != end() && *it != val;++ it);
	return it;
}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::find(const elemType &val)
{
	return const_cast<iterator>(static_cast<const Array<elemType> &>(*this).find(val));
}

template <class elemType>
void Array<elemType>::push_front(const elemType &val){insert(begin() , val);}

template <class elemType>
void Array<elemType>::pop_front(){erase(begin());}

template <class elemType>
void Array<elemType>::push_back(const elemType &val)
{
	if (tot == maxsize) extend();
	array[tot ++] = val;
}

template <class elemType>
void Array<elemType>::pop_back()
{
	if (empty()) throw(OutOfBound());
	-- tot;
}

template <class elemType>
typename Array<elemType>::const_iterator Array<elemType>::begin() const {return array;}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::begin(){return array;}

template <class elemType>
typename Array<elemType>::const_iterator Array<elemType>::end() const {return array + tot;}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::end(){return array + tot;}

template <class elemType>
const elemType &Array<elemType>::front() const {return *begin();}

template <class elemType>
elemType &Array<elemType>::front(){return *begin();}

template <class elemType>
const elemType &Array<elemType>::operator[](const int &pos) const
{
	if (pos < 0 || pos >= tot) throw(OutOfBound());
	return array[pos];
}

template <class elemType>
elemType &Array<elemType>::operator[](const int &pos)
{
	return const_cast<elemType &>(static_cast<const Array<elemType> &>(*this)[pos]);
}

template <class elemType>
const elemType &Array<elemType>::back() const {return (*this)[tot - 1];}

template <class elemType>
elemType &Array<elemType>::back(){return const_cast<elemType &>(static_cast<const Array<elemType> &>(*this).back());}

template <class elemType>
Array<elemType>::~Array(){delete [] array;}

template <class elemType>
void Array<elemType>::extend()
{
	elemType *tmp = new elemType [maxsize <<= 1];
	for (std::size_t i = 0;i < tot;++ i) tmp[i] = array[i];
	delete [] array , array = tmp;
}

#endif //DSLIB_ARRAY_H