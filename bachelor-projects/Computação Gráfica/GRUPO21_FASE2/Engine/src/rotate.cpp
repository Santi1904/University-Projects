#include "../include/rotate.hpp"

Rotate::Rotate(float _angle,float px,float py,float pz){
    angle = _angle;
    r = Point(px,py,pz);
}

void Rotate::apply_transformation(){
    glRotatef(angle,r.x,r.y,r.z);
}