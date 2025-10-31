#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include <vector>
#include <string>
#include <iostream>
#include "color.hpp"
#include "transformation.hpp"
#include "translate.hpp"
#include "rotate.hpp"
#include "scale.hpp"
#include "tinyxml2.hpp"
#include "point.hpp"
#include "model.hpp"

using namespace tinyxml2;
using namespace std;

class Group{
    public:
        vector<Transformation*> transformations;
        vector<Model> models;
        vector<Group*> groupChildren;
        Group();
        void add_transformation(Transformation *t);
        void add_models(vector<Model> _models);
        void add_group_child(Group *child);
};

#endif