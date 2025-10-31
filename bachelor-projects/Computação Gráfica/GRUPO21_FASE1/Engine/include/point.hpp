#pragma once
#include <string>


class Point {
    private:
	    float x;
	    float y;
	    float z;

    public:
		Point();
	    Point(float x,float y, float z);
		float get_x();
		float get_y();
		float get_z();
	    std::string coords();
};