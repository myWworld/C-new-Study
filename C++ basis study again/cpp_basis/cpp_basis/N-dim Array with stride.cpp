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
	int* stride;
	int* datas;


public:

	struct Node
	{
		int level;
		int offset;
		Array* arr;

		Node(int level, int offset, Array* arr) :level(level), offset(offset), arr(arr) {}

		Node operator[](const int idx)
		{
			if (idx < 0 || idx >= arr->size[level]) return (*this);

			int noff = offset + idx * arr->stride[level];
			
			return Node(level + 1, noff, arr);
		}

		Node& operator=(const int& a)
		{
			arr->datas[offset] = a;
			return *this;
		}

		operator int()
		{
			if (level != arr->dim) return -1e9;

			return arr->datas[offset];
		}


	};

	

	Array(int dim, int* array_size) :dim(dim)
	{
		size = new int[dim];

		for (int i = 0; i < dim; i++)
		{
			size[i] = array_size[i];
		}

		initialize_address();
	}

	Array(const Array& arr) :dim(arr.dim)
	{
		size = new int[dim];
		for (int i = 0; i < dim; i++)
		{
			size[i] = arr.size[i];
		}

		initialize_address();
	}

	~Array()
	{
		delete[] size;
		delete[] stride;
		delete[] datas;
	}


	void initialize_address()
	{
		int total = 1;
		stride = new int[dim];
		for (int d = dim - 1; d >= 0; --d) 
		{
			stride[d] = total;
			total *= size[d];
		}

		datas = new int[total];

		for (int i = 0; i < total; i++)
		{
			datas[i] = 0;
		}
	}

	Node operator[](const int idx)
	{
		int off = idx * stride[0];
		return Node(1, off, this);
	}


};

//int main() {
//	int shape[] = { 2, 3, 4 };
//	Array A(3, shape);
//
//	for (int i = 0; i < 2; ++i)
//		for (int j = 0; j < 3; ++j)
//			for (int k = 0; k < 4; ++k)
//				A[i][j][k] = (i + 1) * (j + 1) * (k + 1);
//
//	for (int i = 0; i < 2; ++i)
//		for (int j = 0; j < 3; ++j)
//			for (int k = 0; k < 4; ++k)
//				std::cout << i << ' ' << j << ' ' << k << " = " << (int)A[i][j][k] << '\n';
//}
//
//


