#include "line.h"

#define max(X,Y) ((X > Y) ? (X) : (Y))
#define min(X,Y) ((X < Y) ? (X) : (Y))

Line::Line()
{

}

Line::Line(double x0, double y0, double x1, double y1) :
    p1(x0,y0), p2(x1,y1)
{

}

Line::Line(Line::Point p1_, Line::Point p2_) :
    p1(p1_), p2(p2_)
{

}

void Line::setP1(double x_, double y_)
{
    p1 = Point(x_,y_);
}

void Line::setP2(double x_, double y_)
{
    p2 = Point(x_,y_);
}

bool Line::intersect(const Line &l1)
{
    auto o1 = orientation(this->p1,this->p2,l1.p1);
    auto o2 = orientation(this->p1,this->p2,l1.p2);
    auto o3 = orientation(l1.p1,l1.p2,this->p1);
    auto o4 = orientation(l1.p1,l1.p2,this->p2);

    if((o1 != o2) && (o3 != o4))
        return true;
    if(o1==COLINEAR && onSegment(this->p1,l1.p1,this->p2))
        return true;
    if(o2==COLINEAR && onSegment(this->p1,l1.p2,this->p2))
        return true;
    if(o3==COLINEAR && onSegment(l1.p1,this->p1,l1.p2))
        return true;
    if(o4==COLINEAR && onSegment(l1.p1,this->p2,l1.p2))
        return true;
    return false;
}

Line::orientation_t Line::orientation(const Line::Point &p1, const Line::Point &p2, const Line::Point &p3)
{
    auto v = (p2.y - p1.y) * (p3.x - p2.x) -
            (p2.x - p1.x) * (p3.y - p2.y);
    if(v==0) return COLINEAR;

    return (v>0) ? CLOCKWISE : C_CLOCKWISE;
}

bool Line::onSegment(const Line::Point &p1, const Line::Point &p2, const Line::Point &p3)
{
    if(p2.x <= max(p1.x,p3.x) && p2.x >= min(p1.x,p3.x) &&
       p2.y <= max(p1.y,p3.y) && p2.y >= min(p1.y,p3.y))
        return true;
    return false;
}
