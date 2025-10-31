#include "../include/color.hpp"

Color::Color(){}

Color::Color(Point _rgb){
    rgb = _rgb;
}

void Color::apply_color(){
    glColor3f(rgb.x,rgb.y,rgb.z);
}