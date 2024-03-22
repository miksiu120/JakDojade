#include "ownString.h"
#include <iostream>
#include <string.h>
using namespace std;

const int sizeOfCharArray(const char *element)
{
	if (element == "" or element == nullptr )
	{
		return 0;
	}
	int sizeElement = 0;
	while (element[sizeElement] != '\0')
	{
		sizeElement++;
	}
	return sizeElement;
}

ownString::ownString() :word{ nullptr }, size{0}
{

}

ownString::ownString(const char* element) :word{ new char[sizeOfCharArray(element)+1] },
size{sizeOfCharArray(element)}
{
	strcpy_s(word, size+1, element);
}
ownString::ownString(const ownString& element)
{
	size = element.length();
	word = new char[size+1];
	strcpy_s(word, size + 1, element.word);
}

ownString::ownString(const char&& sign) {
	word = new char[2];
	word[0] = sign;
	word[1] = '\0';
}

ownString::ownString(const char& sign) {
	word = new char[2];
	word[0] = sign;
	word[1] = '\0';
}


int ownString::length() const
{
	return size;
}
void ownString::substring(int startIndex, int numToCut,ownString* destination)
{
	char* temp = new char[numToCut + 1];
	for (int i = startIndex; i < startIndex + numToCut; i++)
	{
		temp[i - startIndex] = word[i];
	}
	temp[numToCut] = '\0';
	*destination = temp;
	delete[] temp;
}


char& ownString::operator[](int index)
{
	
	return word[index];
}

ownString ownString::operator=(const ownString& compared)
{

	if (compared.word == nullptr or compared.word == "")
	{
		delete[]word;
		word = nullptr;
		return *this;
	}

	if(this != NULL and  word!=nullptr)
		delete[] word;

	
	word = new char[compared.size + 1];
	size = compared.size;
	strcpy_s(word, size + 1, compared.word);
	return *this;
}



void ownString::operator=(const char* compared)
{

	if (compared == nullptr or compared == "")
	{
		delete[]word;
		word = nullptr;
		return;
	}

	if (word != nullptr)
		delete[] word;

	int newSize = sizeOfCharArray(compared);
	word = new char[newSize + 1];
	size = newSize;
	strcpy_s(word, size + 1, compared);
	
}

ownString ownString::operator=(const char& sign)
{
	delete[] word;
	word = new char[2];
	word[0] = sign;
	word[1] = '\0';
	return *this;
}

ownString ownString::operator=(char&& sign)
{
	delete[] word;
	word = new char[2];
	word[0] = sign;
	word[1] = '\0';
	return *this;
}

ownString ownString::operator+(const char &sign) {

	char* temp = new char[size + 2];
	for (int i = 0; i < size; i++)
	{
		temp[i] = word[i];
	}
	temp[size] = sign;
	temp[size + 1] = '\0';
	size++;
	delete word;
	word = temp;

	return *this;
}

ownString ownString::addFromLeft(const char& sign) {

	char* temp = new char[size + 2];
	temp[0] = sign;
	for (int i = 1; i <= size; i++)
	{
		temp[i] = word[i-1];
	}
	temp[size + 1] = '\0';
	size++;
	delete word;
	word = temp;

	return *this;
}


bool ownString::operator==(ownString& compared)
{

	if (this == NULL)
	{
		return false;
	}

	if (size != compared.size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (word[i] != compared[i])
			{
				return false;
			}
		}
	}
	return true;
}

void ownString::addCharPointer(char* pointer)
{
	size = sizeOfCharArray(pointer);
	word = pointer;

}

bool ownString::operator==(const char* compared)
{
	if (size != sizeOfCharArray(compared))
	{
		
		return false;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (word[i] != compared[i])
			{
				return false;
			}
		}
	}
	
	return true;
}

bool ownString::operator!=(const char* compared)
{


	if (size != sizeOfCharArray(compared))
	{

		return true;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (word[i] != compared[i])
			{
				return true;
			}
		}
	}

	return false;
}


std::ostream& operator<< (std::ostream& stream, const ownString& element) {
	stream << element.word;
	return stream;
}


int ownString::getCharIndex(int element)
{
	for (int i = 0; i < length(); i++)
	{
		if (element == word[i])
		{
			return i;
		}
	}
	return -1;
}



ownString::~ownString() {
	if (word != nullptr)
		delete word;
}

int ownString::find(char letter) {
	
	
	for (int i = 0; i < size; i++)
	{
		if (word[i] == letter)
			return i;
	}
	return -1;
}

void ownString::erase(int firstIndex, int numOfElements)
{

	if (word == nullptr)
		return;


	char* newWord = new char[size]{};
	int newWordIndex = 0;
	for (int i = 0; i < size; i++)
	{
	
		if (i < firstIndex or i >= firstIndex + numOfElements)
		{
		
			newWord[newWordIndex++] = word[i];
		}
	}
	newWord[newWordIndex] = '\0';
	strcpy_s(word,newWordIndex + 1 ,newWord);
	size = sizeOfCharArray(word);
	delete[] newWord;
}

void ownString::writeSpecialChar(const char* compared)
{
	if (word != nullptr)
		delete[] word;

	int newSize = sizeOfCharArray(compared)-1;
	word = new char[newSize + 1];
	size = newSize;
	
	for (int i = 0; i < size; i++)
	{
		word[i] = compared[i];
	}
	word[size] = '\0';

}

int ownString::toInt()
{
	// return 0 when there is a letter or sth
	int number=0;
	int power = 0;
	for (int i = size - 1; i >= 0; i--)
	{
		int digit = word[i] - '0';

		if (digit > 9)
			return 0;
		number += digit*pow(10,power++);
		
	}
	return number;
}

int ownString::count(char letter)
{
	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		if (word[i] == letter)
			counter++;
	}
	return counter;
}

char ownString::getChar(int index)
{
	if (index < length())
		return word[index];
	else
		return -1;
}

