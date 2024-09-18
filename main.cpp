#include<iostream>
#include"Vector.hpp"

using namespace std;
class Student
{
public:
	friend ostream& operator<<(ostream& os, Student& object)
	{
		os << object.age << " " << object.name << endl;
		return os;
	}
	Student()
	{
		age = 0;
		name = NULL;
	}
	Student(int age,const char* pname)
	{
		
		this->age = age;
		name = new char[strlen(pname)+1];
		strcpy_s(name, strlen(pname) + 1,pname);
	}
	void print()
	{
		cout << age << " " << name << endl;
	}
	~Student()
	{
		/*if (name) 
		{
			delete name;
		}*/
	}
private:
	int age;
	char *name;
};
int main()
{
	try
	{
		Vector<int> myvector(-10);
		for (int i = 0; i < myvector.getLength(); i++)
		{
			myvector[i] = i + 10;
		}
		cout << myvector << endl;
	}
	catch (errNegativeException &err)
	{
		cout << "errNegativeException..." << endl;
	}
	catch (errZeroException &err)
	{
		cout << "errZeroException..." << endl;
	}
	catch (errToolBigException &err)
	{
		cout << "errToolBigException..." << endl;
	}
	catch (errTooSmallException &err)
	{
		cout << "errTooSmallException..." << endl;
	}
	system("pause");
	return 0;
}