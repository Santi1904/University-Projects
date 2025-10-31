#include "../include/plane.hpp"


Plane::Plane(int _length, int _divisions) {
    length = _length;
    divisions = _divisions;
}


std::vector<Point> Plane::generate_points(float div_l, float util_p, float fix, int flag){
    std::vector<Point> points;
    // flag 0 -> plane x z (y fix)
    // flag 1 -> plane x y (z fix)
    // flag 2 -> plane y z (x fix)
    
    for(float start = -util_p; start < util_p; start += div_l) 

        for(float c_point = -util_p; c_point < util_p; c_point += div_l){

            if (flag == 0){

                points.push_back(Point(start,fix,c_point));
                points.push_back(Point(start,fix,c_point+div_l));
                points.push_back(Point(start+div_l,fix,c_point+div_l));

                points.push_back(Point(start,-fix,c_point));
                points.push_back(Point(start+div_l,-fix,c_point+div_l));
                points.push_back(Point(start,-fix,c_point+div_l));


                points.push_back(Point(start+div_l,fix,c_point+div_l));
                points.push_back(Point(start+div_l,fix,c_point));
                points.push_back(Point(start,fix,c_point));

                points.push_back(Point(start+div_l,-fix,c_point+div_l));
                points.push_back(Point(start,-fix,c_point));
                points.push_back(Point(start+div_l,-fix,c_point));
            }

            else if (flag == 1){
                points.push_back(Point(start,c_point,fix));
                points.push_back(Point(start+div_l,c_point+div_l,fix));
                points.push_back(Point(start,c_point+div_l,fix));

                points.push_back(Point(start,c_point,-fix));
                points.push_back(Point(start,c_point+div_l,-fix));
                points.push_back(Point(start+div_l,c_point+div_l,-fix));


                points.push_back(Point(start+div_l,c_point+div_l,fix));
                points.push_back(Point(start,c_point,fix));
                points.push_back(Point(start+div_l,c_point,fix));

                points.push_back(Point(start+div_l,c_point+div_l,-fix));
                points.push_back(Point(start+div_l,c_point,-fix));
                points.push_back(Point(start,c_point,-fix));
            }

            else{
                points.push_back(Point(fix,start,c_point));
                points.push_back(Point(fix,start+div_l,c_point+div_l));
                points.push_back(Point(fix,start,c_point+div_l));

                points.push_back(Point(-fix,start,c_point));
                points.push_back(Point(-fix,start,c_point+div_l));
                points.push_back(Point(-fix,start+div_l,c_point+div_l));


                points.push_back(Point(fix,start+div_l,c_point+div_l));
                points.push_back(Point(fix,start,c_point));
                points.push_back(Point(fix,start+div_l,c_point));

                points.push_back(Point(-fix,start+div_l,c_point+div_l));
                points.push_back(Point(-fix,start+div_l,c_point));
                points.push_back(Point(-fix,start,c_point));
            }

        }
    
    return points;
}

std::vector<Point> Plane::generate_plane(){
    float div_l = (float)length / (float)divisions;
    float util_p = (float)length / 2;

    return generate_points(div_l,util_p,0,0);
}