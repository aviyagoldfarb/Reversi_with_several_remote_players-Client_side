//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#include "Point.h"

Point::Point(int x, int y) : x(x) , y(y) {}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int x) {
    this->x = x;
}

void Point::setY(int y) {
    this->y = y;
}

bool Point::isEqual(Point other){
    if(this->x == other.getX() && this->y == other.getY()){
        return true;
    }
    return false;
}

void Point::pointToPrint() const{
    cout << "(" << this->x << "," << this->y << ")";
}

bool operator == (const Point &point1, const Point &point2) {
    if(point1.getX() == point2.getX() && point1.getY() == point2.getY()){
        return true;
    }
    else
        return false;
}

bool operator != (const Point &point1, const Point &point2) {
    return ((point1.getX() != point2.getX()) || (point1.getY() != point2.getY()));
}
