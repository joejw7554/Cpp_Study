#include "CArr.h"
#include "assert.h"
#include "iostream"

using namespace std;
void CArr::Resize(int _iResizeCount)
{
	//Exceptional case
	if (_iResizeCount <= m_iMaxCount)
	{
		assert(nullptr);
	}

	int* NewArr = new int[_iResizeCount];

	for (int i = 0; i < m_iCount; ++i)
	{
		NewArr[i] = m_pData[i];
	}

	delete[] m_pData;

	m_pData = NewArr;

	m_iMaxCount = _iResizeCount;
}

void CArr::PushBack(T& _Data)
{
	if (m_iMaxCount <= m_iCount)
	{
		Resize(m_iMaxCount * 2);
	}
	m_pData[m_iCount++] = _Data;
}

void CArr::Display(int ArrIndex)
{
	cout << m_pData[ArrIndex] << endl;
}

int& CArr::operator[](int idx)
{
	return *(m_pData + idx);
}

CArr::CArr() : m_pData(nullptr), m_iCount(0), m_iMaxCount(2)
{
	m_pData = new int[2]; //컴파일러에게 판단의 근거 를 주기 위해- >자료데이터형* 변수명 = new 자료데이터형 이렇게 C++ 에서 변경된것이다
}

CArr::~CArr()
{
	delete[] m_pData;
}
