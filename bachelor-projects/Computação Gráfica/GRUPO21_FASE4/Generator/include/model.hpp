#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <fstream>
#include "point.hpp"
#include "util.hpp"


class Model{
    private:
        std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> full;
        std::vector<std::vector<Point>> points;
    
    public:
        Model(std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> _full, std::vector<std::vector<Point>> _points);
        void save_file(std::string file);
};

#endif