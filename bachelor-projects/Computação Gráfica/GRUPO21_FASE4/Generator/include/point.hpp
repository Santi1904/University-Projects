#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>


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
		std::string point_to_string();
		void zero_correction();
		Point normalize_point();
};

#endif