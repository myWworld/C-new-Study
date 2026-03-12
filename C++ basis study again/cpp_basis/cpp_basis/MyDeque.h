#include<iostream>
#include<string>
#include<set>
#include <map>
#include <unordered_set>
#include<algorithm>
#include <functional>
#include <cctype>

using namespace std; 

template<typename T>
class Vector
{
	T* data;
	size_t size;

public:

	Vector( size_t size) : size(size)
	{
		data = new T[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = 3;
		}
	}

	const T& at(const size_t idx) const
	{
		if (idx >= size)
		{
			throw out_of_range("vector의 index가 범위를 초과했습니다,");
		}
		else
		{
			return data[idx];
		}
	}

	~Vector()
	{
		if (data) delete[] data;
	}
};

class Resource
{
public:

	Resource(int id) : id(id) {}
	~Resource() { cout << "리소스 해제: " << id << endl; }


private: 
	int id;
};


int func3()
{
	Resource r(3);
	throw runtime_error("Exception from 3\n");
}

int func2()
{
	Resource r(2);
	func3();
	cout << "실행 안됨!" << endl;

	return 0;
}

int func1()
{
	Resource r(1);
	func2();
	cout << "실행 안됨!" << endl;

	return 0;
}



//int main()
//{
//	
//	try
//	{
//		func1();
//	}
//	catch (exception& e)
//	{
//		cout << "Exception : " << e.what();
//	}
//
//
//	return 0;
//}