#include <stdio.h>
#include "../include/plane.hpp"
#include "../include/model.hpp"
#include "../include/box.hpp"
#include "../include/cone.hpp"
#include "../include/sphere.hpp"
#include "../include/cylinder.hpp"
#include "../include/torus.hpp"
#include "../include/bezier.hpp"
#include "../include/plane_torus.hpp"


int main(int argc, char** argv) {
    std::string file;
    std::vector<std::vector<Point>> points;
    std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> full;

    if (std::string(argv[1]) == "plane" && argc == 5){
        Plane plane = Plane(atoi(argv[2]),atoi(argv[3]));
        full = plane.generate_plane();

        file = std::string(argv[4]);
    }
    
    else if (std::string(argv[1]) == "box" && argc == 5){
        Box box = Box(atoi(argv[2]),atoi(argv[3]));
        full = box.generate_points();

        file = std::string(argv[4]);
    }

    else if (std::string(argv[1]) == "bezier" && argc == 5){
        Bezier bezier = Bezier(std::string(argv[2]),atoi(argv[3]));
        full = bezier.generate_points();

        file = std::string(argv[4]);
    }

    else if (std::string(argv[1]) == "sphere" && argc == 6){
        Sphere sphere = Sphere(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
        full = sphere.generate_points();

        file = std::string(argv[5]);
    }

    else if (std::string(argv[1]) == "inside_sphere" && argc == 6){
        Sphere sphere = Sphere(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
        full = sphere.generate_points();

        file = std::string(argv[5]);
    }

    else if (std::string(argv[1]) == "cone" && argc == 7) {
        Cone cone = Cone(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]));
        full = cone.generate_points();
        
        file = std::string(argv[6]);
    }

    else if (std::string(argv[1]) == "cylinder" && argc == 7) {
        Cylinder cylinder = Cylinder(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]));
        points = cylinder.generate_points();
        
        file = std::string(argv[6]);
    }

    else if (std::string(argv[1]) == "torus" && argc == 7){
        Torus torus = Torus(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]), atoi(argv[5]));
        points = torus.generate_points();

        file = std::string(argv[6]);
    }

    else if (std::string(argv[1]) == "plane_torus" && argc == 7){
        PTorus ptorus = PTorus(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]), atoi(argv[5]));
        points = ptorus.generate_points();

        file = std::string(argv[6]);
    }


    Model model = Model(full,points);
    model.save_file(file);

    return 0;
}