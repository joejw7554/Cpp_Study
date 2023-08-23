#include "iostream"
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::list;

int main()
{
	vector<int> VecInt;
	list<int> ListInt;

	ListInt.push_back(10);
	ListInt.push_back(200);


	list<int>::iterator iterList = ListInt.begin();
	vector<int>::iterator iterVec = VecInt.begin();

	int iData = *iterList;
	iterList++;

	iData = *iterList;
	return 0;
}