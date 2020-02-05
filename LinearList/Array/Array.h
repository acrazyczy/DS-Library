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
	class const_iterator;

	class iterator
	{
		friend class Array<elemType>;
		friend const_iterator::const_iterator(iterator);
	private:
		elemType *ptr;
	public:
		explicit iterator(elemType *ptr_ = nullptr) : ptr(ptr_) {}

		elemType &operator*() const;
		std::size_t operator-(const iterator &) const;
		bool operator==(const iterator &) const;
		bool operator!=(const iterator &) const;

		iterator &operator++();
		const iterator &operator++(int);
		const iterator &operator+(const int &);

		iterator &operator--();
		const iterator &operator--(int);
		const iterator &operator-(const int &);
	};

	class const_iterator
	{
		friend class Array<elemType>;
	private:
		elemType *ptr;
	public:
		explicit const_iterator(elemType *ptr_ = nullptr) : ptr(ptr_) {}
		const_iterator(iterator it) : ptr(it.ptr) {}

		const elemType &operator*() const;
		std::size_t operator-(const const_iterator &) const;
		bool operator==(const const_iterator &) const;
		bool operator!=(const const_iterator &) const;

		const_iterator &operator++();
		const const_iterator &operator++(int);
		const const_iterator &operator+(const int &);

		const_iterator &operator--();
		const const_iterator &operator--(int);
		const const_iterator &operator-(const int &);
	};

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

	const_iterator cbegin() const;
	iterator begin();
	const_iterator cend() const;
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
elemType &Array<elemType>::iterator::operator*() const {return *ptr;}

template <class elemType>
std::size_t Array<elemType>::iterator::operator-(const iterator &it) const {return ptr - it.ptr;}

template <class elemType>
bool Array<elemType>::iterator::operator==(const iterator &it) const {return ptr == it.ptr;}

template <class elemType>
bool Array<elemType>::iterator::operator!=(const iterator &it) const {return ptr != it.ptr;}

template <class elemType>
typename Array<elemType>::iterator &Array<elemType>::iterator::operator++()
{
	++ ptr;
	return *this;
}

template <class elemType>
const typename Array<elemType>::iterator &Array<elemType>::iterator::operator++(int x)
{
	static iterator tmp;
	tmp = *this , ++ ptr;
	return tmp;
}

template <class elemType>
const typename Array<elemType>::iterator &Array<elemType>::iterator::operator+(const int &x)
{
	if (x < 0) return operator-(-x);
	static iterator tmp;
	tmp = *this;
	for (int i = 0;i < x;++ i) tmp = ++ tmp;
	return tmp;
}

template <class elemType>
typename Array<elemType>::iterator &Array<elemType>::iterator::operator--()
{
	-- ptr;
	return *this;
}

template <class elemType>
const typename Array<elemType>::iterator &Array<elemType>::iterator::operator--(int x)
{
	static iterator tmp;
	tmp = *this , -- ptr;
	return tmp;
}

template <class elemType>
const typename Array<elemType>::iterator &Array<elemType>::iterator::operator-(const int &x)
{
	if (x < 0) return operator+(-x);
	static iterator tmp;
	tmp = *this;
	for (int i = 0;i < x;++ i) -- tmp;
	return tmp;
}

template <class elemType>
const elemType &Array<elemType>::const_iterator::operator*() const {return *ptr;}

template <class elemType>
std::size_t Array<elemType>::const_iterator::operator-(const const_iterator &it) const {return ptr - it.ptr;}

template <class elemType>
bool Array<elemType>::const_iterator::operator==(const const_iterator &it) const {return ptr == it.ptr;}

template <class elemType>
bool Array<elemType>::const_iterator::operator!=(const const_iterator &it) const {return ptr != it.ptr;}

template <class elemType>
typename Array<elemType>::const_iterator &Array<elemType>::const_iterator::operator++()
{
	++ ptr;
	return *this;
}

template <class elemType>
const typename Array<elemType>::const_iterator &Array<elemType>::const_iterator::operator++(int x)
{
	static const_iterator tmp;
	tmp = *this , ++ ptr;
	return tmp;
}

template <class elemType>
const typename Array<elemType>::const_iterator &Array<elemType>::const_iterator::operator+(const int &x)
{
	if (x < 0) return operator-(-x);
	static const_iterator tmp;
	tmp = *this;
	for (int i = 0;i < x;++ i) ++ tmp;
	return tmp;
}

template <class elemType>
typename Array<elemType>::const_iterator &Array<elemType>::const_iterator::operator--()
{
	-- ptr;
	return *this;
}

template <class elemType>
const typename Array<elemType>::const_iterator &Array<elemType>::const_iterator::operator--(int x)
{
	static const_iterator tmp;
	tmp = *this , -- ptr;
	return tmp;
}

template <class elemType>
const typename Array<elemType>::const_iterator &Array<elemType>::const_iterator::operator-(const int &x)
{
	if (x < 0) return operator+(-x);
	static const_iterator tmp;
	tmp = *this;
	for (int i = 0;i < x;++ i) -- tmp;
	return tmp;
}


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
	Array<elemType> tmp;const_iterator it = cbegin();
	for (;it != pos && it != cend();++ it) tmp.push_back(*it);
	if (it == cend() && pos != cend()) throw(OutOfBound());
	tmp.push_back(val);
	for (it = pos;it != cend();++ it) tmp.push_back(*it);
	std::size_t gap = pos - cbegin();
	operator=(tmp);
	return begin() + gap;
}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::erase(Array<elemType>::const_iterator pos)
{
	Array<elemType> tmp;const_iterator it = cbegin();
	for (;it != pos && it != cend();++ it) tmp.push_back(*it);
	if (it == cend() && pos != cend()) throw(OutOfBound());
	for (it = pos + 1;it != cend();++ it) tmp.push_back(*it);
	std::size_t gap = pos - cbegin();
	operator=(tmp);
	return begin() + gap;
}

template <class elemType>
typename Array<elemType>::const_iterator Array<elemType>::find(const elemType &val) const
{
	const_iterator it = cbegin();
	for (;it != cend() && *it != val;++ it);
	return it;
}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::find(const elemType &val)
{
	return iterator(static_cast<const Array<elemType> &>(*this).find(val).ptr);
}

template <class elemType>
void Array<elemType>::push_front(const elemType &val){insert(cbegin() , val);}

template <class elemType>
void Array<elemType>::pop_front(){erase(cbegin());}

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
typename Array<elemType>::const_iterator Array<elemType>::cbegin() const {return const_iterator(array);}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::begin(){return iterator(array);}

template <class elemType>
typename Array<elemType>::const_iterator Array<elemType>::cend() const {return const_iterator(array + tot);}

template <class elemType>
typename Array<elemType>::iterator Array<elemType>::end(){return iterator(array + tot);}

template <class elemType>
const elemType &Array<elemType>::front() const {return *cbegin();}

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