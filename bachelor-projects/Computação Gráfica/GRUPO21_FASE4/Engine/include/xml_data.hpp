#ifndef __XML_DATA_HPP__
#define __XML_DATA_HPP__

#include <vector>
#include <unordered_map>
#include "cam_settings.hpp"
#include "group.hpp"
#include "light.hpp"

using namespace std;

class XML {
    public:
        int w_width;
        int w_height;
        int light_count;
        Settings settings;
        vector<Group*> groups;
        vector<Light*> lights;
        XML();
        void add_cam_settings(Settings _settings);
        void add_group(Group* _group);
        void add_window_settings(int width, int height);
        void add_lights(vector<Light*> _lights);
};

#endif