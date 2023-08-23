

typedef struct MyStruct
{
	int* pInt;
	int iCount;
	int iMaxCount;
}MYST;

void InitArr(MYST* _pMYST);
void PushBack(MYST* _pMYST, int Data);
void Reallocate(MYST* _pMYST);
void ReleaseArr(MYST* _pMYST);