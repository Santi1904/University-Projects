#include "../include/model.hpp"


Model::Model(std::vector<Point> _points) {
    points = _points;
}

void Model::save_file(std::string file) {
    std::ofstream myfile("../../Engine/models/" + file, std::ios::out);
    int size = points.size();

    myfile << size << "\n";

    for(int i=0; i<size; i++){
        myfile << points[i].get_x() << " " << points[i].get_y() << " " << points[i].get_z() << "\n";
    }
}