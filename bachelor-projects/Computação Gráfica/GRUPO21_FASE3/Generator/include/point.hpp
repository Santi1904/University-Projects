#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>
#include <cmath>


class Point {
    private:
	    float x;
	    float y;
	    float z;

    public:
	    Point(float x,float y, float z);
		float get_x();
		float get_y();
		float get_z();
		void sum_point(Point p);
		void mult_point(Point p);
		void mult_coef(float coef);
};

#endif