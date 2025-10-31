#include "../include/point.hpp"

Point::Point(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

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

std::string Point::coords() {
	return "X: " +std::to_string(x) + "\nY: " + std::to_string(y) + "\nZ: " + std::to_string(z);
}
