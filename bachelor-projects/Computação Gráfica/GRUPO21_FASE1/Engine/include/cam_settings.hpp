#pragma once
#include <vector>
#include "point.hpp"

using namespace std;

class Settings{
    public:
        int width;
        int height;
        Point position;
        Point lookAt;
        Point up;
        Point projection;
        vector<string> models;

        Settings();
        Settings(int width, int height, Point position, Point lookAt, Point up,  Point projection, vector<string> models);
    
};
