#ifndef LINE_H
#define LINE_H


class Line
{
public:
    struct Point
    {
        Point() {}
        Point(double x_, double y_) : x(x_), y(y_) {}
        double x = 0;
        double y = 0;
    };

public:
    enum orientation_t {COLINEAR, CLOCKWISE, C_CLOCKWISE};

    Line();
    Line(double x0, double y0, double x1, double y1);
    Line(Point p1_, Point p2_);
    const Point& P1() const { return this->p1; }
    const Point& P2() const { return this->p2; }
    void setP1(double x_, double y_);
    void setP2(double x_, double y_);
    bool intersect(const Line& l1);
    static inline orientation_t orientation(const Point& p1, const Point& p2, const Point& p3);
    static inline bool onSegment(const Point& p1, const Point& p2, const Point& p3);


private:
    Point p1 = Point();
    Point p2 = Point();
};

#endif // LINE_H
