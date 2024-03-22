#pragma once
#include "ownstring.h"
#include "graphTree.hpp"
#include "city.h"
#include "nodeToCity.h"
#include <iostream>
#include "coords.h"
using namespace std;
int constexpr BUFFOR_SIZE = 10000;
struct CordsWithCounter;
class CitiesMap
{
    const int mapWidth;
    const int mapHeight;
    ownString* map = nullptr;
    GraphTree& mainList;

    struct CordsWithBool {
        Coordinates cityCords;
        bool visited;
        CordsWithBool(Coordinates c, bool v)
            :cityCords{c},visited{v}
        {

        }
    };
 
    HashMap* hashedCities;
    bool* visited2;
public:
    CitiesMap(int, int, GraphTree* mainList,HashMap*);
    ~CitiesMap();
    Coordinates findFirstDot();
    Coordinates findCityName(Coordinates& dotPosition);
    City* getNextUncheckedCity();
    ownString fetchCityName(Coordinates&);
    ownString fetchCityName(Coordinates&&);
    Vector<CordsWithCounter>* findConnections(City&);
    bool isPossibleToMove(Coordinates& elements);
    bool isPossibleToMove(Coordinates&& elements);
    void floodFill();
    void loadFlights();
    bool doesHavePath(City&);
};
