#include "DArr.h"
#include "iostream"

//Func ptr
//testing Sort using Func ptr
//Dyanamic Array allocation

void ArrInit(MyStruct* Mystruct, int size)
{
	Mystruct->PtrInt = (int*)malloc(size * sizeof(int));
	Mystruct->CurrentSize = 0;
	Mystruct->MaxSize = size;
}

void ReAlocate(MyStruct* Mystruct)
{
	int* NewArray = (int*)malloc(Mystruct->CurrentSize * 2 * sizeof(int));

	for (int i = 0; i < Mystruct->CurrentSize; ++i)
	{
		NewArray[i] = Mystruct->PtrInt[i];
	}

	free(Mystruct->PtrInt);

	Mystruct->PtrInt = NewArray;
}

void AddData(MyStruct* Mystruct, int Data)
{
	if (Mystruct->CurrentSize >= Mystruct->MaxSize)
	{
		ReAlocate(Mystruct);
	}

	Mystruct->PtrInt[Mystruct->CurrentSize++] = Data;
}

void AscendingOrderSort(MyStruct* Mystruct, void (*SortFunc)(int*, int))
{
	SortFunc(Mystruct->PtrInt, Mystruct->CurrentSize);

	if (Mystruct->CurrentSize <= 1)
		return;


	while (true)
	{
		bool bFinish = true;
		for (int j = 0; j < Mystruct->CurrentSize - 1; ++j)
		{
			if (Mystruct->PtrInt[j] > Mystruct->PtrInt[j + 1])
			{
				int Temp = Mystruct->PtrInt[j + 1];
				Mystruct->PtrInt[j + 1] = Mystruct->PtrInt[j];
				Mystruct->PtrInt[j] = Temp;
				bFinish = false;
			}
		}

		if (bFinish)
			break;
	}
}

void DescendingOrderSort(MyStruct* Mystruct)
{
	if (Mystruct->CurrentSize <= 1)
		return;

	for (int i = 0; i < Mystruct->CurrentSize - 1; ++i)
	{
		for (int j = 0; j < Mystruct->CurrentSize - 1; ++j)
		{
			if (Mystruct->PtrInt[j] < Mystruct->PtrInt[j + 1])
			{
				int Temp = Mystruct->PtrInt[j];
				Mystruct->PtrInt[j] = Mystruct->PtrInt[j + 1];
				Mystruct->PtrInt[j + 1] = Temp;
			}
		}
	}
}

void Sort(MyStruct* Mystruct, void(*SortFunc)(int*, int))
{
	SortFunc(Mystruct->PtrInt, Mystruct->CurrentSize);
}

void ArrRelease(MyStruct* Mystruct)
{
	free(Mystruct->PtrInt);
	Mystruct->CurrentSize = 0;
	Mystruct->MaxSize = 0;
}

