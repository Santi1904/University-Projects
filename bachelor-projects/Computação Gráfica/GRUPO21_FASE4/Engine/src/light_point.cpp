#include "../include/light_point.hpp"

Light_point::Light_point(float px, float py, float pz, int _counter){
    p = Point(px,py,pz);
    counter = _counter;
}

void Light_point::apply_light(){
    GLfloat pos[4] = {p.x, p.y, p.z, 1.0};
    GLenum l;
    switch(counter){
        case 0: l = GL_LIGHT0; break;
        case 1: l = GL_LIGHT1; break;
        case 2: l = GL_LIGHT2; break;
        case 3: l = GL_LIGHT3; break;
        case 4: l = GL_LIGHT4; break;
        case 5: l = GL_LIGHT5; break;
        case 6: l = GL_LIGHT6; break;
        case 7: l = GL_LIGHT7; break;
    }
    glLightfv(l, GL_POSITION, pos);
}