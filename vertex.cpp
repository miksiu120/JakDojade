#include "vertex.h"
#include "city.h"

Vertex::Vertex(City* checking) :checkingCity{ checking },
distanceFromSource{ 4000000000 }, previousCity{ nullptr }
{
}

Vertex::Vertex()
{
}

void Vertex::updateShortestDistance(int newDistance)
{
	distanceFromSource = newDistance;
}

int Vertex::getDistance()
{
	return distanceFromSource;
}

void Vertex::setDistance(int newDist)
{
	distanceFromSource = newDist;
}

void Vertex::setPreviousCity(Vertex* prev)
{
	previousCity = prev;
}

City* Vertex::getCity()
{
	return  checkingCity;
}

void Vertex::addNewVisitedIndex(int index)
{
	indexesOfCities.pushBack(index);
}

void Vertex::setNewIndexes(Vector<int> newIndexes)
{
	indexesOfCities = newIndexes;
}

Vertex* Vertex::getPreviousCity()
{
	return previousCity;
}

Vector<int>& Vertex::getVisitedIndexes()
{
	return indexesOfCities;
}

void Vertex::reset()
{
	distanceFromSource = 9999999;
	previousCity = nullptr;
	this->checkingCity->doesVisitedInDijkstra = false;
}

