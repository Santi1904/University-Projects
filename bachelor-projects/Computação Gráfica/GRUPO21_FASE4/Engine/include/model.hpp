#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#ifdef __APPLE__
#include <il.h>
#else
#include <GL/glew.h>
#include <IL/il.h>
#endif


#include <iostream>
#include "../include/color.hpp"
#include <string>
using namespace std;

class Model{
    public:
        string filename;
        string texture_file;
        int flag_texture;
        Color color;
        Model(string _filename);
        void add_color(Color _color);
        void add_texture(string _texture);
};

#endif