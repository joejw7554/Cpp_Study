#pragma once

typedef struct MyStruct
{
	int* PtrInt;
	int CurrentSize;
	int MaxSize;
}MyStruct;


void ArrInit(MyStruct* Mystruct, int size);

void AddData(MyStruct* Mystruct, int Data);

void ArrRelease(MyStruct* Mystruct);

void AscendingOrderSort(MyStruct* Mystruct, void (*SortFunc)(int*, int));

void DescendingOrderSort(MyStruct* Mystruct);

void Sort(MyStruct* Mystruct, void(*SortFunc)(int*, int));