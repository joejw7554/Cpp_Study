// Practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "vector"
#include "TArray.h"

using std::cout;
using std::endl;
using std::vector;
int main()
{
	vector<int> myVector;

	for (int i = 0; i < 10; ++i)
	{
		myVector.push_back(i);
	}

	vector<int>::iterator myVectorIter= myVector.begin();

	myVectorIter = myVector.erase(myVectorIter, myVectorIter+1);

	/*for (myvectoriter; myvectoriter!=myvector.end(); ++myvectoriter)
	{
		cout<<*myvectoriter<<endl;
	}*/
	//cout << *myVectorIter << endl;

	//내가만든 벡터
	/*TArray<int> myArray;

	for (int i = 0; i < 10; ++i)
	{
		myArray.push_back(i);
	}
	
	TArray<int>::iterator myIter= myArray.begin();

	myIter=myArray.erase(myIter, myIter + 6);



	for (myIter=myArray.begin(); myIter != myArray.end(); ++myIter)
	{
		cout << *myIter << endl;
	}*/

	int a = 30;
	

	return 0;
}
