#include "../include/point.hpp"

Point::Point(){
    x = 999.9;
    y = 999.9;
    z = 999.9;
}

Point::Point(float xx,float yy, float zz) {
	x = xx;
    y = yy;
    z = zz;
}

std::string Point::coords() {
	return "X: " + std::to_string(x) + "\nY: " + std::to_string(y) + "\nZ: " + std::to_string(z);
}
