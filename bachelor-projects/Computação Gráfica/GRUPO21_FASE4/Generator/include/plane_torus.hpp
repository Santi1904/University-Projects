#ifndef PLANE_TORUS_H
#define PLANE_TORUS_H

#include <vector>
#include "point.hpp"

class PTorus{
    private:
        int out_radius;
        int in_radius;
        int slices;
        int stacks;
    public:
        PTorus(int _out_radius, int in_radius, int _slices, int _stacks);
        std::vector<std::vector<Point>> generate_points();
};

#endif