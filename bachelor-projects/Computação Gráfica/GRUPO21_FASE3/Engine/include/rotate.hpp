#ifndef __ROTATE_HPP__
#define __ROTATE_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "transformation.hpp"
#include "point.hpp"

class Rotate : public Transformation{
    public:
        float angle;
        float time;
        Point r;
        Rotate(float _x,float _y, float _z);
        void apply_transformation();
        void add_time(float _time);
        void add_angle(float _angle);
};

#endif