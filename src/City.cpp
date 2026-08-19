#include "City.hpp"
#include <iostream>
using namespace std;

City::City(int id, double x, double y) : id(id), x(x), y(y) {}

int City::getId() const{
    return id;
}

double City::getX() const{
    return x;
}

double City::getY() const{
    return y;
}