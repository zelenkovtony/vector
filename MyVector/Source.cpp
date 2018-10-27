#include <iostream>
#include "vector.h"

int main() {
	vector<int> a;
	a.push_back(1);
	a.push_back(2);
	vector<int>::iterator it=a.begin();
	a.erase(it);

	getchar();
	return 0;
}