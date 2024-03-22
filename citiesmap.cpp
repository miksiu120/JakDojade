#include "citiesMap.h"
#include <iostream>
#include "Vector.h"
#include <cstring>
#include "Hashmap.h"
using namespace std;


struct CordsWithCounter {
public:
    Coordinates cords{ 0,0 };

    int pathLength = 0;
    CordsWithCounter(Coordinates cords, int pathLength)
        :cords{ cords }, pathLength{ pathLength }
    {

    }

    CordsWithCounter() :cords{ 0,0 }, pathLength{ 0 }
    {
    }
    bool operator==(const CordsWithCounter& compared)
    {
        if ((cords == compared.cords))
        {
            return true;
        }
        else
            return false;
    }
};




CitiesMap::CitiesMap(int width, int height, GraphTree* mainList,HashMap* hashed)
    :mapWidth{ width }, mapHeight{ height }, map{ new ownString[mapHeight] }
    , mainList{ *mainList },hashedCities{hashed}
{
 
    char buffor[BUFFOR_SIZE];
    std::cin.getline(buffor, BUFFOR_SIZE);

    Vector<Coordinates>coordsCities;

    for (int i = 0; i < mapHeight; i++)
    {
        char buffor2[BUFFOR_SIZE];
        for (int j = 0; j <= mapWidth; j++)
        {
            char buf = getchar();
            buffor2[j] = buf;
            if (buf == '*')
                coordsCities.pushBack(Coordinates{j,i});  
        }
        buffor2[mapWidth] = '\0';
        ownString loadedLine{ buffor2 };
        map[i] = loadedLine;

    }

     for (int j = 0; j < coordsCities.size; j++)
     {
         Coordinates firstDot = coordsCities[j];   
         Coordinates firstLetter = findCityName(firstDot);
         City* firstCity = new City{ fetchCityName(firstLetter),firstDot };
         mainList->addNewIndependentCity(firstCity);
         hashedCities->addNewElement(mainList->getCityList()[j]);
     }

   
 
}

CitiesMap::~CitiesMap()
{
    delete[] map;
}

Coordinates CitiesMap::findFirstDot()
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            if (map[i][j] == '*')
            {
                return Coordinates{ j,i };
            }
        }
    }
    return Coordinates{ -1,-1 };
}

Coordinates CitiesMap::findCityName(Coordinates& dotPosition)
{
    int abroadCords[8][2]
        = { {0,1},{1,0},{-1,0},{0,-1},{1,1},{-1,1},{1,-1}, {-1,-1} };
    for (int i = 0; i < 8; i++)
    {

        if (isPossibleToMove(Coordinates{ dotPosition.x + abroadCords[i][1],dotPosition.y + abroadCords[i][0] }) and map[dotPosition.y + abroadCords[i][0]]
            [dotPosition.x + abroadCords[i][1]] >= 'A' and
            map[dotPosition.y + abroadCords[i][0]]
            [dotPosition.x + abroadCords[i][1]] <= 'Z')
        {
            return Coordinates{ dotPosition.x + abroadCords[i][1],
                dotPosition.y + abroadCords[i][0] };
        }
    }
    return Coordinates{ -1,-1 };
}

ownString CitiesMap::fetchCityName(Coordinates& letterCoordinates)
{
    ownString cityName{ map[letterCoordinates.y][letterCoordinates.x] };

    Coordinates checkingCords{ letterCoordinates.x,letterCoordinates.y };
    while (isPossibleToMove(checkingCords) and isalnum(map[checkingCords.y][checkingCords.x]))
    {
        cityName.addFromLeft(map[checkingCords.y][checkingCords.x--]);
    }

    Coordinates checkingCords2{ letterCoordinates.x + 1,letterCoordinates.y };
    while (isPossibleToMove(checkingCords2) and isalnum(map[checkingCords2.y][checkingCords2.x]))
    {
        cityName = cityName + map[checkingCords2.y][checkingCords2.x++];
    }
    return cityName;
}
ownString CitiesMap::fetchCityName(Coordinates&& letterCoordinates)
{
    ownString cityName{ map[letterCoordinates.y][letterCoordinates.x] };

    Coordinates checkingCords{ letterCoordinates.x,letterCoordinates.y };
    while (isPossibleToMove(checkingCords) and isalnum(map[checkingCords.y][checkingCords.x]))
    {
        cityName.addFromLeft(map[checkingCords.y][checkingCords.x--]);
    }
    Coordinates checkingCords2{ letterCoordinates.x + 1,letterCoordinates.y };
    while (isPossibleToMove(checkingCords2) and isalnum(map[checkingCords2.y][checkingCords2.x]))
    {
        cityName = cityName + map[checkingCords2.y][checkingCords2.x++];
    }
    return cityName;
}

