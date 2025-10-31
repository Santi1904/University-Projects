#include "../include/box.hpp"


Box::Box(int _length, int _divisions) {
    length = _length;
    divisions = _divisions;
}

std::vector<Point> Box::generate_points(){
    std::vector<Point> points;

    std::vector<Point> _points;
    std::vector<Point> points_;
    std::vector<Point> _points_;
    float div_l = (float)length / (float)divisions;
    float util_p = (float)length / 2;

    Plane plane = Plane(length,divisions);
    points_ = plane.generate_points(div_l,util_p,util_p,0);
    _points = plane.generate_points(div_l,util_p,util_p,1);
    _points_ = plane.generate_points(div_l,util_p,util_p,2);

    for(int i=0; i<points_.size(); i++)
        points.push_back(points_[i]);
    
    for(int i=0; i<_points.size(); i++)
        points.push_back(_points[i]);

    for(int i=0; i<_points_.size(); i++)
        points.push_back(_points_[i]);


    return points;
}