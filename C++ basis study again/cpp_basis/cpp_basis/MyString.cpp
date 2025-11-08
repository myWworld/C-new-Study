#pragma once

#include <cstdio>
#include <iostream>
#include <string.h>
#include <vector>


class MyString
{
	char* string_content;
	int memory_capacity;
	int len;

public:

	MyString(const char* name);
	MyString(char c);


	explicit MyString(int capacity) :memory_capacity(capacity) , string_content(nullptr), len(capacity){}
	MyString(const MyString& s);

	~MyString();

	int length() const
	{
		return len;
	}

	int capacity() const { return memory_capacity; }

	void print();
	void println();

	MyString& assign(const MyString& str);
	MyString& assign(const char* str);
	
	void reserve(int size);
	char at(int i);

	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, const char c);

	MyString& erase(int loc, int num);

	int find(int find_from, MyString& str) const;
	int find(int find_from, const char* str) const;
	int find(int find_from, char c) const;

	int compare(const MyString& str);

	void strcat(const MyString& s);
	bool strsame(const MyString& s);
	bool strcmp(const MyString& s);

	bool operator== (const MyString& s)
	{
		return !compare(s);
	}

	MyString& operator=(const MyString& s)
	{
		return assign(s);
	}

	char& operator[](const int index)
	{
		return string_content[index];
	}

	MyString operator+(const MyString& s)
	{
		int loc = len;

		char* newChar = new char[len + s.len + 1];
		int newLen = len + s.len;

		for (int i = 0; i < newLen; i++)
		{
			if (i < len)
			{
				newChar[i] = string_content[i];
			}
			else
			{
				newChar[i] = s.string_content[i - len];
			}
		}

		newChar[newLen] = '\0';

		MyString temp(newChar);
		return temp;
	}


private :

	std::vector<int> getPi(const MyString& s) const
	{
		int m = s.len;
		int j = 0;

		std::vector<int> pi(m, 0);
		
		for (int i = 1; i < m; i++)
		{
			while (j > 0 && s.string_content[i] != s.string_content[j])
				j = pi[j - 1];
			
			if (s.string_content[i] == s.string_content[j])
				pi[i] = ++j;
		}

		return pi;
	}

public:

	bool kmp( MyString& p) const
	{
		std::vector<int> ans;

		auto pi = getPi(p);
		
		int n = len;
		int m = p.len;
		int j = 0;

		for (int i = 0; i < n; i++)
		{
			while (j > 0 && string_content[i] != p.string_content[j])
				j = pi[j - 1];

			if (string_content[i] == p.string_content[j])
			{
				if (j == m - 1)
				{
					return true;
				}
				else
				{
					j++;
				}
			}
		}

		return false;
	}
};

//int main()
//{
//	MyString str1("i am ii");
//	MyString str2(" james");
//
//	std::cout << str1[2];
//
//	str1[2] = 'v';
//
//
//	std::cout << str1[2];
//
//
//	return 0;
//}


MyString::MyString(const char* name)
{
	len = strlen(name);
	string_content = new char[len];
	memory_capacity = len;
	
	for (int i = 0; i < len; i++)
	{
		string_content[i] = name[i];
	}
}

MyString::MyString(char c)
{
	string_content = new char[1];
	len = 1;
	memory_capacity = 1;
	string_content[0] = c;
}

MyString::MyString(const MyString& s)
{
	len = s.len;
	string_content = new char[s.len];
	memory_capacity = s.memory_capacity;

	for (int i = 0; i < len; i++)
	{
		string_content[i] = s.string_content[i];
	}
}

MyString::~MyString()
{
	if (string_content)
		delete[] string_content;
}

void MyString::print()
{
	for (int i = 0; i < len; i++)
	{
		std::cout << string_content[i];
	}
}

void MyString::println()
{
	for (int i = 0; i < len; i++)
	{
		std::cout << string_content[i];
	}

	std::cout << std::endl;
}

