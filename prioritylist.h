#pragma once
#include "nodeList.h"
#include <iostream>

class PriorityList
{
	nodeQueue* first;
	int size = 0;

public:
	PriorityList();
	void push(Vertex* );
	void showList();
	int getSize();
	bool isEmpty();
	Vertex* front();
	void pop();
};

