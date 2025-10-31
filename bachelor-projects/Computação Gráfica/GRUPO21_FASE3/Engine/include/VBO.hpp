#ifndef __VBO_HPP__
#define __VBO_HPP__


#include <vector>
#include "point.hpp"
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;

class VBO{
    public:
        GLuint vertixes;
	    GLuint indexes;
	    int vertixCount;
	    int indexCount;
        VBO();
        void draw();
};

#endif