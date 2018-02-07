#ifndef GRAHAM_H
#define GRAHAM_H
#include <iostream>
#include <algorithm>
#include <vector>

struct cordinate {
	int x;
	int y;
};

class Graham
{public:
    static void Grahams(std::vector<cordinate> cordinates);
	static int angle(cordinate a, cordinate b, cordinate c);
};
#endif
 
