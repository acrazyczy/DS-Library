#include "LeftistTree.h"
#include <algorithm>
#include <iostream>
#include <fstream>

/*void search(LinkedList<int> &list , int x , std::ofstream &out)
{
	LinkedList<int>::iterator it = list.find(x);
	if (it == list.end()) out << x << " not found." << std::endl;
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
	/*LinkedList<int> list;
	std::ifstream in("data.in");
	for (int x;in >> x;) list.push_back(x);
	in.close();
	const LinkedList<int> const_list(list);
	std::ofstream out("data.out");
	for (auto x : list) out << x << " ";
	out << std::endl;
	for (LinkedList<int>::iterator it = list.begin();it != list.end();++ it) out << *it << " ";
	out << std::endl;
	for (LinkedList<int>::const_iterator it = const_list.begin();it != const_list.end();++ it) out << *it << " ";
	out << std::endl;
	size_t cnt = const_list.size();
	for (size_t i = 0;i < cnt;++ i) out << const_list[i] << " ";
	out << std::endl;
	list.pop_back() , list.pop_front() , list.push_front(-1);
	for (LinkedList<int>::iterator it = list.begin();it != list.end();++ it) out << *it << " ";
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
	search(list , 3 , out) , search(list , -3 , out);
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

	LeftistTree<int> ltree , ltree_ , ltree__;
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
	for (int i = 0;i < 100000;++ i) ltree.push(i & 1 ? i : -i);
	for (;!ltree.empty();ltree.pop()) out << ltree.top() << " ";
	out << std::endl;
	out.close();
	return 0;
}