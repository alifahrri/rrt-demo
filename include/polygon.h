#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "line.h"

class Polygon
{
public:
    typedef Line::Point Point;
    typedef std::vector<Point> Points;
public:
    Polygon();
    Polygon(Points points);
    Points points() { return points_; }
    bool isInside(const Point& p);
private:
    Points points_;
};

#endif // POLYGON_H
