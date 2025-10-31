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
        std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> generate_points(float div_l, float util_p, float fix, int flag);
        std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> generate_plane();
};

#endif