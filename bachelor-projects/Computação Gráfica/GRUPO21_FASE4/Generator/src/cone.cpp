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

std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> Cone::generate_points(){
    std::vector<std::vector<Point>> result;
    std::vector<Point> points;
    std::vector<Point> normals;

    std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> allCoords;
	std::vector<std::pair<float,float>> textCoords;

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
        normals.push_back(Point(0,-1,0));
        normals.push_back(Point(0,-1,0));
        normals.push_back(Point(0,-1,0));
        textCoords.push_back(std::pair<float,float>(0,0));
        textCoords.push_back(std::pair<float,float>(float(i+1)/(float)stacks, 0));
        textCoords.push_back(std::pair<float,float>((float)i/(float)stacks, 0));

	    for (int j=0; j<slices; j++){


            points.push_back(Point((act_radius-div_radius)*sin(angle*j),act_size + div_size,(act_radius-div_radius)*cos(angle*j)));
            points.push_back(Point(act_radius*sin(angle*j),act_size,act_radius*cos(angle*j)));
            points.push_back(Point(act_radius*sin(angle*(j+1)),act_size,act_radius*cos(angle*(j+1))));
            normals.push_back(Point(sin(angle*j)/2.0f,sin(atan((float)radius / (float)heigth))/2.0f, cos(angle*j)/2.0f).normalize_point());
            normals.push_back(Point(sin(angle*j)/2.0f,sin(atan((float)radius / (float)heigth))/2.0f, cos(angle*j)/2.0f).normalize_point());
            normals.push_back(Point(sin(angle*(j+1))/2.0f,sin(atan((float)radius / (float)heigth))/2.0f, cos(angle*(j+1))/2.0f).normalize_point());

            textCoords.push_back(std::pair<float, float>((float)(j+1) / (float)slices, (i+1)/ (float)stacks));
            textCoords.push_back(std::pair<float, float>((float)(j+1) / (float)slices, i / (float)stacks));
            textCoords.push_back(std::pair<float, float>((float)j / (float)slices, i / (float)stacks));


            points.push_back(Point(act_radius*sin(angle*(j+1)),act_size,act_radius*cos(angle*(j+1))));
            points.push_back(Point((act_radius-div_radius)*sin(angle*(j+1)),act_size + div_size,(act_radius-div_radius)*cos(angle*(j+1))));
            points.push_back(Point((act_radius-div_radius)*sin(angle*j),act_size + div_size,(act_radius-div_radius)*cos(angle*j)));
            normals.push_back(Point(sin(angle*(j+1))/2.0f,sin(atan((float)radius / (float)heigth))/2.0f, cos(angle*(j+1))/2.0f).normalize_point());
            normals.push_back(Point(sin(angle*(j+1))/2.0f,sin(atan((float)radius / (float)heigth))/2.0f, cos(angle*(j+1))/2.0f).normalize_point());
            normals.push_back(Point(sin(angle*j)/2.0f,sin(atan((float)radius / (float)heigth))/2.0f, cos(angle*j)/2.0f).normalize_point());

            textCoords.push_back(std::pair<float, float>((float)j / (float)slices, (float)i / (float)stacks));
            textCoords.push_back(std::pair<float, float>((float)(j) / (float)slices, (i+1) / (float)stacks));
            textCoords.push_back(std::pair<float, float>((float)(j + 1) / (float)slices, (i+1) / (float)stacks));

	    }
        act_radius -= div_radius;
    }

    points.push_back(Point(0,0,0));
    points.push_back(Point(radius*sin(angle*(i+1)),0,radius*cos(angle*(i+1))));
    points.push_back(Point(radius*sin(angle*i),0,radius*cos(angle*i)));
    normals.push_back(Point(0,-1,0));
    normals.push_back(Point(0,-1,0));
    normals.push_back(Point(0,-1,0));
    textCoords.push_back(std::pair<float,float>(0,0));
    textCoords.push_back(std::pair<float,float>(float(i+1)/(float)stacks, 0));
    textCoords.push_back(std::pair<float,float>((float)i/(float)stacks, 0));;

    result.push_back(points);
    result.push_back(normals);
    allCoords.first = result;
    allCoords.second = textCoords;
    return allCoords;
}