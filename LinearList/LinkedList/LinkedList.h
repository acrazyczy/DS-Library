//
// Created by crazy_cloud on 2020/1/31.
//

#ifndef DSLIB_LINKEDLIST_H
#define DSLIB_LINKEDLIST_H

#include "LinearList.h"

template <class elemType>
class LinkedList : public LinearList<elemType>
{
private:
	struct Node
	{
		elemType val;
		Node *prec , *succ;

		Node() : val() , prec(nullptr) , succ(nullptr) {};
	}*head , *tail;

	int tot;
public:
	class const_iterator;

	class iterator
	{
		friend const_iterator::const_iterator(iterator);
	private:
		Node *ptr;
	public:
		explicit iterator(Node *ptr_ = nullptr) : ptr(ptr_) {}

		elemType &operator*() const;
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
		friend class LinkedList<elemType>;
	private:
		Node *ptr;
	public:
		explicit const_iterator(Node *ptr_ = nullptr) : ptr(ptr_) {}
		const_iterator(iterator it) : ptr(it.ptr) {}

		const elemType &operator*() const;
		bool operator==(const const_iterator &) const;
		bool operator!=(const const_iterator &) const;

		const_iterator &operator++();
		const const_iterator &operator++(int);
		const const_iterator &operator+(const int &);

		const_iterator &operator--();
		const const_iterator &operator--(int);
		const const_iterator &operator-(const int &);
	};

	LinkedList() : LinearList<elemType>() , head(new Node) , tail(head) , tot(0) {}
	LinkedList(const LinkedList<elemType> &);
	LinkedList<elemType> &operator=(const LinkedList<elemType> &);

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

	virtual ~LinkedList();
};

template <class elemType>
elemType &LinkedList<elemType>::iterator::operator*() const {return ptr -> val;}

template <class elemType>
bool LinkedList<elemType>::iterator::operator==(const iterator &it) const {return ptr == it.ptr;}

template <class elemType>
bool LinkedList<elemType>::iterator::operator!=(const iterator &it) const {return ptr != it.ptr;}

template <class elemType>
typename LinkedList<elemType>::iterator &LinkedList<elemType>::iterator::operator++()
{
	if (ptr -> succ == nullptr) throw(OutOfBound());
	ptr = ptr -> succ;
	return *this;
}

template <class elemType>
const typename LinkedList<elemType>::iterator &LinkedList<elemType>::iterator::operator++(int x)
{
	if (ptr -> succ == nullptr) throw(OutOfBound());
	iterator tmp = *this;
	ptr = ptr -> succ;
	return tmp;
}

template <class elemType>
const typename LinkedList<elemType>::iterator &LinkedList<elemType>::iterator::operator+(const int &x)
{
	if (x < 0) return operator-(-x);
	iterator tmp = *this;
	for (int i = 0;i < x;++ i) tmp = ++ tmp;
	return tmp;
}

template <class elemType>
typename LinkedList<elemType>::iterator &LinkedList<elemType>::iterator::operator--()
{
	if (ptr -> prec == nullptr) throw(OutOfBound());
	ptr = ptr -> prec;
	return *this;
}

template <class elemType>
const typename LinkedList<elemType>::iterator &LinkedList<elemType>::iterator::operator--(int x)
{
	if (ptr -> prec == nullptr) throw(OutOfBound());
	iterator tmp = *this;
	ptr = ptr -> prec;
	return tmp;
}

template <class elemType>
const typename LinkedList<elemType>::iterator &LinkedList<elemType>::iterator::operator-(const int &x)
{
	if (x < 0) return operator+(-x);
	iterator tmp = *this;
	for (int i = 0;i < x;++ i) -- tmp;
	return tmp;
}

template <class elemType>
const elemType &LinkedList<elemType>::const_iterator::operator*() const {return ptr -> val;}

template <class elemType>
bool LinkedList<elemType>::const_iterator::operator==(const const_iterator &it) const {return ptr == it.ptr;}

template <class elemType>
bool LinkedList<elemType>::const_iterator::operator!=(const const_iterator &it) const {return ptr != it.ptr;}

template <class elemType>
typename LinkedList<elemType>::const_iterator &LinkedList<elemType>::const_iterator::operator++()
{
	if (ptr -> succ == nullptr) throw(OutOfBound());
	ptr = ptr -> succ;
	return *this;
}

template <class elemType>
const typename LinkedList<elemType>::const_iterator &LinkedList<elemType>::const_iterator::operator++(int x)
{
	if (ptr -> succ == nullptr) throw(OutOfBound());
	const_iterator tmp = *this;
	ptr = ptr -> succ;
	return tmp;
}

template <class elemType>
const typename LinkedList<elemType>::const_iterator &LinkedList<elemType>::const_iterator::operator+(const int &x)
{
	if (x < 0) return operator-(-x);
	const_iterator tmp = *this;
	for (int i = 0;i < x;++ i) ++ tmp;
	return tmp;
}

template <class elemType>
typename LinkedList<elemType>::const_iterator &LinkedList<elemType>::const_iterator::operator--()
{
	if (ptr -> prec == nullptr) throw(OutOfBound());
	ptr = ptr -> prec;
	return *this;
}

template <class elemType>
const typename LinkedList<elemType>::const_iterator &LinkedList<elemType>::const_iterator::operator--(int x)
{
	if (ptr -> prec == nullptr) throw(OutOfBound());
	const_iterator tmp = *this;
	ptr = ptr -> prec;
	return tmp;
}

template <class elemType>
const typename LinkedList<elemType>::const_iterator &LinkedList<elemType>::const_iterator::operator-(const int &x)
{
	if (x < 0) return operator+(-x);
	const_iterator tmp = *this;
	for (int i = 0;i < x;++ i) -- tmp;
	return tmp;
}

