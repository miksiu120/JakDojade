#pragma once
#include "vector.h"
class City;
class Vertex
{
	City* checkingCity = nullptr;
	unsigned int distanceFromSource = 0;
	Vertex* previousCity = nullptr;
	Vector<int>indexesOfCities;
	friend class GraphTree;
	friend class CitiesMap;
public:
	Vertex(City*);
	Vertex();

	void updateShortestDistance(int newDistance);
	int getDistance();
	void setDistance(int);
	void setPreviousCity(Vertex* prev);
	City* getCity();
	void addNewVisitedIndex(int index);
	void setNewIndexes(Vector<int> newIndexes);
	Vertex* getPreviousCity();
	Vector<int>& getVisitedIndexes();
	void reset();

private:

};