MyString& MyString::assign(const MyString& str)
{
	len = str.len;

	if (len > memory_capacity)
	{
		delete[] string_content;
		memory_capacity = len;
	}
	string_content = new char[str.len];


	for (int i = 0; i < i != str.len; i++)
	{
		string_content[i] = str.string_content[i];
	}
	return *this;
}

MyString& MyString::assign(const char* str)
{
	len = strlen(str);

	if (len > memory_capacity)
	{
		delete[] string_content;
		memory_capacity = len;
	}

	string_content = new char[strlen(str)];

	for (int i = 0; i != len; i++)
	{
		string_content[i] = str[i];
	}

	return *this;
}

void MyString::reserve(int size)
{
	if (size > memory_capacity)
	{
		char* prev_cont = string_content;

		string_content = new char[size];
		memory_capacity = size;

		for (int i = 0; i != len; i++)
		{
			string_content[i] = prev_cont[i];
		}

		delete[] prev_cont;
	}
}

char MyString::at(int i)
{
	if (i >= len || i < 0)
		return NULL;
	else
		string_content[i];
}

MyString& MyString::insert(int loc, const MyString& str)
{
	if (loc > len || loc < 0)
		return *this;

	if (len + str.len > memory_capacity)
	{
		
		if (memory_capacity * 2 > len + str.len)
			memory_capacity *= 2;
		else
		{
			memory_capacity = len + str.len;
		}

		char* prev_str = string_content;
		
		string_content = new char[memory_capacity];

		int i;
		for (i = 0; i < loc; i++)
		{
			string_content[i] = prev_str[i];
		}

		for (int j = 0; j < str.len; j++)
		{
			string_content[i + j] = str.string_content[j];
		}

		for (; i < len; i++)
		{
			string_content[i + str.len] = prev_str[i];
		}


		delete[] prev_str;

		len = len + str.len;
		return *this;
		
	}

	for (int i = len - 1; i >= loc; i--)
	{
		string_content[i + str.len] = string_content[i];
	}

	for (int i = 0; i < loc; i++)
	{
		string_content[i + loc] = string_content[i];
	}

	len = str.len + len;
	return *this;
}

MyString& MyString::insert(int loc, const char* str)
{
	MyString temp(str);
	return insert(loc, temp);
}

MyString& MyString::insert(int loc, const char c)
{
	MyString temp(c);
	return insert(loc, temp);
}

MyString& MyString::erase(int loc, int num)
{
	if (loc >= len || loc < 0 || num < 0)
		return *this;

	if (num > len)
		num = len;

	for (int i = loc + num; i < len; i++)
	{
		string_content[i - num] = string_content[i];
	}
	len -= num;
	return *this;
}

int MyString::find(int find_from, MyString& str) const
{
	if (kmp(str) == true)
	{
		return 1;
	}

	return -1;
}

int MyString::find(int find_from, const char* str) const
{
	MyString temp(str);
	return find(find_from, temp);
}

int MyString::find(int find_from, char c) const
{
	MyString temp(c);
	return find(find_from, temp);
}

int MyString::compare(const MyString& str)
{
	for (int i = 0; i < std::min(len,str.len); i++)
	{
		if (string_content[i] > str.string_content[i])
			return 1;
		else if(string_content[i] < str.string_content[i])
			return -1;
	}

	if (len == str.len) return 0;
	else if (len > str.len) return 1;

	return -1;
}


void MyString::strcat(const MyString& s)
{
	int otherLen = s.len;
	int newLen = len + otherLen;
	
	char* prevStr = string_content;

	if (newLen > memory_capacity)
	{
		string_content = new char[newLen];
		memory_capacity = newLen;

	}

	for (int i = 0; i < len; i++)
	{
		
		
			string_content[i] = prevStr[i];
		
	}

	for (int i = 0; i < otherLen; i++)
	{


		string_content[len + i] = s.string_content[i];

	}


	len = newLen;


	delete[] prevStr;
}

bool MyString::strsame(const MyString& s)
{
	return false;
}

bool MyString::strcmp(const MyString& s)
{
	return false;
}