Vector<CordsWithCounter>* CitiesMap::findConnections(City& mainCity)
{

    visited2 = new bool[mapWidth * mapHeight];
    // fill(visited2,(visited2+mapHeight*mapWidth),0 );
    memset(visited2, 0, mapHeight * mapWidth);
    Vector<CordsWithCounter>* cityCords = new Vector<CordsWithCounter>;
    Vector<CordsWithCounter>element;
    element.pushBack(CordsWithCounter{ mainCity.getDotCords(),0 });

    int neighbourArray[][2] = { {1,0},{0,1},{-1,0},{0,-1} };

    auto isThereRoad = [&](int i, int j) -> bool {
        int newX = element[i].cords.x + neighbourArray[j][0];
        int newY = element[i].cords.y + neighbourArray[j][1];
        return (this->map[newY][newX] == '#') &&
            (!visited2[(newY * mapWidth) + newX]);
    };

    auto isThereCity = [&](int i, int j) -> bool {
        int newX = element[i].cords.x + neighbourArray[j][0];
        int newY = element[i].cords.y + neighbourArray[j][1];
        Coordinates newCoords{ newX, newY };

        return (this->map[newY][newX] == '*') and
            (mainCity.getDotCords() != newCoords) and
            !(cityCords->find(CordsWithCounter{ Coordinates{ element[i].cords.x + neighbourArray[j][0],element[i].cords.y + neighbourArray[j][1]},0 }));
    };


    for (long long int i = 0; i < element.size; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (isPossibleToMove(Coordinates{ element[i].cords.x + neighbourArray[j][0],element[i].cords.y + neighbourArray[j][1] }))
            {
                if (isThereRoad(i,j))
                {

                    element.pushBack(CordsWithCounter
                        { Coordinates{ element[i].cords.x + neighbourArray[j][0],element[i].cords.y + neighbourArray[j][1] },element[i].pathLength + 1 });
                }

                if (isThereCity(i,j))
                {
                    Coordinates newCords{ element[i].cords.x + neighbourArray[j][0],element[i].cords.y + neighbourArray[j][1] };
                    cityCords->pushBack(CordsWithCounter{ newCords,element[i].pathLength + 1 });

                }
                visited2[(element[i].cords.y + neighbourArray[j][1]) * mapWidth + element[i].cords.x + neighbourArray[j][0]] = true;
            }

        }

        visited2[(element[i].cords.y) * mapWidth + element[i].cords.x] = true;
    }
    delete[] visited2;

    return cityCords;
}

bool CitiesMap::isPossibleToMove(Coordinates& elements)
{
    if (elements.x >= 0 and elements.y >= 0 and
        elements.x < mapWidth and elements.y < mapHeight)
        return true;
    return false;
}

bool CitiesMap::isPossibleToMove(Coordinates&& elements)
{
    if (elements.x >= 0 and elements.y >= 0 and
        elements.x < mapWidth and elements.y < mapHeight)
        return true;
    return false;
}

City* CitiesMap::getNextUncheckedCity()
{
    static int i = 0;
    for (; i < mainList.getCityList().size; i++)
    {

        if (mainList.getCityList()[i]->checkingCity->doesChecked() == false)
        {
            return mainList.getCityList()[i]->checkingCity;
        }
    }

    return nullptr;
}

void CitiesMap::floodFill()
{

    mainList.setSentry(mainList.getCityList()[0]);

    City* firstCity = getNextUncheckedCity();
    while (firstCity != nullptr)
    {
        firstCity = getNextUncheckedCity();

        if (firstCity == nullptr)
            return;

        if (doesHavePath(*firstCity) == false)
        {
            firstCity->setCheck();
            continue;
        }

        Vector<City*>toCheck;
        toCheck.pushBack(firstCity);
        for(int i=0;i<toCheck.size;i++)
        {
            Vector<CordsWithCounter>* newCitiesCords = findConnections(*toCheck[i]);
            for (int j = 0; j < newCitiesCords->size; j++)
            {
                City* lookingCity = mainList.findByCords(newCitiesCords->vector[j].cords);
                
                mainList.addNewNode(lookingCity, toCheck[i], newCitiesCords->vector[j].pathLength);

                if (lookingCity->doesChecked() == false)
                {
                    lookingCity->setCheck();
                    toCheck.pushBack(lookingCity);
                }
            }
            delete newCitiesCords;
            toCheck[i]->setCheck();
        }
    }
}

void CitiesMap::loadFlights()
{
    int n;
    cin >> n;

    if (n == 0)
        return;
    getchar();
    for (int i = 0; i < n; i++)
    {
    char *firstCity = new char[20] {};
    ownString firstString;
    char *secondCity = new char[20]{};
    ownString secondString;
    int time;

        char loadingChar{};
       // cin >> firstCity;
        int indexFirst = 0;
       
        loadingChar = getchar();
        do {
            firstCity[indexFirst++] = loadingChar;
            loadingChar = getchar();           
        } while(loadingChar != ' ');
        firstCity[indexFirst] = '\0';
        firstString.addCharPointer(firstCity);
       // cin >> secondCity;
        int indexSecond = 0;
        loadingChar = getchar();
        do {
            secondCity[indexSecond++] = loadingChar;
            loadingChar = getchar();
            
        } while (loadingChar != ' ');
        secondCity[indexSecond] = '\0';
        secondString.addCharPointer(secondCity);
       
        char num[8];
        int numIndex = 0;
        loadingChar = getchar();
        do {
            num[numIndex++] = loadingChar;
            loadingChar = getchar();
        } while(loadingChar!='\n');
        num[numIndex] = '\0';
        time = atoi(num);
        City* second = hashedCities->find(secondCity)->getCity();
        City* first = hashedCities->find(firstCity)->getCity();
        
        delete[] firstCity;
        delete[] secondCity;
      
        mainList.addNewNode(second,first, time);
    }
}

bool CitiesMap::doesHavePath(City& city)
{
    int neighbourArray[][2] = { {1,0},{0,1},{-1,0},{0,-1} };
    bool didPathFind = false;
    for (int j = 0; j < 4; j++)
    {
        Coordinates checkingCords = Coordinates{ city.getDotCords().x + neighbourArray[j][0],city.getDotCords().y + neighbourArray[j][1] };
        if (isPossibleToMove(checkingCords) and (map[checkingCords.y][checkingCords.x] == '#'
            or map[checkingCords.y][checkingCords.x] == '*'))
        {
            return true;
        }
    }
    return didPathFind;
}
