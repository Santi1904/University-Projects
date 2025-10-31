#include "../include/cam_settings.hpp"

Settings::Settings(){
    width = 0;
}

Settings::Settings(int w, int h, Point p, Point l, Point u, Point pr, vector<string> m){
    width = w;
    height = h;
    position = p;
    lookAt = l;
    up = u;
    projection = pr;
    models = m;
}