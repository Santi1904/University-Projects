#include "../include/plane.hpp"


Plane::Plane(int _length, int _divisions) {
    length = _length;
    divisions = _divisions;
}


std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> Plane::generate_points(float div_l, float util_p, float fix, int flag){
    std::vector<Point> points;
    std::vector<std::pair<float,float>> textCoords;
    std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> allCoords;
    std::vector<Point> normals;
    std::vector<std::vector<Point>> result;
    float s,t;
    // flag 0 -> plane x z (y fix)
    // flag 1 -> plane x y (z fix)
    // flag 2 -> plane y z (x fix)
    
    for(float start = -util_p; start < util_p; start += div_l) 

        for(float c_point = -util_p; c_point < util_p; c_point += div_l){

            if (flag == 0){

                points.push_back(Point(start,fix,c_point));
                points.push_back(Point(start,fix,c_point+div_l));
                points.push_back(Point(start+div_l,fix,c_point+div_l));
                normals.push_back(Point(0,1,0));
                normals.push_back(Point(0,1,0));
                normals.push_back(Point(0,1,0));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(0,1));
                textCoords.push_back(std::pair<float,float>(1,1));
                
                points.push_back(Point(start,-fix,c_point));
                points.push_back(Point(start+div_l,-fix,c_point+div_l));
                points.push_back(Point(start,-fix,c_point+div_l));
                normals.push_back(Point(0,-1,0));
                normals.push_back(Point(0,-1,0));
                normals.push_back(Point(0,-1,0));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(0,1));
                

                points.push_back(Point(start+div_l,fix,c_point+div_l));
                points.push_back(Point(start+div_l,fix,c_point));
                points.push_back(Point(start,fix,c_point));
                normals.push_back(Point(0,1,0));
                normals.push_back(Point(0,1,0));
                normals.push_back(Point(0,1,0));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(1,0));
                textCoords.push_back(std::pair<float,float>(0,0));
                
                
                points.push_back(Point(start+div_l,-fix,c_point+div_l));
                points.push_back(Point(start,-fix,c_point));
                points.push_back(Point(start+div_l,-fix,c_point));
                normals.push_back(Point(0,-1,0));
                normals.push_back(Point(0,-1,0));
                normals.push_back(Point(0,-1,0));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(1,0));
            }

            else if (flag == 1){
                points.push_back(Point(start,c_point,fix));
                points.push_back(Point(start+div_l,c_point+div_l,fix));
                points.push_back(Point(start,c_point+div_l,fix));
                normals.push_back(Point(0,0,1));
                normals.push_back(Point(0,0,1));
                normals.push_back(Point(0,0,1));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(0,1));             


                points.push_back(Point(start,c_point,-fix));
                points.push_back(Point(start,c_point+div_l,-fix));
                points.push_back(Point(start+div_l,c_point+div_l,-fix));
                normals.push_back(Point(0,0,-1));
                normals.push_back(Point(0,0,-1));
                normals.push_back(Point(0,0,-1));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(0,1));
                textCoords.push_back(std::pair<float,float>(1,1));

                points.push_back(Point(start+div_l,c_point+div_l,fix));
                points.push_back(Point(start,c_point,fix));
                points.push_back(Point(start+div_l,c_point,fix));
                normals.push_back(Point(0,0,1));
                normals.push_back(Point(0,0,1));
                normals.push_back(Point(0,0,1));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(1,0));

                points.push_back(Point(start+div_l,c_point+div_l,-fix));
                points.push_back(Point(start+div_l,c_point,-fix));
                points.push_back(Point(start,c_point,-fix));
                normals.push_back(Point(0,0,-1));
                normals.push_back(Point(0,0,-1));
                normals.push_back(Point(0,0,-1));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(1,0));
                textCoords.push_back(std::pair<float,float>(0,0));
            }

            else{
                points.push_back(Point(fix,start,c_point));
                points.push_back(Point(fix,start+div_l,c_point+div_l));
                points.push_back(Point(fix,start,c_point+div_l));
                normals.push_back(Point(1,0,0));
                normals.push_back(Point(1,0,0));
                normals.push_back(Point(1,0,0));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(1,0));

                points.push_back(Point(-fix,start,c_point));
                points.push_back(Point(-fix,start,c_point+div_l));
                points.push_back(Point(-fix,start+div_l,c_point+div_l));
                normals.push_back(Point(-1,0,0));
                normals.push_back(Point(-1,0,0));
                normals.push_back(Point(-1,0,0));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(1,0));
                textCoords.push_back(std::pair<float,float>(1,1));


                points.push_back(Point(fix,start+div_l,c_point+div_l));
                points.push_back(Point(fix,start,c_point));
                points.push_back(Point(fix,start+div_l,c_point));
                normals.push_back(Point(1,0,0));
                normals.push_back(Point(1,0,0));
                normals.push_back(Point(1,0,0));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(0,0));
                textCoords.push_back(std::pair<float,float>(0,1));

                points.push_back(Point(-fix,start+div_l,c_point+div_l));
                points.push_back(Point(-fix,start+div_l,c_point));
                points.push_back(Point(-fix,start,c_point));
                normals.push_back(Point(-1,0,0));
                normals.push_back(Point(-1,0,0));
                normals.push_back(Point(-1,0,0));
                textCoords.push_back(std::pair<float,float>(1,1));
                textCoords.push_back(std::pair<float,float>(0,1));
                textCoords.push_back(std::pair<float,float>(0,0));             
            }

        }
    
    result.push_back(points);
	result.push_back(normals);
	allCoords.first = result;
	allCoords.second = textCoords;
	return allCoords;
}

std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> Plane::generate_plane(){
    float div_l = (float)length / (float)divisions;
    float util_p = (float)length / 2;

    return generate_points(div_l,util_p,0,0);
}