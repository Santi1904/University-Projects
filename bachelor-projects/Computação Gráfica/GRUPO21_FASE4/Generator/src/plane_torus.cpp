#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "../include/plane_torus.hpp"


PTorus::PTorus(int _out_radius, int _in_radius, int _slices, int _stacks) {
    out_radius = _out_radius;
    in_radius = _in_radius;
    slices = _slices;
    stacks = _stacks;
}

std::vector<std::vector<Point>> PTorus::generate_points(){
    std::vector<Point> points;
    std::vector<Point> normals;
    std::vector<std::vector<Point>> result;

    float angleSES = 2 * M_PI / slices;
    int using_radius = out_radius - in_radius;
    float mid_value = ((float)out_radius - (float)in_radius) / (float)stacks;
    float out_sub = (float)out_radius;
    float in_sub = (float)in_radius;
    
    for (int i=0; i<slices; i++){

        for (int j=0; j<stacks; j++){

            points.push_back(Point(out_sub*cos(angleSES*i),0,out_sub*sin(angleSES*i)));
            points.push_back(Point((out_sub-mid_value)*cos(angleSES*i),0,(out_sub-mid_value)*sin(angleSES*i)));
            points.push_back(Point(out_sub*cos(angleSES*(i+1)),0,out_sub*sin(angleSES*(i+1))));
            normals.push_back(Point(0,1,0));
            normals.push_back(Point(0,1,0));
            normals.push_back(Point(0,1,0));

            points.push_back(Point(out_sub*cos(angleSES*(i+1)),0,out_sub*sin(angleSES*(i+1))));
            points.push_back(Point((out_sub-mid_value)*cos(angleSES*i),0,(out_sub-mid_value)*sin(angleSES*i)));
            points.push_back(Point((out_sub-mid_value)*cos(angleSES*(i+1)),0,(out_sub-mid_value)*sin(angleSES*(i+1))));
            normals.push_back(Point(0,1,0));
            normals.push_back(Point(0,1,0));
            normals.push_back(Point(0,1,0));
            
            
            points.push_back(Point(out_sub*cos(angleSES*i),0,out_sub*sin(angleSES*i)));
            points.push_back(Point(out_sub*cos(angleSES*(i+1)),0,out_sub*sin(angleSES*(i+1))));
            points.push_back(Point((out_sub-mid_value)*cos(angleSES*i),0,(out_sub-mid_value)*sin(angleSES*i)));
            normals.push_back(Point(0,-1,0));
            normals.push_back(Point(0,-1,0));
            normals.push_back(Point(0,-1,0));

            points.push_back(Point(out_sub*cos(angleSES*(i+1)),0,out_sub*sin(angleSES*(i+1))));
            points.push_back(Point((out_sub-mid_value)*cos(angleSES*(i+1)),0,(out_sub-mid_value)*sin(angleSES*(i+1))));
            points.push_back(Point((out_sub-mid_value)*cos(angleSES*i),0,(out_sub-mid_value)*sin(angleSES*i)));
            normals.push_back(Point(0,-1,0));
            normals.push_back(Point(0,-1,0));
            normals.push_back(Point(0,-1,0));

            out_sub -= mid_value;

        }

        out_sub = (float)out_radius;
    }

    result.push_back(points);
    result.push_back(normals);
    return result;
}