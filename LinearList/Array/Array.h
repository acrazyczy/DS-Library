//
// Created by crazy_cloud on 2020/1/29.
//

#ifndef DSLIB_ARRAY_H
#define DSLIB_ARRAY_H

#include "LinearList.h"

template <class valueType>
class Array : public LinearList<valueType>
{
private:
	valueType *array;
	std::size_t maxsize , tot;

	void extend();
public:
	class iterator
	{
		friend class Array<valueType>;
	private:
		valueType *ptr;
	public:
		typedef valueType _valueType;
		typedef valueType * _ptrType;

		explicit iterator(valueType *ptr_ = nullptr) : ptr(ptr_) {}

		valueType &operator*() const;
		std::size_t operator-(const iterator &) const;
		bool operator==(const iterator &) const;
		bool operator!=(const iterator &) const;

		iterator &operator++();
		iterator operator++(int);
		iterator operator+(const int &);

		iterator &operator--();
		iterator operator--(int);
		iterator operator-(const int &);
	};

	typedef Const_Iterator<iterator> const_iterator;

	Array() : LinearList<valueType>() , array(new valueType [1]) , maxsize(1) , tot(0) {}
	Array(const Array<valueType> &);
	Array<valueType> &operator=(const Array<valueType> &);

	virtual void clear() override;
	virtual bool empty() const override;
	void resize(std::size_t);
	void resize(std::size_t , const valueType &);
	virtual std::size_t size() const override;
	iterator insert(const_iterator , const valueType &);
	iterator erase(const_iterator);
	const_iterator find(const valueType &) const;
	iterator find(const valueType &);

	void push_front(const valueType &);
	void pop_front();
	void push_back(const valueType &);
	void pop_back();

	const_iterator cbegin() const;
	iterator begin();
	const_iterator cend() const;
	iterator end();

	virtual const valueType &front() const override;
	virtual valueType &front() override;
	virtual const valueType &operator[](const int &) const override;
	virtual valueType &operator[](const int &) override;
	virtual const valueType &back() const override;
	virtual valueType &back() override;

	virtual ~Array();
};

template <class valueType>
valueType &Array<valueType>::iterator::operator*() const {return *ptr;}

template <class valueType>
std::size_t Array<valueType>::iterator::operator-(const iterator &it) const {return ptr - it.ptr;}

template <class valueType>
bool Array<valueType>::iterator::operator==(const iterator &it) const {return ptr == it.ptr;}

template <class valueType>
bool Array<valueType>::iterator::operator!=(const iterator &it) const {return ptr != it.ptr;}

template <class valueType>
typename Array<valueType>::iterator &Array<valueType>::iterator::operator++()
{
	++ ptr;
	return *this;
}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::iterator::operator++(int x)
{
	iterator tmp = *this;
	++ ptr;
	return tmp;
}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::iterator::operator+(const int &x)
{
	if (x < 0) return operator-(-x);
	iterator tmp = *this;
	for (int i = 0;i < x;++ i) tmp = ++ tmp;
	return tmp;
}

template <class valueType>
typename Array<valueType>::iterator &Array<valueType>::iterator::operator--()
{
	-- ptr;
	return *this;
}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::iterator::operator--(int x)
{
	iterator tmp = *this;
	-- ptr;
	return tmp;
}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::iterator::operator-(const int &x)
{
	if (x < 0) return operator+(-x);
	iterator tmp = *this;
	for (int i = 0;i < x;++ i) -- tmp;
	return tmp;
}

template <class valueType>
Array<valueType>::Array(const Array<valueType> &rhs)
{
	array = new valueType [rhs.maxsize];
	for (std::size_t i = 0;i < rhs.tot;++ i) array[i] = rhs.array[i];
	maxsize = rhs.maxsize , tot = rhs.tot;
}

template <class valueType>
Array<valueType> &Array<valueType>::operator=(const Array<valueType> &rhs)
{
	if (this == &rhs) return *this;
	delete [] array;
	array = new valueType [rhs.maxsize];
	for (std::size_t i = 0;i < rhs.tot;++ i) array[i] = rhs.array[i];
	maxsize = rhs.maxsize , tot = rhs.tot;
	return *this;
}

