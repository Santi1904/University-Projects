#include "../include/light_spotlight.hpp"

Light_spotlight::Light_spotlight(Point _s, Point _dir, float _cutoff, int _counter){
    s = _s;
    dir = _dir;
    cutoff = _cutoff;
    counter = _counter;
}

void Light_spotlight::apply_light(){
    GLfloat pos[4] = {s.x, s.y, s.z, 1.0};
    GLfloat d[3] = {dir.x, dir.y, dir.z};
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
    glLightfv(l, GL_SPOT_DIRECTION, d);
    glLightf(l, GL_SPOT_CUTOFF, cutoff);
}