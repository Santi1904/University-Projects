#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "../include/cylinder.hpp"


Cylinder::Cylinder(int _radius, int _heigth, int _slices, int _stacks) {
    radius = _radius;
    heigth = _heigth;
    slices = _slices;
    stacks = _stacks;
}

std::vector<std::vector<Point>> Cylinder::generate_points(){
    std::vector<Point> points;
    std::vector<std::vector<Point>> result;
    float angle = 2 * M_PI / slices;
    float div_size = (float)heigth / (float)stacks;
    float act_size = 0;

    for (int i = 0; i < stacks; act_size += div_size, i++){

	    for (int j=0; j<slices; j++){
            
            if (i == 0) {
                points.push_back(Point(radius*sin(angle*j),act_size,radius*cos(angle*j)));
                points.push_back(Point(0,act_size,0));
                points.push_back(Point(radius*sin(angle*(j+1)),act_size,radius*cos(angle*(j+1))));
            }

            points.push_back(Point(radius*sin(angle*j),act_size,radius*cos(angle*j)));
            points.push_back(Point(radius*sin(angle*(j+1)),act_size,radius*cos(angle*(j+1))));
            points.push_back(Point(radius*sin(angle*j),act_size+div_size,radius*cos(angle*j)));

            points.push_back(Point(radius*sin(angle*(j+1)),act_size,radius*cos(angle*(j+1))));
            points.push_back(Point(radius*sin(angle*(j+1)),act_size+div_size,radius*cos(angle*(j+1))));
            points.push_back(Point(radius*sin(angle*j),act_size+div_size,radius*cos(angle*j)));

            if (i == stacks - 1) {
                points.push_back(Point(radius*sin(angle*j),act_size+div_size,radius*cos(angle*j)));
                points.push_back(Point(radius*sin(angle*(j+1)),act_size+div_size,radius*cos(angle*(j+1))));
                points.push_back(Point(0,act_size+div_size,0));
            }
	    }
        
    }

    result.push_back(points);
    return result;
}