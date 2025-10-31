#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "point.hpp"

class Color{
    public:
        int flag_rgb;
        Point rgb;
        Point diffuse;
        Point ambient;
        Point specular;
        Point emissive;
        float shininess;
        Color();
        Color(Point _rgb);
        Color(Point _diffuse, Point _ambient, Point _specular, Point _emissive, float _shininess);
        void apply_color();
};

#endif