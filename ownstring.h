#pragma once
#include <iostream>

class ownString {

	 char *word = nullptr;
	 int size = 0;
public:
	ownString();
	ownString(const char *);
	ownString(const ownString&);
	ownString(const char&&);
	ownString(const char&);
	char& operator[](int index);
	ownString operator=(const ownString&);
	void operator=(const char*);
	ownString operator=(const char&) ;
	ownString operator=(char&&);
	bool operator==(ownString&);
	void addCharPointer(char* );
	bool operator==(const char*);
	bool operator!=(const char*);
	ownString operator+(const char&);
	ownString addFromLeft(const char&);
	int length() const;
	void substring(int,int, ownString*);
	int  find(char);
	int count(char);
	char getChar(int);
	void erase(int,int );
	void writeSpecialChar(const char*);
	int toInt();
	int getCharIndex(int);
	friend class attributesList;

	friend const int sizeOfCharArray(const char*);
	friend std::ostream& operator<< (std::ostream& stream, const ownString&);


	~ownString();


};