#include <iostream>
#include <map>
#include <set>
#include <string>
#include "CBST.h"

using namespace std;
enum myEnum
{
	Type1,
	Type2,
	Type3,
};

enum class OTHER_TYPE
{
	Type1,
	Type2,
	Type3
};

int main()
{ 
	CBST<int, int> bstint;
	tPair<int, int> pair;
	pair.first = 100;
	bstint.Insert(pair);

	pair.first = 150;
	bstint.Insert(pair);

	pair.first = 50;
	bstint.Insert(pair);

	return 0;
}