template <class elemType>
LinkedList<elemType>::LinkedList(const LinkedList<elemType> &rhs)
{
	tot = rhs.tot , head = nullptr , tail = nullptr;
	for (const_iterator it = rhs.begin();it != rhs.end();++ it)
	{
		Node *node = new Node;
		node -> val = *it , node -> prec = tail;
		if (tail == nullptr) head = node;
		else tail -> succ = node;
		tail = node;
	}
	Node *node = new Node;
	if (head == nullptr) head = node;
	else tail -> succ = node;
	node -> prec = tail , tail = node;
}

template <class elemType>
LinkedList<elemType> &LinkedList<elemType>::operator=(const LinkedList<elemType> &rhs)
{
	if (this == &rhs) return *this;
	clear();
	tot = rhs.tot , head = tail = nullptr;
	for (const_iterator it = rhs.begin();it != rhs.end();++ it)
	{
		Node *node = new Node;
		node -> val = *it , node -> prec = tail;
		if (tail == nullptr) head = node;
		else tail -> succ = node;
		tail = node;
	}
	Node *node = new Node;
	if (head == nullptr) head = node;
	else tail -> succ = node;
	node -> prec = tail , tail = node;
	return *this;
}

template <class elemType>
void LinkedList<elemType>::clear()
{
	for (Node *ptr = head , *nxt;head != nullptr;head = nxt) nxt = head -> succ , delete head;
	tot = 0 , head = tail = new Node;
}

template <class elemType>
bool LinkedList<elemType>::empty() const {return !tot;}

template <class elemType>
void LinkedList<elemType>::resize(std::size_t n)
{
	LinkedList tmp;const_iterator it = begin();
	for (std::size_t i = 0;i < n && i < tot;++ i , ++ it) tmp.push_back(*it);
	for (std::size_t i = tot;i < n;++ i) tmp.push_back(elemType());
	operator=(tmp);
}

template <class elemType>
void LinkedList<elemType>::resize(std::size_t n , const elemType &val)
{
	LinkedList tmp;const_iterator it = begin();
	for (std::size_t i = 0;i < n && i < tot;++ i , ++ it) tmp.push_back(*it);
	for (std::size_t i = tot;i < n;++ i) tmp.push_back(val);
	operator=(tmp);
}

template <class elemType>
std::size_t LinkedList<elemType>::size() const {return tot;}

template <class elemType>
typename LinkedList<elemType>::iterator LinkedList<elemType>::insert(typename LinkedList<elemType>::const_iterator pos , const elemType &val)
{
	Node *ptr = new Node;ptr -> val = val , ++ tot;
	ptr -> prec = pos.ptr -> prec;
	if (pos.ptr == head) head = ptr;
	else pos.ptr -> prec -> succ = ptr;
	ptr -> succ = pos.ptr , pos.ptr -> prec = ptr;
	return iterator(ptr);
}

template <class elemType>
typename LinkedList<elemType>::iterator LinkedList<elemType>::erase(typename LinkedList<elemType>::const_iterator pos)
{
	if (pos.ptr == tail) throw(OutOfBound());
	iterator ret(pos.ptr -> succ);
	if (pos.ptr == head) head = pos.ptr -> succ;
	else pos.ptr -> prec -> succ = pos.ptr -> succ;
	pos.ptr -> succ -> prec = pos.ptr -> prec;
	delete pos.ptr , -- tot;
	return ret;
}

template <class elemType>
typename LinkedList<elemType>::const_iterator LinkedList<elemType>::find(const elemType &val) const
{
	const_iterator it = begin();
	for (;it != end() && *it != val;++ it);
	return it;
}

template <class elemType>
typename LinkedList<elemType>::iterator LinkedList<elemType>::find(const elemType &val)
{
	return iterator(static_cast<const LinkedList<elemType> &>(*this).find(val).ptr);
}

template <class elemType>
void LinkedList<elemType>::push_front(const elemType &val){insert(begin() , val);}

template <class elemType>
void LinkedList<elemType>::pop_front(){erase(begin());}

template <class elemType>
void LinkedList<elemType>::push_back(const elemType &val){insert(end() , val);}

template <class elemType>
void LinkedList<elemType>::pop_back(){erase(-- end());}

template <class elemType>
typename LinkedList<elemType>::const_iterator LinkedList<elemType>::begin() const {return const_iterator(head);}

template <class elemType>
typename LinkedList<elemType>::iterator LinkedList<elemType>::begin(){return iterator(head);}

template <class elemType>
typename LinkedList<elemType>::const_iterator LinkedList<elemType>::end() const {return const_iterator(tail);}

template <class elemType>
typename LinkedList<elemType>::iterator LinkedList<elemType>::end(){return iterator(tail);}

template <class elemType>
const elemType &LinkedList<elemType>::front() const {return *begin();}

template <class elemType>
elemType &LinkedList<elemType>::front(){return *begin();}

template <class elemType>
const elemType &LinkedList<elemType>::operator[](const int &pos) const
{
	if (pos < 0 || pos >= tot) throw(OutOfBound());
	const_iterator it = begin();
	for (int i = 1;i <= pos;++ i) ++ it;
	return *it;
}

template <class elemType>
elemType &LinkedList<elemType>::operator[](const int &pos)
{
	return const_cast<elemType &>(static_cast<const LinkedList<elemType> &>(*this)[pos]);
}

template <class elemType>
const elemType &LinkedList<elemType>::back() const {return *(-- end());}

template <class elemType>
elemType &LinkedList<elemType>::back() {return *(-- end());}

template <class elemType>
LinkedList<elemType>::~LinkedList(){clear() , delete head;}

#endif //DSLIB_LINKEDLIST_H