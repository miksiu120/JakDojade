#include "city.h"
#include "nodeToCity.h"
City::City(ownString name, Coordinates newCords)
	:name{name},cordsPosition{newCords},nodes{},isChecked{false}
{
}


Coordinates& City::getDotCords()
{
	return cordsPosition;
}

ownString& City::getName()
{
	return name;
}
ownString* City::getPointingName()
{
	return &name;
}
int City::getIndex()
{
	return index;
}

City::~City()
{
	for (int i = 0; i < this->nodes.size; i++)
	{
		delete nodes[i];
	}
}