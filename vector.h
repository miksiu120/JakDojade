#pragma once
#include <iostream>

constexpr int BEGIN_SIZE = 64;

template<typename T>
struct Vector {

	T* vector = new T[BEGIN_SIZE];
	int actualSizeOfArray = BEGIN_SIZE;

	int size = 0;

	Vector() { };
	~Vector()
	{
		delete vector;
	}
	void extendArray()
	{
		actualSizeOfArray *= 2;
		T* copyvector = new T[actualSizeOfArray];

		for (int i = 0; i < actualSizeOfArray - actualSizeOfArray/2; i++)
		{
			copyvector[i] = vector[i];
		}
		delete[]vector;
		vector = copyvector;

	}

	T& operator[](int index)
	{
		return vector[index];
	}

	void pushBack(T newElement)
	{

		if (actualSizeOfArray == size )
		{
			extendArray();
		}
		vector[size] = newElement;
		size++;
	}
	void erase(T toErase)
	{
		for (int i = 0; i < actualSizeOfArray; i++)
		{

			if (vector[i] == toErase)
			{

				T* copy = new T[actualSizeOfArray];

				int remove = 0;
				for (int j = 0; j < size; j++)
				{
					if (j == i)
					{
						remove--;
						continue;
					}

					copy[j + remove] = vector[j];
				}
				delete[] vector;
				vector = copy;
				size--;

				return;
			}
		}
	}
	bool find(T searchedElement)
	{
		for (int i = 0; i <size; i++)
		{
			if (vector[i] == searchedElement)
				return true;
		}
		return false;
	}
	void reset()
	{
		delete[] vector;
		actualSizeOfArray = 512;
		vector = new T[512];
		size = 0;
	}
	void deleteArray()
	{
		delete[] vector;
		
	}
};