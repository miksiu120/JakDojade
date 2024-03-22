#include "nodeToCity.h"
#include "city.h"
NodeToCity::NodeToCity() :city{ nullptr }
{
}
NodeToCity::NodeToCity(City* city, int distance) :city{ city }, distance{ distance }
{

}



City* NodeToCity::getCity()
{
	return city;
}

int NodeToCity::getCityIndex()
{
	return city->getIndex();
}

int NodeToCity::getDistance()
{
	return distance;
}


NodeToCity::~NodeToCity()
{

}