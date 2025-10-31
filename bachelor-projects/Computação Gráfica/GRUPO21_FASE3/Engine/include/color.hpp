#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "point.hpp"

class Color{
    public:
        Point rgb;
        Color();
        Color(Point _rgb);
        void apply_color();
};

#endif