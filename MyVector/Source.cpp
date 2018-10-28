#include <iostream>
#include "vector.h"

int main() 
{
	vector<int> a;

	for(int i=0;i<20;i++)
		a.push_back(i);

	vector<int>::iterator it = a.begin();
	a.erase(++it);

	for (auto i : a)
		std::cout << i << " ";

	getchar();
	return 0;
}