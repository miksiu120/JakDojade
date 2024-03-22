#pragma once
class City;
class NodeToCity
{
	City* city;
	int distance;
public:
	NodeToCity();
	NodeToCity(City*,int);
	City* getCity();
	int getCityIndex();
	int getDistance();
	~NodeToCity();

};

