#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "../include/cone.hpp"


Cone::Cone(int _radius, int _heigth, int _slices, int _stacks) {
    radius = _radius;
    heigth = _heigth;
    slices = _slices;
    stacks = _stacks;
}

std::vector<Point> Cone::generate_points(){
    std::vector<Point> points;

    float angle = 2 * M_PI / slices;
    float div_size = (float)heigth / (float)stacks;
    float act_size = 0;

    float act_radius = (float)radius;
    float div_radius = (float)radius / (float) (stacks);
    int i;
    for (i = 0; i < stacks; act_size += div_size, i++){

        points.push_back(Point(0,0,0));
        points.push_back(Point(radius*sin(angle*(i+1)),0,radius*cos(angle*(i+1))));
        points.push_back(Point(radius*sin(angle*i),0,radius*cos(angle*i)));

	    for (int j=0; j<slices; j++){

            points.push_back(Point((act_radius-div_radius)*sin(angle*j),act_size + div_size,(act_radius-div_radius)*cos(angle*j)));
            points.push_back(Point(act_radius*sin(angle*j),act_size,act_radius*cos(angle*j)));
            points.push_back(Point(act_radius*sin(angle*(j+1)),act_size,act_radius*cos(angle*(j+1))));

            points.push_back(Point(act_radius*sin(angle*(j+1)),act_size,act_radius*cos(angle*(j+1))));
            points.push_back(Point((act_radius-div_radius)*sin(angle*(j+1)),act_size + div_size,(act_radius-div_radius)*cos(angle*(j+1))));
            points.push_back(Point((act_radius-div_radius)*sin(angle*j),act_size + div_size,(act_radius-div_radius)*cos(angle*j)));

	    }
        act_radius -= div_radius;
    }

    points.push_back(Point(0,0,0));
    points.push_back(Point(radius*sin(angle*(i+1)),0,radius*cos(angle*(i+1))));
    points.push_back(Point(radius*sin(angle*i),0,radius*cos(angle*i)));
    return points;
}