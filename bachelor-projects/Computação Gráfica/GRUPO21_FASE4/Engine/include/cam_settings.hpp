#ifndef __CAM_SETTINGS_HPP__
#define __CAM_SETTINGS_HPP__

#include <vector>
#include "point.hpp"

using namespace std;

class Settings{
    public:
        Point position;
        Point lookAt;
        Point up;
        Point projection;

        Settings();
        Settings(Point position, Point lookAt, Point up,  Point projection);
    
};

#endif