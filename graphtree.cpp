#include "graphTree.hpp"
#include "nodeToCity.h"
#include "city.h"
#include <iostream>
#include "vertex.h"
#include  <queue>
#include "prioritylist.h"
GraphTree::GraphTree()
{
	sentry = nullptr;
}

GraphTree::GraphTree(HashMap* mapped)
{
	sentry = nullptr;
	hashedCities = mapped;
}

GraphTree::~GraphTree()
{
	for (int i = 0; i < cityList.size; i++)
	{
		delete cityList[i]->checkingCity;
		delete cityList[i];
	}

}

GraphTree::GraphTree(Vertex* newSentry) {
	sentry = newSentry;
}

City* GraphTree::findByCords(Coordinates looking)
{
	for (int i = 0; i < cityList.size; i++)
	{
		if (cityList[i]->checkingCity->cordsPosition == looking)
			return cityList[i]->checkingCity;
	}
	return nullptr;
}

void GraphTree::addNewCity(City* newCity, City* City, int distance)
{
	

}

void GraphTree::addNewIndependentCity(City* newCity)
{
	newCity->index = cityList.size;
	Vertex* newVertex = new Vertex{ newCity };
	cityList.pushBack(newVertex);
}


void GraphTree::addNewNode(City* newCity, City* connectedCity, int& distance)
{
	NodeToCity* newNode = new NodeToCity{ newCity,distance };
	connectedCity->nodes.pushBack(newNode);
}

void GraphTree::setSentry(Vertex* sentry)
{
	this->sentry = sentry;
}

void GraphTree::showList()
{
	for (int i = 0; i < cityList.size; i++)
	{
		std::cout << cityList[i]->checkingCity->name << std::endl;
		for (int j = 0; j < cityList[i]->checkingCity->nodes.size; j++)
		{
			std::cout<<cityList[i]->checkingCity->index << "\t" << cityList[i]->checkingCity->nodes[j]->getCity()->getName() << std::endl;
		}
	}
}

void GraphTree::doDijkstra(ownString* startCityName, ownString* goalCityName, bool showVisited)
{
	Vertex* startCity = hashedCities->find(*startCityName);
	Vertex* goalCity = hashedCities->find(*goalCityName);

	PriorityList checkingCities;
	checkingCities.push(startCity);
	resetVertexes();
	cityList[startCity->getCity()->index]->setDistance(0);

	while(checkingCities.isEmpty() == false)
	{
        City* checkingVertex = checkingCities.front()->getCity();
		checkingCities.pop();
		
		if (checkingVertex->getName() == *goalCityName)
		{
			break;
		}
		
		for (int i = 0; i < checkingVertex->nodes.size; i++)
		{

			if (cityList[checkingVertex->nodes[i]->getCityIndex()]->getDistance() >
				checkingVertex->nodes[i]->getDistance() + cityList[checkingVertex->index] -> getDistance())
				{
				cityList[checkingVertex->nodes[i]->getCityIndex()]
				->setDistance(checkingVertex->nodes[i]->getDistance() + cityList[checkingVertex->index]->getDistance());
				
				Vertex* prev = cityList[checkingVertex->index];
				cityList[checkingVertex->nodes[i]->getCityIndex()]->setPreviousCity(prev);
				}		

			if (checkingVertex->nodes[i]->getCity()->doesVisitedInDijkstra == false)
			{
				checkingCities.push(cityList[checkingVertex->nodes[i]->getCity()->getIndex()]);
				checkingVertex->nodes[i]->getCity()->doesVisitedInDijkstra = true;
			}

		}

		
	}
		Vertex* checking = cityList[goalCity->getCity()->index];

		if (checking->getCity() == goalCity->getCity())
		{
			std::cout << checking->getDistance() << " ";
			Vertex* temp = checking;
			if (showVisited)
			{
				Vector<ownString*>visitedCities;
				while (temp->getPreviousCity() != nullptr and temp->getPreviousCity()->getCity() != startCity->getCity())
				{
			
					visitedCities.pushBack(temp->getPreviousCity()->getCity()->getPointingName());
					temp = temp->getPreviousCity();
				}

				for (int j = visitedCities.size - 1; j >= 0; j--)
				{
					std::cout << *visitedCities[j] << " ";
				}
				
			}

			std::cout << std::endl;
		}
		
		
	
}


void GraphTree::resetVertexes()
{
	for (int i = 0; i < cityList.size; i++)
	{
		cityList[i]->reset();
	}
}

Vector<Vertex*>& GraphTree::getCityList()
{
	return cityList;
}
