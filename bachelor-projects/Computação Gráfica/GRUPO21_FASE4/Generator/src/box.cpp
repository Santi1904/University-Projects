#include "../include/box.hpp"


Box::Box(int _length, int _divisions) {
    length = _length;
    divisions = _divisions;
}

std::pair<std::vector<std::vector<Point>> ,std::vector<std::pair<float,float>>> Box::generate_points(){
    std::vector<Point> _points;
    std::vector<Point> points_;
    std::vector<Point> _points_;
    std::vector<std::pair<float,float>> _textCoords;
    std::vector<std::pair<float,float>> textCoords_;
    std::vector<std::pair<float,float>> _textCoords_;
    std::vector<Point> _normals;
    std::vector<Point> normals_;
    std::vector<Point> _normals_;
    std::pair<std::vector<std::vector<Point>> , std::vector<std::pair<float,float>>> allCoords_;
    std::pair<std::vector<std::vector<Point>> , std::vector<std::pair<float,float>>> _allCoords_;
    std::pair<std::vector<std::vector<Point>> , std::vector<std::pair<float,float>>> _allCoords;

    std::vector<std::vector<Point>> result_;
    std::vector<Point> resultPoints;
    std::vector<Point> resultNormals;

    std::vector<std::pair<float,float>> resulText;

    std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> boxCoords;

    float div_l = (float)length / (float)divisions;
    float util_p = (float)length / 2;
    
    Plane plane = Plane(length,divisions);
    
    allCoords_ = plane.generate_points(div_l,util_p,util_p,0);
    points_ = allCoords_.first[0];
    normals_ = allCoords_.first[1];
    textCoords_ = allCoords_.second;

    _allCoords_ = plane.generate_points(div_l,util_p,util_p,1);
    _points_ = _allCoords_.first[0];
    _normals_ = _allCoords_.first[1];
    _textCoords_ = _allCoords_.second;

    _allCoords = plane.generate_points(div_l,util_p,util_p,2);
    _points = _allCoords.first[0];
    _normals = _allCoords.first[1];
    _textCoords = _allCoords.second;

    for(int i=0; i<points_.size(); i++){
        resultPoints.push_back(points_[i]);
        resultNormals.push_back(normals_[i]);
        resulText.push_back(textCoords_[i]);
    }
    for(int i=0; i<_points_.size(); i++){
        resultPoints.push_back(_points_[i]);
        resultNormals.push_back(_normals_[i]);
        resulText.push_back(_textCoords_[i]);
    }

    for(int i=0; i<_points.size(); i++){
        resultPoints.push_back(_points[i]);
        resultNormals.push_back(_normals[i]);
        resulText.push_back(_textCoords[i]);
    }
    result_.push_back(resultPoints);
    result_.push_back(resultNormals);
    boxCoords.first = result_;
    boxCoords.second = resulText;

    return boxCoords;
}