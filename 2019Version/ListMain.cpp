#include <iostream>
#include "Clist.h"
#include <list>

using std::cout;
using std::list;
using std::endl;

int main()
{
	list<int> myList;

	myList.push_back(100);
	myList.push_back(200);
	myList.push_back(300);

	list<int>::iterator myIter = myList.begin();

	myList.erase(myList.begin(), myIter);


	for (myIter = myList.begin(); myIter != myList.end(); ++myIter)
	{
		cout << *myIter << endl;
	}




	/*CList<int> Clist;
	Clist.push_back(100);
	Clist.push_back(300);
	Clist.push_back(400);

	CList<int>::iterator ListIter = Clist.begin();
	++ListIter;

	ListIter = Clist.insert(ListIter, 200);

	for (ListIter=Clist.begin(); ListIter != Clist.end(); ++ListIter)
	{
		cout << *ListIter << endl;
	}*/

	return 0;
}