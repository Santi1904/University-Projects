#include "../include/point.hpp"


Point::Point(float xx,float yy, float zz) {
	x = xx;
    y = yy;
    z = zz;
}

float Point::get_x(){
    return x;
}

float Point::get_y(){
    return y;
}

float Point::get_z(){
    return z;
}