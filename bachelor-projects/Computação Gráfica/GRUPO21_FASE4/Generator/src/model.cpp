#include "../include/model.hpp"


Model::Model(std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> _full, std::vector<std::vector<Point>> _points) {
    full = _full;
    points = _points;
}

void Model::save_file(std::string file) {
    std::ofstream myfile("../../Engine/models/" + file, std::ios::out);
    if (points.size() > 0){
        int size = points[0].size();

        myfile << size << "\n";

        if (points.size() == 1){
            std::vector<std::vector<float>> normals = normals_calc(points[0]);
            for(int i=0; i<size; i++){
                myfile << points[0][i].get_x() << " " << points[0][i].get_y() << " " << points[0][i].get_z() << " "; 
                myfile << normals[i][0] << " " << normals[i][1] << " " << normals[i][2] << "\n";
            }
        }

        else {
            for(int i=0; i<size; i++){
                myfile << points[0][i].get_x() << " " << points[0][i].get_y() << " " << points[0][i].get_z() << " "; 
                myfile << points[1][i].get_x() << " " << points[1][i].get_y() << " " << points[1][i].get_z() << "\n";
            }
        }
    }

    else {
        int size = full.first[0].size();

        myfile << size << "\n";

        if (full.first.size() == 1){
            std::vector<std::vector<float>> normals = normals_calc(full.first[0]);
            for(int i=0; i<size; i++){
                myfile << full.first[0][i].get_x() << " " << full.first[0][i].get_y() << " " << full.first[0][i].get_z() << " "; 
                myfile << normals[i][0] << " " << normals[i][1] << " " << normals[i][2] << " ";
                myfile << full.second[i].first <<  " " << full.second[i].second << " " << "\n";
            }
        }

        else {
            for(int i=0; i<size; i++){
                myfile << full.first[0][i].get_x() << " " << full.first[0][i].get_y() << " " << full.first[0][i].get_z() << " "; 
                myfile << full.first[1][i].get_x() << " " << full.first[1][i].get_y() << " " << full.first[1][i].get_z() << " ";
                myfile << full.second[i].first <<  " " << full.second[i].second << " " << "\n";
            }
        }

    }
}