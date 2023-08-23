#include "iostream"
#include "CArr.h"
#include <list>
#include <vector>

using std::vector;
using std::list;
using std::cout;
using std::endl;

int main()
{
	CArr<int> myVector;

	for (int i = 0; i < 5; ++i)
	{
		myVector.PushBack(i + 1);
	}
	CArr<int>::iterator myiter = myVector.begin();


	for (myiter;  myiter != myVector.end(); myiter++)
	{
    	if (0 == *myiter % 2)
		{
			myiter=myVector.erase(myiter);
		}
	}

	for (int i = 0; i < myVector.size(); i++)
	{
		cout << myVector[i] << endl;
	}



	return 0;
}