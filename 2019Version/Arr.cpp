#include "Arr.h"
#include <iostream>

void InitArr(MYST* _pArr)
{
	_pArr->pInt = (int*)malloc(sizeof(int) * 2);
	_pArr->iCount = 0;
	_pArr->iMaxCount = 2;
}

void PushBack(MYST* _pArr, int Data)
{
	if (_pArr->iMaxCount <= _pArr->iCount)
	{
		Reallocate(_pArr);
	}
	_pArr->pInt[_pArr->iCount++] = Data;
}

void Reallocate(MYST* _pArr)
{
	int* New_pArr = (int*)malloc(_pArr->iMaxCount * 2 * sizeof(int));

	for (int i = 0; i < _pArr->iMaxCount; ++i)
	{
		New_pArr[i] = _pArr->pInt[i];
	}

	free(_pArr->pInt);

	_pArr->pInt = New_pArr;

	_pArr->iMaxCount *= 2;
}





void ReleaseArr(MYST* _pArr)
{
	free(_pArr->pInt);
	_pArr->iCount = 0;
	_pArr->iMaxCount = 0;
}