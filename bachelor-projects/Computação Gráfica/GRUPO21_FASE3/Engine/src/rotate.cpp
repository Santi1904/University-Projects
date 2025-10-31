#include "../include/rotate.hpp"

Rotate::Rotate(float px,float py,float pz){
    r = Point(px,py,pz);
    angle = -1;
    time = -1;
}

void Rotate::add_time(float _time){
    time = _time;
}

void Rotate::add_angle(float _angle){
    angle = _angle;
}

void Rotate::apply_transformation(){
    if(time != -1){
        angle = ((float)glutGet(GLUT_ELAPSED_TIME) * 360 / 1000) / ((float)time);
    }
    glRotatef(angle,r.x,r.y,r.z);
}