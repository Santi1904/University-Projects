#ifndef __LIGHT_POINT_HPP__
#define __LIGHT_POINT_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "light.hpp"
#include "point.hpp"

class Light_point : public Light{
    public:
        Point p;
        int counter;
        Light_point(float _x, float _y, float _z, int _counter);
        void apply_light();
};

#endif