#ifndef CYLINDER_H
#define CYLINDER_H

#include <vector>
#include "point.hpp"

class Cylinder{
    private:
        int radius;
        int heigth;
        int slices;
        int stacks;
    public:
        Cylinder(int _radius, int _heigth, int _slices, int _stack);
        std::vector<std::vector<Point>> generate_points();
};

#endif