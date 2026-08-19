#include "City.hpp"
#include <iostream>
using namespace std;

int main()
{
    City city(0, 10, 20);

    cout << city.getId() << endl;
    cout << city.getX() << endl;
    cout << city.getY() << endl;
}