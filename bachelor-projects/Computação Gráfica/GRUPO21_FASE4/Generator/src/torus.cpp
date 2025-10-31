#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "../include/torus.hpp"


Torus::Torus(int _out_radius, int _in_radius, int _slices, int _stacks) {
    out_radius = _out_radius;
    in_radius = _in_radius;
    slices = _slices;
    stacks = _stacks;
}

std::vector<std::vector<Point>> Torus::generate_points(){
    std::vector<Point> points;
    std::vector<std::vector<Point>> result;

    float angleSES = 2 * M_PI / slices;
    int using_radius = out_radius - in_radius;
    
    for (int i=0; i<slices; i++){
        float angleSKS = 2 * M_PI / stacks;

        for (int j=0; j<stacks; j++){
            points.push_back(Point((out_radius+using_radius*cos(j*angleSKS))*cos(i*angleSES),(out_radius+using_radius*cos(j*angleSKS))*sin(i*angleSES),using_radius*sin(j*angleSKS)));
            points.push_back(Point((out_radius+using_radius*cos((j+1)*angleSKS))*cos(i*angleSES),(out_radius+using_radius*cos((j+1)*angleSKS))*sin(i*angleSES),using_radius*sin((j+1)*angleSKS)));
            points.push_back(Point((out_radius+using_radius*cos((j+1)*angleSKS))*cos((i+1)*angleSES),(out_radius+using_radius*cos((j+1)*angleSKS))*sin((i+1)*angleSES),using_radius*sin((j+1)*angleSKS)));

            points.push_back(Point((out_radius+using_radius*cos((j+1)*angleSKS))*cos((i+1)*angleSES),(out_radius+using_radius*cos((j+1)*angleSKS))*sin((i+1)*angleSES),using_radius*sin((j+1)*angleSKS)));
            points.push_back(Point((out_radius+using_radius*cos(j*angleSKS))*cos((i+1)*angleSES),(out_radius+using_radius*cos(j*angleSKS))*sin((i+1)*angleSES),using_radius*sin(j*angleSKS)));
            points.push_back(Point((out_radius+using_radius*cos(j*angleSKS))*cos(i*angleSES),(out_radius+using_radius*cos(j*angleSKS))*sin(i*angleSES),using_radius*sin(j*angleSKS)));


        }
    }

    result.push_back(points);
    return result;
}
