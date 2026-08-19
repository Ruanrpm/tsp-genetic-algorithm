#ifndef CITY_HPP
#define CITY_HPP

class City{
private:
    int id;
    double x;
    double y;

public:
    City(int id, double x, double y);

    int getId() const;
    double getX() const;
    double getY() const;
};

#endif