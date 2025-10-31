#include "../include/scale.hpp"

Scale::Scale(float _x,float _y,float _z){
    s = Point(_x,_y,_z);
}


void Scale::apply_transformation(){
    glScalef(s.x,s.y,s.z);
}