
#include <iostream>
#include "LinkedList.h"
#include "DArr.h"
#include <time.h>

using namespace std;
void BubbleSort(int* _pData, int CurrentSize)
{
	if (CurrentSize <= 1)
		return;


	while (true)
	{
		bool bFinish = true;
		for (int j = 0; j < CurrentSize - 1; ++j)
		{
			if (_pData[j] > _pData[j + 1])
			{
				int Temp = _pData[j + 1];
				_pData[j + 1] = _pData[j];
				_pData[j] = Temp;
				bFinish = false;
			}
		}

		if (bFinish)
			break;
	}
}

int main()
{
	
	MyStruct s;

	int Input{};
	cout << "Enter the size you want to allocate on dynamic allocation.: ";
	scanf_s("%d", &Input);

	srand(time(nullptr));

	ArrInit(&s, Input);

	for (int i = 0; i < 10; i++)
	{
		int iRand= rand() % 100 + 1;
		AddData(&s, iRand);
	}

	for (int i = 0; i < s.CurrentSize; i++)
	{
		cout << s.PtrInt[i] << endl;
	}

	cout << "-------------------------------------------" << endl;

	Sort(&s, &BubbleSort);

	for (int i = 0; i < s.CurrentSize; i++)
	{
		cout << s.PtrInt[i] << endl;
	}

	/*cout << "\n\n\n";

	DescendingOrder(&s);
	for (int i = 0; i < s.CurrentSize; i++)
	{
		cout << s.PtrInt[i] << endl;
	}*/

	ArrRelease(&s);
}