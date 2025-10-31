#ifndef CONE_H
#define CONE_H

#include <vector>
#include "point.hpp"

class Cone{
    private:
        int radius;
        int heigth;
        int slices;
        int stacks;
    public:
        Cone(int _radius, int _heigth, int _slices, int _stack);
        std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> generate_points();
};

#endif