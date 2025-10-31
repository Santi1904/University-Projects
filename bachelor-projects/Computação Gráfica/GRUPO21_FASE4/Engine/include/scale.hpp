#ifndef __SCALE_HPP__
#define __SCALE_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "transformation.hpp"
#include "point.hpp"

class Scale : public Transformation{
    public:
        Point s;
        Scale(float _x,float _y,float _z);
        void apply_transformation();
};

#endif