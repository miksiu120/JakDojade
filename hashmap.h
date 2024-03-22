#pragma once
#include "coords.h"
#include <cstring>
#include <iostream>
#include "city.h"
#include "ownstring.h"
#include "vertex.h"
using namespace std;

constexpr int TABLE_SIZE = 500000;

struct HashNode {
	Vertex* hashedVertex;
	HashNode* next;
	unsigned int key;
	HashNode(Vertex* val,unsigned int key)
		:hashedVertex{ val },next{nullptr}, key{key}
	{

	}
	HashNode(const HashNode& copied)
		:hashedVertex{ copied.hashedVertex }, next{ nullptr }, key{ copied.key }
	{

	}
	HashNode()
	{
		key = -1;
		hashedVertex = nullptr;
		next = nullptr;
	}

	~HashNode()
	{ 
		if (hashedVertex == nullptr);
			return;

		HashNode* current = this->next;
		while (current != nullptr) {
			HashNode* next = current->next;
			delete current;
			current = next;
		}	
	}

};

class HashMap
{

	const int CAPACITY;
	HashNode* hashArray;

public:
	HashMap():CAPACITY{ TABLE_SIZE },hashArray{ new HashNode[TABLE_SIZE] }
	{
	}

	~HashMap()
	{
		
		delete[] hashArray;
	}
	unsigned int getHashedIndex(ownString& cityName)
	{
		unsigned long hash = 2137;
		for (int i = 0; i < cityName.length();i++) {
			hash = ((hash << cityName[i]-'0') + hash) + cityName[i];
		}
		return hash % TABLE_SIZE;
	}
	unsigned int getHashedIndex(ownString&& cityName)
	{
		unsigned long hash = 2137;
		for (int i = 0; i < cityName.length(); i++) {
			hash = ((hash << cityName[i] - '0') + hash) + cityName[i];
		}
		return hash % TABLE_SIZE;
	}

	void addNewElement(Vertex* cityName)
	{
		unsigned int hashedIndex = getHashedIndex(cityName->getCity()->getName());
		HashNode* element = new HashNode{ cityName,hashedIndex };
		if (hashArray[hashedIndex].key != -1)
		{
			HashNode* checking = &hashArray[hashedIndex];
			while (checking->next != nullptr)
			{	
				checking = checking->next;
			}
			checking->next = element;
		}
		else
		hashArray[hashedIndex] = *element;

	}

	Vertex* find(ownString& looking)
	{
		HashNode* lookingNode = &hashArray[getHashedIndex(looking)];
		while (!(lookingNode->hashedVertex->getCity()->getName() == looking))
		{
			lookingNode = lookingNode->next;

			if (lookingNode == nullptr)
				return nullptr;
		}
		return lookingNode->hashedVertex;
	}

	Vertex* find(ownString&& looking)
	{
		HashNode* lookingNode = &hashArray[getHashedIndex(looking)];
		while (!(lookingNode->hashedVertex->getCity()->getName() == looking))
		{
			lookingNode = lookingNode->next;

			if (lookingNode == nullptr)
				return nullptr;
		}
		return lookingNode->hashedVertex;
	}

};


