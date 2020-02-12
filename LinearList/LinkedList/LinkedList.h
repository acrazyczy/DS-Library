//
// Created by crazy_cloud on 2020/1/31.
//

#ifndef DSLIB_LINKEDLIST_H
#define DSLIB_LINKEDLIST_H

#include "LinearList.h"

template <class valueType>
class LinkedList : public LinearList<valueType>
{
private:
	struct Node
	{
		valueType val;
		Node *prec , *succ;

		Node() : val() , prec(nullptr) , succ(nullptr) {};
	}*head , *tail;

	std::size_t tot;
public:
	class iterator
	{
		friend class LinkedList<valueType>;
	private:
		Node *ptr;
	public:
		typedef valueType _valueType;
		typedef Node * _ptrType;

		explicit iterator(Node *ptr_ = nullptr) : ptr(ptr_) {}

		valueType &operator*() const;
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

	LinkedList() : LinearList<valueType>() , head(new Node) , tail(head) , tot(0) {}
	LinkedList(const LinkedList<valueType> &);
	LinkedList<valueType> &operator=(const LinkedList<valueType> &);

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

	void merge(LinkedList<valueType> &);

	virtual ~LinkedList();
};

template <class valueType>
valueType &LinkedList<valueType>::iterator::operator*() const {return ptr -> val;}

template <class valueType>
bool LinkedList<valueType>::iterator::operator==(const iterator &it) const {return ptr == it.ptr;}

template <class valueType>
bool LinkedList<valueType>::iterator::operator!=(const iterator &it) const {return ptr != it.ptr;}

template <class valueType>
typename LinkedList<valueType>::iterator &LinkedList<valueType>::iterator::operator++()
{
	if (ptr -> succ == nullptr) throw(OutOfBound());
	ptr = ptr -> succ;
	return *this;
}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::iterator::operator++(int x)
{
	if (ptr -> succ == nullptr) throw(OutOfBound());
	iterator tmp = *this;
	ptr = ptr -> succ;
	return tmp;
}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::iterator::operator+(const int &x)
{
	if (x < 0) return operator-(-x);
	iterator tmp = *this;
	for (int i = 0;i < x;++ i) tmp = ++ tmp;
	return tmp;
}

template <class valueType>
typename LinkedList<valueType>::iterator &LinkedList<valueType>::iterator::operator--()
{
	if (ptr -> prec == nullptr) throw(OutOfBound());
	ptr = ptr -> prec;
	return *this;
}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::iterator::operator--(int x)
{
	if (ptr -> prec == nullptr) throw(OutOfBound());
	iterator tmp = *this;
	ptr = ptr -> prec;
	return tmp;
}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::iterator::operator-(const int &x)
{
	if (x < 0) return operator+(-x);
	iterator tmp = *this;
	for (int i = 0;i < x;++ i) -- tmp;
	return tmp;
}

template <class valueType>
LinkedList<valueType>::LinkedList(const LinkedList<valueType> &rhs)
{
	tot = rhs.tot , head = nullptr , tail = nullptr;
	for (const_iterator it = rhs.cbegin();it != rhs.cend();++ it)
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

template <class valueType>
LinkedList<valueType> &LinkedList<valueType>::operator=(const LinkedList<valueType> &rhs)
{
	if (this == &rhs) return *this;
	clear();
	tot = rhs.tot , head = tail = nullptr;
	for (const_iterator it = rhs.cbegin();it != rhs.cend();++ it)
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

template <class valueType>
void LinkedList<valueType>::clear()
{
	for (Node *ptr = head , *nxt;head != nullptr;head = nxt) nxt = head -> succ , delete head;
	tot = 0 , head = tail = new Node;
}

template <class valueType>
bool LinkedList<valueType>::empty() const {return !tot;}

template <class valueType>
void LinkedList<valueType>::resize(std::size_t n)
{
	LinkedList tmp;const_iterator it = cbegin();
	for (std::size_t i = 0;i < n && i < tot;++ i , ++ it) tmp.push_back(*it);
	for (std::size_t i = tot;i < n;++ i) tmp.push_back(valueType());
	operator=(tmp);
}

template <class valueType>
void LinkedList<valueType>::resize(std::size_t n , const valueType &val)
{
	LinkedList tmp;const_iterator it = begin();
	for (std::size_t i = 0;i < n && i < tot;++ i , ++ it) tmp.push_back(*it);
	for (std::size_t i = tot;i < n;++ i) tmp.push_back(val);
	operator=(tmp);
}

template <class valueType>
std::size_t LinkedList<valueType>::size() const {return tot;}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::insert(typename LinkedList<valueType>::const_iterator pos , const valueType &val)
{
	Node *ptr = new Node;ptr -> val = val , ++ tot;
	ptr -> prec = pos.ptr -> prec;
	if (pos.ptr == head) head = ptr;
	else pos.ptr -> prec -> succ = ptr;
	ptr -> succ = pos.ptr , pos.ptr -> prec = ptr;
	return iterator(ptr);
}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::erase(typename LinkedList<valueType>::const_iterator pos)
{
	if (pos.ptr == tail) throw(OutOfBound());
	iterator ret(pos.ptr -> succ);
	if (pos.ptr == head) head = pos.ptr -> succ;
	else pos.ptr -> prec -> succ = pos.ptr -> succ;
	pos.ptr -> succ -> prec = pos.ptr -> prec;
	delete pos.ptr , -- tot;
	return ret;
}

template <class valueType>
typename LinkedList<valueType>::const_iterator LinkedList<valueType>::find(const valueType &val) const
{
	const_iterator it = cbegin();
	for (;it != cend() && *it != val;++ it);
	return it;
}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::find(const valueType &val)
{
	return iterator(static_cast<const LinkedList<valueType> &>(*this).find(val).ptr);
}

template <class valueType>
void LinkedList<valueType>::push_front(const valueType &val){insert(cbegin() , val);}

template <class valueType>
void LinkedList<valueType>::pop_front(){erase(cbegin());}

template <class valueType>
void LinkedList<valueType>::push_back(const valueType &val){insert(cend() , val);}

template <class valueType>
void LinkedList<valueType>::pop_back(){erase(-- cend());}

template <class valueType>
typename LinkedList<valueType>::const_iterator LinkedList<valueType>::cbegin() const {return const_iterator(head);}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::begin(){return iterator(head);}

template <class valueType>
typename LinkedList<valueType>::const_iterator LinkedList<valueType>::cend() const {return const_iterator(tail);}

template <class valueType>
typename LinkedList<valueType>::iterator LinkedList<valueType>::end(){return iterator(tail);}

template <class valueType>
const valueType &LinkedList<valueType>::front() const {return *cbegin();}

template <class valueType>
valueType &LinkedList<valueType>::front(){return *begin();}

template <class valueType>
const valueType &LinkedList<valueType>::operator[](const int &pos) const
{
	if (pos < 0 || pos >= tot) throw(OutOfBound());
	const_iterator it = cbegin();
	for (int i = 1;i <= pos;++ i) ++ it;
	return *it;
}

template <class valueType>
valueType &LinkedList<valueType>::operator[](const int &pos)
{
	return const_cast<valueType &>(static_cast<const LinkedList<valueType> &>(*this)[pos]);
}

template <class valueType>
const valueType &LinkedList<valueType>::back() const {return *(-- cend());}

template <class valueType>
valueType &LinkedList<valueType>::back() {return *(-- end());}

template <class valueType>
void LinkedList<valueType>::merge(LinkedList<valueType> &rhs)
{
	if (tail -> prec == nullptr) head = rhs.head;
	else tail -> prec -> succ = rhs.head;
	rhs.head = tail , tail = rhs.tail , rhs.tail = rhs.head , tot += rhs.tot , rhs.tot = 0;
}

template <class valueType>
LinkedList<valueType>::~LinkedList(){clear() , delete head;}

#endif //DSLIB_LINKEDLIST_H