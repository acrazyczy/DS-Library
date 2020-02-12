//
// Created by crazy_cloud on 2020/2/8.
//

#ifndef DSLIB_AVLTREE_H
#define DSLIB_AVLTREE_H

/*#include <functional>
#include <cstdlib>

template <class keyType , class valueType , class compare = std::less<keyType> >
class AVLTree
{
private:
	struct Node
	{
		keyType key;
		valueType value;
		std::size_t height;
		Node *son[2];

		Node() : key() , value() , height(0) , son({nullptr , nullptr}) {}
	}*root;

	std::size_t tot;

	void rotate(Node *);
	void maintain(Node *);

	Node *find(const Node *& , const keyType &) const;
	Node *insert(Node * , const keyType & , const valueType &);
	void erase(Node * , const keyType &);
public:
	class const_iterator;

	class iterator
	{
		friend class AVLTree<keyType , valueType , compare>;
		friend const_iterator::const_iterator(iterator);
	private:
		Node *ptr;
	public:
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

	class const_iterator
	{
		friend class AVLTree<keyType , valueType , compare>;
	private:
		Node *ptr;
	public:
		explicit const_iterator(Node *ptr_ = nullptr) : ptr(ptr_) {}
		const_iterator(iterator it) : ptr(it.ptr) {}

		const valueType &operator*() const;
		bool operator==(const const_iterator &) const;
		bool operator!=(const const_iterator &) const;

		const_iterator &operator++();
		const_iterator operator++(int);
		const_iterator operator+(const int &);

		const_iterator &operator--();
		const_iterator operator--(int);
		const_iterator operator-(const int &);
	};

	AVLTree() : root(new Node) , tot(0) {}
	AVLTree(const AVLTree<keyType , valueType , compare> &);
	AVLTree<keyType , valueType , compare> &operator=(const AVLTree<keyType , valueType , compare> &);

	std::pair<iterator , bool> insert(const valueType &);
	bool erase(const valueType &);
	void erase(const const_iterator &);
	const_iterator find(const keyType &) const;
	iterator find(const keyType &);
	void clear();

	const_iterator cbegin() const;
	iterator begin();
	const_iterator cend() const;
	iterator end();

	~AVLTree();
};

template <class keyType , class valueType , class compare>
AVLTree<keyType , valueType , compare>::AVLTree(const AVLTree<keyType , valueType , compare> &rhs)
{
}

template <class keyType , class valueType , class compare>
AVLTree<keyType , valueType , compare> &AVLTree<keyType , valueType , compare>::operator=(const AVLTree<keyType , valueType , compare> &rhs)
{
}

template <class keyType , class valueType , class compare>
std::pair<iterator , bool> AVLTree<keyType , valueType , compare>::insert(const valueType &value)
{
}

template <class keyType , class valueType , class compare>
bool AVLTree<keyType , valueType , compare>::erase(const valueType &value)
{
}

template <class keyType , class valueType , class compare>
void AVLTree<keyType , valueType , compare>::erase(const const_iterator &pos)
{
}

template <class keyType , class valueType , class compare>
AVLTree<keyType , valueType , compare>::~AVLTree()
{
}*/

#endif //DSLIB_AVLTREE_H