#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <string>


class Point {
    public:
		float x;
	    float y;
	    float z;
		Point();
	    Point(float x,float y, float z);
	    std::string coords();
};

#endif