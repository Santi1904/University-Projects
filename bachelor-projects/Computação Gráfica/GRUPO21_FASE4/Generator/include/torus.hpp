#ifndef TORUS_H
#define TORUS_H

#include <vector>
#include "point.hpp"

class Torus{
    private:
        int out_radius;
        int in_radius;
        int slices;
        int stacks;
    public:
        Torus(int _out_radius, int in_radius, int _slices, int _stacks);
        std::vector<std::vector<Point>> generate_points();
};

#endif