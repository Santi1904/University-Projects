#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "tinyxml2.hpp"
#include "point.hpp"
#include "cam_settings.hpp"

using namespace std;
using namespace tinyxml2;

Settings parse(string filepath);
vector<Point> parse3D_file(string filepath);

