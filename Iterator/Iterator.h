//
// Created by crazy_cloud on 2020/2/12.
//

#ifndef DSLIB_ITERATOR_H
#define DSLIB_ITERATOR_H

template <class Iterator>
class Const_Iterator : public Iterator
{
public:
	typedef typename Iterator::_valueType _valueType;
	typedef typename Iterator::_ptrType _ptrType;

	explicit Const_Iterator(_ptrType ptr = nullptr) : Iterator(ptr) {}
	Const_Iterator(Iterator it) : Iterator(it) {}

	const _valueType &operator*() const;
	bool operator==(const Const_Iterator &) const;
	bool operator!=(const Const_Iterator &) const;

	Const_Iterator &operator++();
	Const_Iterator operator++(int);
	Const_Iterator operator+(const int &) const;

	Const_Iterator &operator--();
	Const_Iterator operator--(int);
	Const_Iterator operator-(const int &) const;
};

template <class Iterator>
class Reverse_Iterator : public Iterator
{
public:
	typedef typename Iterator::_valueType _valueType;
	typedef typename Iterator::_ptrType _ptrType;

	explicit Reverse_Iterator(_ptrType ptr = nullptr) : Iterator(ptr) {}
	Reverse_Iterator(Iterator it) : Iterator(it) {}

	_valueType &operator*() const;
	bool operator==(const Reverse_Iterator &) const;
	bool operator!=(const Reverse_Iterator &) const;

	Reverse_Iterator &operator++();
	Reverse_Iterator operator++(int);
	Reverse_Iterator operator+(const int &) const;

	Reverse_Iterator &operator--();
	Reverse_Iterator operator--(int);
	Reverse_Iterator operator-(const int &) const;
};

template <class Iterator>
class Const_Reverse_Iterator : public Iterator
{
public:
	typedef typename Iterator::_valueType _valueType;
	typedef typename Iterator::_ptrType _ptrType;

	explicit Const_Reverse_Iterator(_ptrType ptr = nullptr) : Iterator(ptr) {}
	Const_Reverse_Iterator(Iterator it) : Iterator(it) {};

	const _valueType &operator*() const;
	bool operator==(const Const_Reverse_Iterator &) const;
	bool operator!=(const Const_Reverse_Iterator &) const;

	Const_Reverse_Iterator &operator++();
	Const_Reverse_Iterator operator++(int);
	Const_Reverse_Iterator operator+(const int &) const;

	Const_Reverse_Iterator &operator--();
	Const_Reverse_Iterator operator--(int);
	Const_Reverse_Iterator operator-(const int &) const;
};

template <class Iterator>
const typename Const_Iterator<Iterator>::_valueType &Const_Iterator<Iterator>::operator*() const {return Iterator::operator*();}

template <class Iterator>
bool Const_Iterator<Iterator>::operator==(const Const_Iterator &rhs) const {return Iterator::operator==(rhs);}

template <class Iterator>
bool Const_Iterator<Iterator>::operator!=(const Const_Iterator &rhs) const {return Iterator::operator!=(rhs);}

template <class Iterator>
Const_Iterator<Iterator> &Const_Iterator<Iterator>::operator++(){return Iterator::operator++() , *this;}

template <class Iterator>
Const_Iterator<Iterator> Const_Iterator<Iterator>::operator++(int x){return Iterator::operator++(x);}

template <class Iterator>
Const_Iterator<Iterator> Const_Iterator<Iterator>::operator+(const int &x) const {return Iterator::operator+(x);}

template <class Iterator>
Const_Iterator<Iterator> &Const_Iterator<Iterator>::operator--(){return Iterator::operator--() , *this;}

template <class Iterator>
Const_Iterator<Iterator> Const_Iterator<Iterator>::operator--(int x){return Iterator::operator--(x);}

template <class Iterator>
Const_Iterator<Iterator> Const_Iterator<Iterator>::operator-(const int &x) const {return Iterator::operator-(x);}

template <class Iterator>
typename Reverse_Iterator<Iterator>::_valueType &Reverse_Iterator<Iterator>::operator*() const {return *Iterator::operator-(1);}

template <class Iterator>
bool Reverse_Iterator<Iterator>::operator==(const Reverse_Iterator &rhs) const {return Iterator::operator==(rhs);}

template <class Iterator>
bool Reverse_Iterator<Iterator>::operator!=(const Reverse_Iterator &rhs) const {return Iterator::operator!=(rhs);}

template <class Iterator>
Reverse_Iterator<Iterator> &Reverse_Iterator<Iterator>::operator++(){return Iterator::operator--() , *this;}

template <class Iterator>
Reverse_Iterator<Iterator> Reverse_Iterator<Iterator>::operator++(int x){return Iterator::operator--(x);}

template <class Iterator>
Reverse_Iterator<Iterator> Reverse_Iterator<Iterator>::operator+(const int &x) const {return Iterator::operator-(x);}

template <class Iterator>
Reverse_Iterator<Iterator> &Reverse_Iterator<Iterator>::operator--(){return Iterator::operator++() , *this;}

template <class Iterator>
Reverse_Iterator<Iterator> Reverse_Iterator<Iterator>::operator--(int x){return Iterator::operator++(x);}

template <class Iterator>
Reverse_Iterator<Iterator> Reverse_Iterator<Iterator>::operator-(const int &x) const {return Iterator::operator+(x);}

template <class Iterator>
const typename Const_Reverse_Iterator<Iterator>::_valueType &Const_Reverse_Iterator<Iterator>::operator*() const {return *Iterator::operator-(1);}

template <class Iterator>
bool Const_Reverse_Iterator<Iterator>::operator==(const Const_Reverse_Iterator &rhs) const {return Iterator::operator==(rhs);}

template <class Iterator>
bool Const_Reverse_Iterator<Iterator>::operator!=(const Const_Reverse_Iterator &rhs) const {return Iterator::operator!=(rhs);}

template <class Iterator>
Const_Reverse_Iterator<Iterator> &Const_Reverse_Iterator<Iterator>::operator++(){return Iterator::operator--() , *this;}

template <class Iterator>
Const_Reverse_Iterator<Iterator> Const_Reverse_Iterator<Iterator>::operator++(int x){return Iterator::operator--(x);}

template <class Iterator>
Const_Reverse_Iterator<Iterator> Const_Reverse_Iterator<Iterator>::operator+(const int &x) const {return Iterator::operator-(x);}

template <class Iterator>
Const_Reverse_Iterator<Iterator> &Const_Reverse_Iterator<Iterator>::operator--(){return Iterator::operator++() , *this;}

template <class Iterator>
Const_Reverse_Iterator<Iterator> Const_Reverse_Iterator<Iterator>::operator--(int x){return Iterator::operator++(x);}

template <class Iterator>
Const_Reverse_Iterator<Iterator> Const_Reverse_Iterator<Iterator>::operator-(const int &x) const {return Iterator::operator+(x);}

#endif //DSLIB_ITERATOR_H