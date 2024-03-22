#pragma once
#include "nodeToCity.h"
class Vertex;
class nodeQueue
{
	Vertex* current;
	nodeQueue* next;
	friend class PriorityList;
public:
	nodeQueue(Vertex* node);
	Vertex* getNode();
};

inline nodeQueue::nodeQueue(Vertex* node):current{node}, next{nullptr}
{
}

inline Vertex* nodeQueue::getNode()
{
	return current;
}
 