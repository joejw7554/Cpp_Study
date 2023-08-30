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
	bstint.insert(make_bstpair(25, 0));
	bstint.insert(make_bstpair(75, 0));
	bstint.insert(make_bstpair(125, 0));
	bstint.insert(make_bstpair(175, 0));


	CBST<int, int>::iterator Iter = bstint.begin();
	Iter = bstint.find(150);
	Iter = bstint.erase(Iter);



	return 0;
}