#ifndef __TRANSLATE_HPP__
#define __TRANSLATE_HPP__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
#include <vector>

#include "transformation.hpp"
#include "point.hpp"

using namespace std;

class Translate : public Transformation {
    public:
        Point t;
        float time;
        int flag_g;
        int flag_align;
        static int flag_curves;
        int point_count;
        vector<Point> cat_points;
        Translate(float _x,float _y,float _z);
        Translate(float _time, int _align, vector<Point> curves);
        void apply_transformation();
        void getGlobalCatmullRomPoint(float gt, Point &pos, Point &deriv);
        void getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, Point &pos, Point &deriv);
        void multMatrixVector(float *m, float *v, float *res);
        void renderCatmullRomCurve();
};


#endif