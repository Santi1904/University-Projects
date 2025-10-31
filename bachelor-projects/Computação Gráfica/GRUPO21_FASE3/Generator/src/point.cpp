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

void Point::sum_point(Point p){
    x += p.x;
    y += p.y;
    z += p.z;
}

void Point::mult_point(Point p){
    x *= p.x;
    y *= p.y;
    z *= p.z;
}

void Point::mult_coef(float coef){
    if (not(std::isinf(coef)) and not(std::isnan(coef)) and not(-std::isnan(coef))) {
        x *= coef;
        y *= coef;
        z *= coef;
    }
}