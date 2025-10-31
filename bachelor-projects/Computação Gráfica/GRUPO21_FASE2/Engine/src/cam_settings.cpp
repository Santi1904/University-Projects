#include "../include/cam_settings.hpp"

Settings::Settings(){}

Settings::Settings(Point p, Point l, Point u, Point pr){
    position = p;
    lookAt = l;
    up = u;
    projection = pr;
}