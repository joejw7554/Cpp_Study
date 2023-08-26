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

	CBST<int, int>::iterator Iter = bstint.begin();
	Iter = bstint.find(150);


	(*Iter).first;

	Iter->second;
	

	

	/*


	Iter->first;

	(*Iter).second;
	Iter->second;


	for (Iter = bstint.begin(); Iter != bstint.end(); ++Iter)
	{
		cout << Iter->first << "	" << Iter->second << endl;
	}*/

	return 0;
}