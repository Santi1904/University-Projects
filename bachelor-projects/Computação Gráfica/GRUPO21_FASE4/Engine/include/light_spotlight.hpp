#ifndef __LIGHT_SPOTLIGHT_HPP__
#define __LIGHT_SPOTLIGHT_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "light.hpp"
#include "point.hpp"

class Light_spotlight : public Light{
    public:
        Point s;
        Point dir;
        float cutoff;
        int counter;
        Light_spotlight(Point _s, Point _dir, float _cutoff, int _counter);
        void apply_light();
};

#endif