template <class valueType>
void Array<valueType>::clear(){tot = 0;}

template <class valueType>
bool Array<valueType>::empty() const {return !tot;}

template <class valueType>
void Array<valueType>::resize(std::size_t n)
{
	Array<valueType> tmp;
	for (std::size_t i = 0;i < n && i < tot;++ i) tmp.push_back(array[i]);
	for (std::size_t i = tot;i < n;++ i) tmp.push_back(valueType());
	operator=(tmp);
}

template <class valueType>
void Array<valueType>::resize(std::size_t n , const valueType &val)
{
	Array<valueType> tmp;
	for (std::size_t i = 0;i < n && i < tot;++ i) tmp.push_back(array[i]);
	for (std::size_t i = tot;i < n;++ i) tmp.push_back(val);
	operator=(tmp);
}

template <class valueType>
std::size_t Array<valueType>::size() const {return tot;}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::insert(Array<valueType>::const_iterator pos , const valueType &val)
{
	Array<valueType> tmp;const_iterator it = cbegin();
	for (;it != pos && it != cend();++ it) tmp.push_back(*it);
	if (it == cend() && pos != cend()) throw(OutOfBound());
	tmp.push_back(val);
	for (it = pos;it != cend();++ it) tmp.push_back(*it);
	std::size_t gap = pos - cbegin();
	operator=(tmp);
	return begin() + gap;
}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::erase(Array<valueType>::const_iterator pos)
{
	Array<valueType> tmp;const_iterator it = cbegin();
	for (;it != pos && it != cend();++ it) tmp.push_back(*it);
	if (it == cend() && pos != cend()) throw(OutOfBound());
	for (it = pos + 1;it != cend();++ it) tmp.push_back(*it);
	std::size_t gap = pos - cbegin();
	operator=(tmp);
	return begin() + gap;
}

template <class valueType>
typename Array<valueType>::const_iterator Array<valueType>::find(const valueType &val) const
{
	const_iterator it = cbegin();
	for (;it != cend() && *it != val;++ it);
	return it;
}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::find(const valueType &val)
{
	return iterator(static_cast<const Array<valueType> &>(*this).find(val).ptr);
}

template <class valueType>
void Array<valueType>::push_front(const valueType &val){insert(cbegin() , val);}

template <class valueType>
void Array<valueType>::pop_front(){erase(cbegin());}

template <class valueType>
void Array<valueType>::push_back(const valueType &val)
{
	if (tot == maxsize) extend();
	array[tot ++] = val;
}

template <class valueType>
void Array<valueType>::pop_back()
{
	if (empty()) throw(OutOfBound());
	-- tot;
}

template <class valueType>
typename Array<valueType>::const_iterator Array<valueType>::cbegin() const {return const_iterator(array);}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::begin(){return iterator(array);}

template <class valueType>
typename Array<valueType>::const_iterator Array<valueType>::cend() const {return const_iterator(array + tot);}

template <class valueType>
typename Array<valueType>::iterator Array<valueType>::end(){return iterator(array + tot);}

template <class valueType>
const valueType &Array<valueType>::front() const {return *cbegin();}

template <class valueType>
valueType &Array<valueType>::front(){return *begin();}

template <class valueType>
const valueType &Array<valueType>::operator[](const int &pos) const
{
	if (pos < 0 || pos >= tot) throw(OutOfBound());
	return array[pos];
}

template <class valueType>
valueType &Array<valueType>::operator[](const int &pos)
{
	return const_cast<valueType &>(static_cast<const Array<valueType> &>(*this)[pos]);
}

template <class valueType>
const valueType &Array<valueType>::back() const {return (*this)[tot - 1];}

template <class valueType>
valueType &Array<valueType>::back(){return const_cast<valueType &>(static_cast<const Array<valueType> &>(*this).back());}

template <class valueType>
Array<valueType>::~Array(){delete [] array;}

template <class valueType>
void Array<valueType>::extend()
{
	valueType *tmp = new valueType [maxsize <<= 1];
	for (std::size_t i = 0;i < tot;++ i) tmp[i] = array[i];
	delete [] array , array = tmp;
}

#endif //DSLIB_ARRAY_H