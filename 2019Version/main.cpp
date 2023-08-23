#include <iostream>
#include "Arr.h"

using namespace std;


int main()
{
 	MYST s{};

	InitArr(&s);

	for (int i = 0; i < 10; i++)
	{
		PushBack(&s, i);
	}

 	ReleaseArr(&s);

	return 0;
}
