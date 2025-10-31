#include "../include/bezier.hpp"


Bezier::Bezier(std::string _path, int _level) {
    path = _path;
    level = _level;
}

std::vector<std::vector<float>> Bezier::generate_bezier_matrix(){
    std::vector<std::vector<float>> bezier_matrix;
    std::vector<float> line1;
    line1.push_back(-1);line1.push_back(3);line1.push_back(-3);line1.push_back(1);
    std::vector<float> line2;
    line2.push_back(3);line2.push_back(-6);line2.push_back(3);line2.push_back(0);
    std::vector<float> line3;
    line3.push_back(-3);line3.push_back(3);line3.push_back(0);line3.push_back(0);
    std::vector<float> line4;
    line4.push_back(1);line4.push_back(0);line4.push_back(0);line4.push_back(0);
    bezier_matrix.push_back(line1);bezier_matrix.push_back(line2);bezier_matrix.push_back(line3);bezier_matrix.push_back(line4);

    return bezier_matrix;
}

std::vector<std::vector<Point>> Bezier::gen_points_matrix(std::vector<float> patch_p, std::vector<Point> points){
    std::vector<std::vector<Point>> output;

    std::vector<Point> add;
    for(int i=0; i<4; i++){
        add.push_back(points[patch_p[i]]);
    }
    output.push_back(add);

    std::vector<Point> add2;
    for(int i=4; i<8; i++){
        add2.push_back(points[patch_p[i]]);
    }
    output.push_back(add2);
    
    std::vector<Point> add3;
    for(int i=8; i<12; i++){
        add3.push_back(points[patch_p[i]]);
    }
    output.push_back(add3);

    std::vector<Point> add4;
    for(int i=12; i<16; i++){
        add4.push_back(points[patch_p[i]]);
    }
    output.push_back(add4);
        

    return output;
}

std::vector<Point> Bezier::gen_final_points(std::vector<std::vector<float>> u_s, std::vector<std::vector<float>> v_s, std::vector<std::vector<Point>> bezier_mult_points){
    std::vector<std::vector<Point>> gen_points = point_matrix_mult(matrix_point_mult(u_s,bezier_mult_points),v_s);
    std::vector<Point> output;
    for (int i=0; i<gen_points.size(); i++)
        for(int j=0; j<gen_points[i].size(); j++)
            output.push_back(gen_points[i][j]);
    return output;
}


std::vector<Point> Bezier::generate_points(){
    std::string full_path = "../patches/" + path, line;
    std::ifstream file (full_path);
    std::vector<std::vector<float>> patches;
    std::vector<Point> c_points;
    std::vector<Point> points;

    std::vector<std::vector<float>> bezier_matrix = generate_bezier_matrix();
    
    std::getline(file, line);
    int patches_nr = std::atoi(line.c_str());
    for (int i=0; i<patches_nr; i++){
        std::getline(file, line);
        patches.push_back(split(line, ' '));
    }

    std::getline(file, line);
    int points_nr = std::atoi(line.c_str());
    for (int i=0; i<points_nr; i++){
        std::getline(file,line);
        std::vector<float> coords = split(line, ' ');
        c_points.push_back(Point(coords[0],coords[1],coords[2]));
    }

    
    for (int i=0; i<patches.size(); i++){
        std::vector<std::vector<Point>> patch_points = gen_points_matrix(patches[i], c_points);
        std::vector<std::vector<Point>> bezier_mult_points = point_matrix_mult(matrix_point_mult(bezier_matrix,patch_points),bezier_matrix);
        std::vector<std::vector<Point>> temp_points;
        for (int u=0; u<=level; u++){
            std::vector<std::vector<float>> u_s;
            std::vector<float> u_line;
            float u_v = (float)u/(float)level;
            u_line.push_back(u_v*u_v*u_v);u_line.push_back(u_v*u_v);u_line.push_back(u_v);u_line.push_back(1);
            u_s.push_back(u_line);

            std::vector<Point> temp_line;
            for (int v=0; v<=level; v++){
                std::vector<std::vector<float>> v_s;
                float v_v = (float)v/(float)level;
                std::vector<float> v1_line;
                v1_line.push_back(v_v*v_v*v_v);
                std::vector<float> v2_line;
                v2_line.push_back(v_v*v_v);
                std::vector<float> v3_line;
                v3_line.push_back(v_v);
                std::vector<float> v4_line;
                v4_line.push_back(1);
                v_s.push_back(v1_line);v_s.push_back(v2_line);v_s.push_back(v3_line);v_s.push_back(v4_line);

                std::vector<Point> gen_points = gen_final_points(u_s,v_s,bezier_mult_points);
                for (int k=0; k<gen_points.size(); k++)
                    temp_line.push_back(gen_points[k]);
            }
            temp_points.push_back(temp_line);
        }

        
        for (int x=0; x<temp_points.size()-1; x++)
            for (int y=0; y<temp_points.size()-1; y++){
                points.push_back(temp_points[x][y]);
                points.push_back(temp_points[x][y+1]);
                points.push_back(temp_points[x+1][y]);
                points.push_back(temp_points[x+1][y]);
                points.push_back(temp_points[x][y+1]);
                points.push_back(temp_points[x+1][y+1]);
            }
    }

    return points;
}