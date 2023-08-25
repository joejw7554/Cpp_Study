#include <iostream>
#include <map>
#include <set>
#include <string>
#include "CBST.h"

using namespace std;

int main()
{
	CBST<int, int> bstint;
	bstint.insert(make_bstpair(100, 0));
	bstint.insert(make_bstpair(150, 0));
	bstint.insert(make_bstpair(50, 0));

	CBST<int, int>::iterator bIter = bstint.begin();

	bIter = bstint.find(150);

	int a = 30;

	return 0;
}