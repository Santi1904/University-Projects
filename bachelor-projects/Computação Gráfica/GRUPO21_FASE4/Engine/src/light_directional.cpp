#include "../include/light_directional.hpp"

Light_directional::Light_directional(float px, float py, float pz, int _counter){
    dir = Point(px,py,pz);
    counter = _counter;
}

void Light_directional::apply_light(){
    GLfloat d[4] = {dir.x, dir.y, dir.z, 0.0};
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
    glLightfv(l, GL_POSITION, d);
}