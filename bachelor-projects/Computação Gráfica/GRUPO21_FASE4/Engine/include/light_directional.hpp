#ifndef __LIGHT_DIRECTIONAL_HPP__
#define __LIGHT_DIRECTIONAL_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "light.hpp"
#include "point.hpp"

class Light_directional : public Light{
    public:
        Point dir;
        int counter;
        Light_directional(float _x, float _y, float _z, int _counter);
        void apply_light();
};

#endif