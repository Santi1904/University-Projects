#include "../include/group.hpp"

Group::Group(){}

void Group::add_transformation(Transformation *t){
    transformations.push_back(t);
}

void Group::add_models(vector<Model> _models){
    models = _models;
}

void Group::add_group_child(Group *child){
    groupChildren.push_back(child);
}