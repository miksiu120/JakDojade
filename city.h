#pragma once
#include "ownstring.h"
#include "Vector.h"
#include "Coords.h"
#include "priorityList.h"
class NodeToCity;
class City
{
	Coordinates cordsPosition;
	ownString name;
	Vector<NodeToCity*>nodes;
	int index = 0;
	bool isChecked = false;
	bool doesVisitedInDijkstra = false;
	friend class GraphTree;
	friend class Vertex;
public:
	City(ownString,Coordinates);
	City() :cordsPosition{ 0,0 } {
		name = "city";
		
	};
	Coordinates& getDotCords();
	ownString& getName();
	ownString* getPointingName();
	int getIndex();
	void setCheck() { isChecked = true; }
	bool doesChecked() { 
		return isChecked;
	}
	~City();
};

