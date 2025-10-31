#include "../include/xml_data.hpp"

XML::XML(){}

void XML::add_cam_settings(Settings _settings){
    settings = _settings;
}

void XML::add_group(Group* _group){
    groups.push_back(_group);
}

void XML::add_window_settings(int width, int height){
    w_width = width;
    w_height = height;
}

void XML::add_lights(vector<Light*> _lights){
    lights = _lights;
    light_count = _lights.size();
}