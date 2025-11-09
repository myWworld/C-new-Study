#include "MyVector.h"

Vector::Vector(int n) : data(new std::string[n]), capacity(n), length(0)
{

}

void Vector::push_back(std::string& s)
{
	if (capacity <= length)
	{
		std::string* temp = new std::string[capacity * 2];

		for (int i = 0; i < length; i++)
		{
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;

		capacity *= 2;
	}

	data[length++] = s;
}

std::string Vector::operator[](const int i)
{
	return data[i];
}

void Vector::remove(int x)
{
	for (int i = x + 1; i < length; i++)
	{
		data[i - 1] = data[i];
	}
	length--;
}



Vector::~Vector()
{
	if (data)
	{
		delete[] data;
	}
}
