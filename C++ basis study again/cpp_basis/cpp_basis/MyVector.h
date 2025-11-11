

#include <iostream>
#include <string>
#include <array>

template<typename T>
class Vector
{
	T* data;
	int capacity;
	int length;

public:

	typedef T value_type;

	Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

	void push_back(T s)
	{
		if (capacity <= length)
		{
			T* temp = new T[capacity * 2];

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

	T operator[](const int i)
	{
		return data[i];
	}

	void remove(int x)
	{
		for (int i = x + 1; i < length; i++)
		{
			data[i - 1] = data[i];
		}
		length--;
	}

	int size() { return length; }


	void swap(int i, int j)
	{
		if (data)
		{
			T temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
	}


	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}
};

template<>
class Vector<bool>
{
	unsigned int* data;
	int capacity;
	int length;

public:

	typedef bool value_type;

	Vector(int n = 1) : data(new unsigned int[n / 32 + 1]), capacity(n /32 + 1), length(0) 
	{
		for (int i = 0; i < capacity; i++)
		{
			data[i] = 0;
		}
	}

	void push_back(bool s)
	{
		if (capacity * 32 <= length)
		{
			unsigned int* temp = new unsigned int[capacity * 2];

			for (int i = 0; i < capacity; i++)
			{
				temp[i] = data[i];
			}

			for (int i = capacity; i < capacity * 2; i++)
			{
				temp[i] = 0;
			}

			delete[] data;
			data = temp;

			capacity *= 2;
		}

		if (s)
		{
			data[length / 32] |= (1 << (length & 32));
		}

		length++;
	}

	bool operator[](const int i)
	{
		return (data[i / 32] & (1 << (i % 32))) != 0 ;
	}

	void remove(int x)
	{
		for (int i = x + 1; i < length; i++)
		{
			int prev = i - 1;
			int curr = i;

			if (data[curr / 32] & (1 << (curr % 32)))
			{
				data[prev / 32] |= (1 << (prev % 32));
			}
			else
			{
				unsigned int all_ones_except_prev = 0xFFFFFFFF;
				all_ones_except_prev ^= (1 << (prev % 32));
				data[prev / 32] &= all_ones_except_prev;
			}
		}
		length--;
	}

	int size() { return length; }

	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}
};

template<typename T>
T max(T& a, T& b)
{
	return a > b ? a : b;
}

template<typename Cont>
void bubble_sort(Cont& cont)
{
	for (int i = 0; i < cont.size(); i++)
	{
		for (int j = i + 1; j < cont.size(); j++)
		{
			if (cont[i] > cont[j])
			{
				cont.swap(i, j);
			}
		}
	}
}

template<typename Cont, typename Comp>
void bubble_sort(Cont& cont, Comp& comp)
{
	for (int i = 0; i < cont.size(); i++)
	{
		for (int j = i + 1; j < cont.size(); j++)
		{
			if (!comp(cont[i] , cont[j]))
			{
				cont.swap(i, j);
			}
		}
	}
}

struct Comp1
{
	bool operator()(int a, int b) { return a > b; }
};

struct Comp2
{
	bool operator()(int a, int b) { return a < b; }
};

template<typename T, int a = 8>
T add_num(T t)
{
	return t + a;
}


int main()
{
	int a = 9;
	std::cout <<  add_num<int, 5>(a);
	std::cout << add_num<int>(a);



}
