#include "../include/color.hpp"

Color::Color(){
    diffuse = Point(200,200,200);
    ambient = Point(50,50,50);
    specular = Point(0,0,0);
    emissive = Point(0,0,0);
    shininess = 0;
    flag_rgb = 0;
}

Color::Color(Point _rgb){
    rgb = _rgb;
    flag_rgb = 1;
}

Color::Color(Point _diffuse, Point _ambient, Point _specular, Point _emissive, float _shininess){
    diffuse = _diffuse;
    ambient = _ambient;
    specular = _specular;
    emissive = _emissive;
    shininess = _shininess;
    flag_rgb = 0;
}

void Color::apply_color(){
    if (flag_rgb){
        glColor3f(rgb.x,rgb.y,rgb.z);
    }
    else{
        float d[4] = {diffuse.x/255, diffuse.y/255, diffuse.z/255, 1.0};
        float a[4] = {ambient.x/255, ambient.y/255, ambient.z/255, 1.0};
        float s[4] = {specular.x/255, specular.y/255, specular.z/255, 1.0};
        float e[4] = {emissive.x/255, emissive.y/255, emissive.z/255, 1.0};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
        glMaterialfv(GL_FRONT, GL_AMBIENT, a);
        glMaterialfv(GL_FRONT, GL_SPECULAR, s);
        glMaterialfv(GL_FRONT,GL_EMISSION, e);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
}