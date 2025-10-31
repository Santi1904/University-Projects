#ifndef BOX_H
#define BOX_H

#include <vector>
#include "point.hpp"
#include "plane.hpp"

class Box{
    private:
        int length;
        int divisions;
    public:
        Box(int _length, int _divisions);       
        std::pair<std::vector<std::vector<Point>> ,std::vector<std::pair<float,float>>> generate_points();
};

#endif