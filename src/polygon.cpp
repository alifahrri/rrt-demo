#include "polygon.h"
#define INF 1000000

Polygon::Polygon()
{

}

Polygon::Polygon(Points points) :
    points_(points)
{

}

bool Polygon::isInside(const Polygon::Point &p)
{
    Point extreme(INF,p.y);
    Line test_line(p,extreme);
    int count = 0;
    for(int i=0; i<points_.size(); i++)
    {
        int next = (i+1)%points_.size();
        Line line_polygon(points_[i],points_[next]);
        if(test_line.intersect(line_polygon))
        {
            if(Line::orientation(points_[i],p,points_[next])==Line::COLINEAR)
                return Line::onSegment(points_[i],p,points_[next]);
            count++;
        }
    }
    return count&1;
}
