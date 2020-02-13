#include "AVLTree.h"
#include "Array.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

/*void search(Array<int> &list , int x , std::ofstream &out)
{
	Array<int>::const_iterator it = list.find(x);
	if (it == list.cend()) out << x << " not found." << std::endl;
	else
	{
		out << x << " found: " << *it << std::endl;
		it = list.erase(it);
		out << "fellow: " << *it << std::endl;
		for (auto x : list) out << x << " ";
		out << std::endl;
	}
}*/

int main()
{
	/*Array<int> list , list_;
	std::ifstream in("data.in");
	for (int x;in >> x;) list.push_back(x);
	in.close() , list_ = list;
	const Array<int> const_list(list);
	//std::sort(list.begin() , list.end() , std::greater<int>());
	std::ofstream out("data.out");
	for (auto x : list) out << x << " ";
	out << std::endl;
	for (Array<int>::iterator it = list.begin();it != list.end();++ it) out << *it << " ";
	out << std::endl;
	for (Array<int>::const_iterator it = const_list.cbegin();it != const_list.cend();++ it) out << *it << " ";
	out << std::endl;
	size_t cnt = const_list.size();
	for (size_t i = 0;i < cnt;++ i) out << const_list[i] << " ";
	out << std::endl;
	list.pop_back() , list.pop_front() , list.push_front(-1);
	for (Array<int>::iterator it = list.begin();it != list.end();++ it) out << *it << " ";
	out << std::endl;
	cnt = list.size();
	list[7] *= -1;
	for (size_t i = 0;i < cnt;++ i) out << list[i] << " ";
	out << std::endl;
	list.front() *= -1 , list.back() *= -1;
	for (auto x : list) out << x << " ";
	out << std::endl;
	list.resize(10 , -2);
	for (auto x : list) out << x << " ";
	out << std::endl;
	list.resize(15 , -2);
	for (auto x : list) out << x << " ";
	out << std::endl;
	search(list , 5 , out) , search(list , -5 , out);
	for (auto x : list) out << x << " ";
	out << std::endl;
	list.merge(list_);
	for (auto x : list) out << x << " ";
	out << std::endl;
	for (auto x : list_) out << x << " ";
	out << std::endl;
	out.close();*/

	/*Queue<int> queue;Stack<int> stack;
	std::ifstream in("data.in");
	for (int x;in >> x;) queue.push(x) , stack.push(x);
	in.close();
	std::ofstream out("data.out");
	for (;!queue.empty();queue.pop()) out << queue.front() << " ";
	out << std::endl;
	for (;!stack.empty();stack.pop()) out << stack.top() << " ";
	out << std::endl;
	out.close();*/

	std::srand(std::time(0));

	/*BinomialHeap<int> ltree , ltree_ , ltree__;
	std::ifstream in("data.in");
	for (int x;in >> x;) ltree.push(x);
	in.close();
	ltree__ = ltree;
	std::ofstream out("data.out");
	for (;!ltree.empty();ltree.pop()) out << ltree.top() << " ";
	out << std::endl;
	ltree_.push(-1) , ltree_.push(15) , ltree_.push(33) , ltree__.join(ltree_);
	for (;!ltree__.empty();ltree__.pop()) out << ltree__.top() << " ";
	out << std::endl;
	for (int i = 0;i < 30;++ i) ltree.push(rand() % 1000);
	for (;!ltree.empty();ltree.pop()) out << ltree.top() << " ";
	out << std::endl;
	out.close();*/

	AVLTree<int , int , std::greater<int> > bst;Array<int> list;
	std::ifstream in("data.in");
	for (int x;in >> x;) list.push_back(x);
	in.close();
	std::ofstream out("data.out");
	std::random_shuffle(list.begin() , list.end());
	for (auto x : list) out << x << " ";
	out << std::endl;
	for (Array<int>::const_iterator it = list.cbegin();it != list.cend();++ it) bst.insert(*it , *it);
	AVLTree<int , int , std::greater<int> > c_bst(bst);
	for (AVLTree<int , int , std::greater<int> >::const_iterator it = c_bst.cbegin();it != c_bst.cend();++ it) out << *it << " ";
	bst.erase(12) , bst.erase(15) , bst.erase(20) , bst.erase(69) , bst.erase(70);
	for (AVLTree<int , int , std::greater<int> >::const_iterator it = bst.cbegin();it != bst.cend();++ it) out << *it << " ";
	out << std::endl;
	return 0;
}