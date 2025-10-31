#include "../include/VBO.hpp"

VBO::VBO(){
    vertixCount=0;
	indexCount=0;
}


void VBO::draw(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexes);
    glBindBuffer(GL_ARRAY_BUFFER,vertixes);
    glVertexPointer(3,GL_FLOAT,0,0);

    glDrawElements(GL_TRIANGLES,indexCount,GL_UNSIGNED_INT,NULL);

}