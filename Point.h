//
// Udi Goldman 301683264 , Aviya Goldfarb 201509635
//

#ifndef EX2_POINT_H
#define EX2_POINT_H

#include <string>
#include <iostream>
using namespace std;

/**
 * the class Point defines Point object.
 * a point represents a cell in the board.
 */
class Point {
public:
    /**
     * constructor of Point object.
     * @param x row.
     * @param y column.
     */
    Point(int x, int y);
    /**
     * get the value of row x.
     * @return row.
     */
    int getX() const;
    /**
     * get the value of column y.
     * @return column.
     */
    int getY() const;
    /**
     * set the value of row x.
     * @param x row.
     */
    void setX(int x);
    /**
     * set the value of column y.
     * @param y column.
     */
    void setY(int y);
    /**
     * check if two points are equal.
     * @param other point.
     * @return boolean.
     */
    bool isEqual(Point other);
    /**
     * printing the point to the screen.
     */
    void pointToPrint() const;
private:
    //row
    int x;
    //column
    int y;
};

/**
 * operator overloading for ==.
 * @param point1
 * @param point2
 * @return
 */
bool operator ==(const Point &point1, const Point &point2);
/**
 * operator overloading for !=.
 * @param point1
 * @param point2
 * @return
 */
bool operator !=(const Point &point1, const Point &point2);

#endif //EX2_POINT_H
