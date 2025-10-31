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

std::string Point::point_to_string(){
    std::string str = std::to_string(x) + std::to_string(y) + std::to_string(z);
    return str;
}

void Point::zero_correction(){
    if (x == -0)
        x = 0;
    if (y == -0)
        y = 0;
    if (z==0)
        z = 0;
}

Point Point::normalize_point(){
    float value = std::sqrt(x*x + y*y + z*z);
    return Point(x / value, y / value, z / value);
}