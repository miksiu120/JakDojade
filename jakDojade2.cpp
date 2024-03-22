
#include <iostream>
#include "ownstring.h"
#include "citiesMap.h"
#include "Hashmap.h"
using namespace std;




int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);



	int mapWidth;
	int mapHeight;
	cin >> mapWidth;
	cin >> mapHeight;

	HashMap hashedCities;

	GraphTree mainList{&hashedCities };
	CitiesMap gameMap{ mapWidth,mapHeight,&mainList,&hashedCities };
	gameMap.floodFill();
    //mainList.showList();
	gameMap.loadFlights();

	int numOfAsks;
	char firstCity[100];
	char secondCity[100];
	ownString first;
	ownString second;
	bool withCities{};
	cin >> numOfAsks;
	
	for (int i = 0; i < numOfAsks; i++)
	{
		cin >> firstCity;
		first = firstCity;
		cin >> secondCity;
		second = secondCity;
		cin >> withCities;
		mainList.doDijkstra(&first,&second, withCities);
	}



}