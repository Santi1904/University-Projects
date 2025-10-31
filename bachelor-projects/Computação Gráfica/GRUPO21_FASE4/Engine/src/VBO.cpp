#include "../include/VBO.hpp"

VBO::VBO(){
    vertixCount = 0;
    indexCount = 0;
    glGenBuffers(4, buffers);
}