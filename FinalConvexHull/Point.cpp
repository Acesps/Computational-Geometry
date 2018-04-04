#include "Point.h"

Point::Point()
{
    x=0;
    y=0;
}

Point::Point(float a, float b)
{
    x=a;
    y=b;
}

Point::~Point()
{
    //dtor
}

//Returns orientation of b-c wrt current point
int Point::angle(Point b, Point c)
{
    int val = (b.x-x)*(c.y-b.y)-(b.y-y)*(c.x-b.x);
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: -1; //  counterclock or clock wise
}

//Returns distance of t from current point
double Point::dis(Point t)
{
    return (x-t.x)*(x-t.x) + (y-t.y)*(y-t.y);
}

//Returns slope of t wrt current point
double Point::slope(Point t)
{
    return (y-t.y)/(x-t.x);
}

//Returns the intercept of line with slope K passing through current point
double Point::intersect(double K)
{
    return y - K * x;
}
