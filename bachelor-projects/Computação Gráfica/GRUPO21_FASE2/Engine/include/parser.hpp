#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "tinyxml2.hpp"
#include "point.hpp"
#include "color.hpp"
#include "xml_data.hpp"
#include "group.hpp"

using namespace std;
using namespace tinyxml2;

Settings parse_cam_settings(XMLElement *camera);
Group *parseGroup(XMLElement *node);
XML *parse(string filepath);
vector<Point> parse3D_file(string filepath);

#endif