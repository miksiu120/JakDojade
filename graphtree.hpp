#pragma once
#include <iostream>
#include "ownstring.h"
#include "Vector.h"
#include "coords.h"
#include "Hashmap.h"
#include "vertex.h"
class City;
class NodeToCity;
class GraphTree
{
	Vertex* sentry;
	HashMap* hashedCities;
	Vector<Vertex*>cityList;
public:
	GraphTree();
	GraphTree(HashMap*);
	~GraphTree();
	GraphTree(Vertex* newSentry);
	City* findByCords(Coordinates);
	void addNewCity(City* newCity, City* City, int distance);
	void addNewIndependentCity(City*);
	void addNewNode(City* newCity, City* connectedCity, int& distance);
	void setSentry(Vertex* sentry);
	void showList();
	void doDijkstra(ownString* startCity, ownString* goalCity,bool withCities);
	void resetVertexes();
	Vector<Vertex*>& getCityList();
};
