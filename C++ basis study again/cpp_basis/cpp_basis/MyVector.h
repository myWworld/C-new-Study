#pragma once
#include <iostream>
#include <string>

class Vector
{
	std::string* data;
	int capacity;
	int length;

public:

	Vector(int n = 1);

	void push_back(std::string s);
	
	std::string operator[](const int i);

	void remove(int x);

	int size() { return length; };
	
	~Vector();
};