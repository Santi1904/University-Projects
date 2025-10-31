#include "../include/group.hpp"

Group::Group(){
    color = Point(1,1,1);
}

void Group::add_transformation(Transformation *t){
    transformations.push_back(t);
}

void Group::add_models(vector<string> _models){
    models = _models;
}

void Group::add_group_child(Group *child){
    groupChildren.push_back(child);
}

void Group::add_color(Color _color){
    color = _color;
}
