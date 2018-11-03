#include <iostream>
#include "vector.h"

int main() 
{
	vector<int> a;

	for(int i=0;i<20;i++)
		a.push_back(i);
	a.pop_back();
	a[4] = 7777;
	a.front()= 5;
	a.back() = 565246;
	a.capacity();
	std::cout << a.front() << std::endl;
	std::cout << a.back() << std::endl;

	vector<int>::iterator it = a.end();
	a.erase(--it);
	a.erase();

	for (auto i : a)
		std::cout << i << " ";

	getchar();
	return 0;
}