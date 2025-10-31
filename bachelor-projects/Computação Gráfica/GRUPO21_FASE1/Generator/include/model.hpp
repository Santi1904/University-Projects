#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <fstream>
#include "point.hpp"


class Model{
    private:
        std::vector<Point> points;
    
    public:
        Model(std::vector<Point> points);
        void save_file(std::string file);
};

#endif