#include "../include/translate.hpp"


Translate::Translate(float px,float py,float pz){
    t = Point(px,py,pz);
}

void Translate::apply_transformation(){
    glTranslatef(t.x,t.y,t.z);
}