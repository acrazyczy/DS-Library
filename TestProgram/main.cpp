#include "Array.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>

void search(Array<int> &list , int x , std::ofstream &out)
{
	Array<int>::iterator it = list.find(x);
	if (it == list.end()) out << x << " not found." << std::endl;
	else
	{
		out << x << " found: " << *it << std::endl;
		it = list.erase(it);
		out << "fellow: " << *it << std::endl;
		for (auto x : list) out << x << " ";
		out << std::endl;
	}
}

int main()
{
	Array<int> list;
	std::ifstream in("data.in");
	for (int x;in >> x;) list.push_back(x);
	in.close();
	const Array<int> const_list(list);
	std::sort(list.begin() , list.end() , std::greater<int>());
	std::ofstream out("data.out");
	for (auto x : list) out << x << " ";
	out << std::endl;
	for (Array<int>::iterator it = list.begin();it != list.end();++ it) out << *it << " ";
	out << std::endl;
	for (Array<int>::const_iterator it = const_list.begin();it != const_list.end();++ it) out << *it << " ";
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
	search(list , 25 , out) , search(list , -25 , out);
	out.close();
	return 0;
}