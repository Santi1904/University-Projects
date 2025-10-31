#ifndef __XML_DATA_HPP__
#define __XML_DATA_HPP__

#include <vector>
#include "cam_settings.hpp"
#include "group.hpp"

using namespace std;

class XML {
    public:
        int w_width;
        int w_height;
        Settings settings;
        vector<Group*> groups;
        XML();
        void add_cam_settings(Settings _settings);
        void add_group(Group* _group);
        void add_window_settings(int width, int height);
};

#endif