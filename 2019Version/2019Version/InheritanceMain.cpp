#include "iostream"

	using std::cout;
	using std::endl;
class A
{
	int intVar;
public:
	A():intVar()
	{
	}

	A(int _intVar) :intVar(_intVar)
	{
	}
	~A()
	{
	}

	virtual void Greet()
	{
	}
};

class B: public A
{
	float floatVar;

public:
	B() :floatVar()
	{

	}
	B(float _floatVar, int _intVar) :floatVar(_floatVar), A(_intVar)
	{
	}
	~B()
	{
	}

	 virtual void Greet() override
	{
		cout << "Hello I'm child class" << endl;
	}
};

int main()
{
	A AClass;
	B BClass;

	A* ClassPtr= &BClass;

	ClassPtr->Greet();
}