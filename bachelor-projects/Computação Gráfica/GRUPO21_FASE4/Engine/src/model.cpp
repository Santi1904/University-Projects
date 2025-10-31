#include "../include/model.hpp"

Model::Model(string _filename){
	filename = _filename;
    flag_texture = 0;
	color = Color();
}

void Model::add_color(Color _color){
    color = _color;
}


void Model::add_texture(string _texture){
    flag_texture = 1;
    texture_file = _texture;
}