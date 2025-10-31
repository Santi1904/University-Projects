#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "point.hpp"

class Sphere{
    private:
        float radius;
        int slices;
        int stacks;
    public:
        Sphere(float _radius, int _slices,int _stacks);
        std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> generate_points();
};

#endif
