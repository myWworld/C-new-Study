#include <cstdio>
#include <iostream>
#include <string>


class Array;
class Int;
class Iterator;

class Array
{
	friend Int;

	const int dim;
	int* size;

	struct Address
	{
		int level;
		void* next;
	};

	Address* top;

public:

	class Iterator
	{
		int* location;
		Array* arr;

		friend Int;


	public:

		Iterator (Array *_arr, int* _location = NULL) :arr(_arr), location(_location)
		{
			location = new int[_arr->dim];
			for (int i = 0; i < _arr->dim; i++)
			{
				location[i] = (_location != NULL ? _location[i] : 0);
			}
		}

		Iterator(const Iterator& itr) : arr(itr.arr)
		{
			location = new int[arr->dim];
			for (int i = 0; i < arr->dim; i++)
			{
				location[i] = itr.location[i];
			}
		}

		~Iterator()
		{
			delete[] location;
		}


		Iterator& operator++()
		{
			if (location[0] >= arr->size[0])
				return *this;

			bool carry = false;

			int i = arr->dim - 1;

			do {

				location[i]++;

				if (location[i] >= arr->size[i] && i >= 1)
				{
					location[i] -= arr->size[i];
					carry = true;
					i--;
				}
				else
					carry = false;



			} while (i >= 0 && carry);


			return *this;
		}

		Iterator& operator++(int)
		{
			if (location[0] >= arr->size[0])
				return *this;

			Iterator itr(*this);
			++(*this);
			return itr;

		}

		Iterator& operator=(const Iterator& itr)
		{
			arr = itr.arr;
			location = new int[itr.arr->dim];

			for (int i = 0; i < itr.arr->dim; i++)
			{
				location[i] = itr.location[i];
			}
			return (*this);
		}

		bool operator!=(const Iterator& itr)
		{
			if (itr.arr->dim != arr->dim) return true;

			for (int i = 0; i < arr->dim; i++)
			{
				if (itr.location[i] != location[i])
					return true;
			}

			return false;
		}

		bool operator==(const Iterator& itr)
		{
			if (itr.arr->dim != arr->dim) return false;

			for (int i = 0; i < arr->dim; i++)
			{
				if (itr.location[i] != location[i])
					return false;
			}

			return true;
		}

		Int operator*();
	};

	friend Iterator;


	Array(int dim, int* array_size) :dim(dim)
	{
		size = new int[dim];

		for (int i = 0; i < dim; i++)
		{
			size[i] = array_size[i];
		}

		top = new Address;
		top->level = 0;
		initialize_address(top);
	}

	Array(const Array& arr) :dim(arr.dim)
	{
		size = new int[dim];
		for (int i = 0; i < dim; i++)
		{
			size[i] = arr.size[i];
		}

		top = new Address;
		top->level = 0;

		initialize_address(top);
	}

	~Array()
	{
		delete_address(top);
		delete[] size;
	}


	void initialize_address(Address* current)
	{
		if (!current) return;

		if (current->level == dim - 1)
		{
			current->next = new int[size[current->level]];
			return;
		}

		current->next = new Address[size[current->level]];
		
		for (int i = 0; i < size[current->level]; i++)
		{
			(static_cast<Address*>(current->next) + i)->level = current->level + 1;
			initialize_address(static_cast<Address*>(current->next) + i);
		}
	}

	void delete_address(Address* current)
	{
		if (!current) return;


		for (int i = 0; current->level < dim -1 && i <size[current->level]; i++)
		{
			delete_address(static_cast<Address*>(current->next) + i);
		}

		delete[] current->next;
	}

	Iterator begin()
	{
		int* arr = new int[dim];
		for (int i = 0; i < dim; i++)
		{
			arr[i] = 0;
		}

		Iterator temp(this, arr);
		delete[] arr;
		return temp;
	}

	Iterator end()
	{
		int* arr = new int[dim];
		arr[0] = size[0];

		for (int i = 1; i < dim; i++)
		{
			arr[i] = 0;
		}

		Iterator temp(this, arr);
		delete[] arr;
		return temp;
	}

	Int operator[](const int index);
	
};


class Int
{
	void* data;

	int level;
	Array* array;

public:

	

	Int(int index, int _level = 0, void* _data = NULL, Array* array = NULL)
		:level(_level), data(_data), array(array)
	{
		if (_level < 1 || index >= array->size[_level - 1])
		{
			data = NULL;
			return;
		}

		if (level == array->dim)
		{
			data = static_cast<void*>(static_cast<int*>(static_cast<Array::Address*>(data)->next) + index);
		}
		else
		{
			data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next) + index);
		}

	}

	Int& operator=(const int& a)
	{
		if (data) *static_cast<int*> (data) = a;
		return *this;
	}

	Int operator[](const int index)
	{
		if (!data) return 0;
		return Int(index, level + 1, data, array);
	}

	operator int()
	{
		if (data) return *static_cast<int*>(data);
		return 0;
	}

};

Int Array::operator[](const int index)
{
	return Int(index, 1, static_cast<void*>(top), this);
}



Int Array::Iterator::operator*()
{
	Int start = arr->operator[](location[0]);
	for (int i = 1; i < arr->dim; i++)
	{
		start = start.operator[](location[i]);
		
	}

	return start;
}


//int main()
//{
//
//	int size[] = { 2,3,4 };
//
//	Array arr(3, size);
//
//	Array::Iterator itr = arr.begin();
//
//	for (int i = 0; itr != arr.end(); itr++, i++)
//	{
//		(*itr) = i;
//	}
//	for (itr = arr.begin(); itr != arr.end(); itr++)
//	{
//		std::cout << *itr << std::endl;
//	}
//	for (int i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			for (int k = 0; k < 4; k++)
//			{
//				arr[i][j][k] = (i + 1) * (j + 1) * (k + 1) + arr[i][j][k];
//			}
//		}
//	}
//
//	for (int i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			for (int k = 0; k < 4; k++)
//			{
//				std::cout << i << " " << j << " " << k << " " << arr[i][j][k] << std::endl;
//			}
//		}
//	}
//
//	return 0;
//}