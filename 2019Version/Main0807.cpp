#include "iostream"


using namespace std;
class CMy
{

private:
	int m_i;
	float m_f;

public:
	void SetInt(int i)
	{
		m_i = i;
	}

	int GetInt()
	{
		return m_i;
	}

	CMy& operator =(const CMy& _Other)
	{
		this->m_i = _Other.m_i;
		this->m_f = _Other.m_f;

		return *this;
	}

};


int main()
{
	CMy a;

	CMy b;

	a = b;

	return 0;

}