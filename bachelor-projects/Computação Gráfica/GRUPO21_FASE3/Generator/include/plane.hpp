#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <vector>
#include "point.hpp"

class Plane{
    private:
        int length;
        int divisions;
    public:
        Plane(int _length, int _divisions);
        std::vector<Point> generate_points(float div_l, float util_p, float fix, int flag);
        std::vector<Point> generate_plane();
};

#endif