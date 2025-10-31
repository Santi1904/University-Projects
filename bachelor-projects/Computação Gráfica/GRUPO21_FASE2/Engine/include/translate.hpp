#ifndef __TRANSLATE_HPP__
#define __TRANSLATE_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "transformation.hpp"
#include "point.hpp"

class Translate : public Transformation {
    public:
        Point t;
        Translate(float _x,float _y,float _z);
        void apply_transformation();
};

#endif