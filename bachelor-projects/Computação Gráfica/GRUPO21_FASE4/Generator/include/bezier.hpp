#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "util.hpp"


class Bezier{
    private:
        std::string path;
        int level;
    public:
        Bezier(std::string _path, int _level);
        std::vector<std::vector<float>> generate_bezier_matrix();
        std::vector<std::vector<Point>> gen_points_matrix(std::vector<float> patch_p, std::vector<Point> points);
        std::vector<Point> gen_final_points(std::vector<std::vector<float>> u_s, std::vector<std::vector<float>> v_s, std::vector<std::vector<Point>> bezier_mult_points);
        std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> generate_points();
};

#endif