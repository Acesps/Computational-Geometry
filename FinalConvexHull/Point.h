#ifndef POINT_H
#define POINT_H

using namespace std;
class Point
{
    public:
        float x,y;

        int angle(Point, Point);
        double dis (Point);
        double slope (Point);
        double intersect(double);

        Point();
        Point(float, float);
        virtual ~Point();

    protected:

    private:
};

#endif // POINT_H
