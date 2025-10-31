#ifndef __VBO_HPP__
#define __VBO_HPP__


#include <vector>
#include <iostream>
#include "point.hpp"
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

class VBO{
    public:
        GLuint buffers[4];
	    int vertixCount;
        int indexCount;
        VBO();
};

#endif