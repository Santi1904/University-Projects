#include "../include/util.hpp"


std::vector<float> split(const std::string& s, char separator) {
    std::vector<float> output;

    std::string::size_type prev_pos = 0, pos = 0;
    std::string use = s[0] == ' ' ? s.substr(1,s.size()-1) : s;

    while((pos = use.find(separator, pos)) != std::string::npos){
        std::string substring(use.substr(prev_pos, pos-prev_pos));

        output.push_back(atof(substring.c_str()));
        prev_pos = pos++;
    }

    output.push_back(atof(use.substr(prev_pos, pos-prev_pos).c_str()));

    return output;
}

std::vector<std::vector<float>> matrix_mult (std::vector<std::vector<float>> matrix1, std::vector<std::vector<float>> matrix2){
    std::vector<std::vector<float>> output;
    std::vector<float> line;
    for (int i=0; i<matrix2[0].size(); i++)
        line.push_back(0);
    for (int i=0; i<matrix1.size(); i++)
        output.push_back(line);


    for(int i=0; i<matrix1.size(); i++){    
        for(int j=0; j<matrix2[0].size(); j++){     
            for(int k=0; k<matrix1[i].size(); k++){    
                output[i][j]+=matrix1[i][k]*matrix2[k][j];
            }    
        }
    }

    return output;
}

std::vector<std::vector<Point>> point_matrix_mult (std::vector<std::vector<Point>> matrix1, std::vector<std::vector<float>> matrix2){
    std::vector<std::vector<Point>> output;
    std::vector<Point> line;
    
    for (int i=0; i<matrix2[0].size(); i++)
        line.push_back(Point(0,0,0));
    for (int i=0; i<matrix1.size(); i++)
        output.push_back(line);

    for(int i=0; i<matrix1.size(); i++){    
        for(int j=0; j<matrix2[0].size(); j++){      
            for(int k=0; k<matrix1[i].size(); k++){
                matrix1[i][k].mult_coef(matrix2[k][j]);
                output[i][j].sum_point(matrix1[i][k]);
                matrix1[i][k].mult_coef(1/matrix2[k][j]);
            }    
        }
    }

    return output;
}

std::vector<std::vector<Point>> matrix_point_mult (std::vector<std::vector<float>> matrix1, std::vector<std::vector<Point>> matrix2){
    std::vector<std::vector<Point>> output;
    std::vector<Point> line;
    for (int i=0; i<matrix2[0].size(); i++)
        line.push_back(Point(0,0,0));
    for (int i=0; i<matrix1.size(); i++)
        output.push_back(line);
    

    for(int i=0; i<matrix1.size(); i++){    
        for(int j=0; j<matrix2[0].size(); j++){      
            for(int k=0; k<matrix1[i].size(); k++){
                matrix2[k][j].mult_coef(matrix1[i][k]);
                output[i][j].sum_point(matrix2[k][j]);
                matrix2[k][j].mult_coef(1/matrix1[i][k]);
            }    
        }
    }

    return output;
}

std::vector<float> normalize(std::vector<float> vector){
    std::vector<float> result;

    float value = std::sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
    for (int i=0; i<3; i++)
        result.push_back(vector[i]/value);
    
    return result;
}

std::vector<float> vector_mult(std::vector<float> u, std::vector<float> v){
    std::vector<float> result;
    result.push_back(u[2]*v[1] - u[1]*v[2]);
    result.push_back(u[0]*v[2] - u[2]*v[0]);
    result.push_back(u[1]*v[0] - u[0]*v[1]);

    //if (result[0] > 1 || result[1] > 1 || result[2] > 1){
        //std::cout << "norm:   " << result[0] << " " << result[1] << " " << result[2] << std::endl;
    //normalize(result);
    //}

    return result;
}

std::vector<std::vector<float>> init_normals(std::vector<Point> points){
    std::vector<std::vector<float>> start_normals;

    for(int i=0; i<points.size(); i+=3){
        std::vector<float> u;
        std::vector<float> v;

        u.push_back(points[i+1].get_x() - points[i].get_x()); u.push_back(points[i+1].get_y() - points[i].get_y()); u.push_back(points[i+1].get_z() - points[i].get_z());
        v.push_back(points[i+2].get_x() - points[i].get_x()); v.push_back(points[i+2].get_y() - points[i].get_y()); v.push_back(points[i+2].get_z() - points[i].get_z());
        //std::vector<float> u_n = normalize(u);
        //std::vector<float> v_n = normalize(v);

        std::vector<float> mult = vector_mult(v,u);
        for (int j=0; j<3; j++){
            start_normals.push_back(mult);
            //std::cout << "mult:   " << mult[0] << " " << mult[1] << " " << mult[2] << std::endl;
        }

    }

    return start_normals;
}

std::vector<std::vector<float>> normals_calc(std::vector<Point> points){
    std::vector<std::vector<float>> result;
    std::vector<std::vector<float>> start_normals = init_normals(points);
    
    std::map<std::string, std::vector<float>> normal_map;
    //std::map<std::string, int> count_map;
    for (int i=0; i<points.size(); i++){
        points[i].zero_correction();
        std::string key = points[i].point_to_string();
        std::vector<float> vector = start_normals[i];
        if (normal_map.count(key) == 0){
            normal_map[key] = vector;
            //count_map[key] = 0;
        }
        for(int j=0; j<3; j++)
            normal_map[key][j] += vector[j]; 
        //count_map[key]++;
    }


    //std::map<std::string, std::vector<float>>::iterator it;
    //for (it = normal_map.begin(); it != normal_map.end(); it++){
    //    //std::cout << it->first << " : " << it->second[0] << " " << it->second[1] << " " << it->second[2] << '\n';
    //    for (int j=0; j<3; j++)
    //        it->second[j] /= count_map[it->first];
    //}

    for (int i=0; i<points.size(); i++)
        result.push_back(normalize(normal_map[points[i].point_to_string()]));

    //std::cout << start_normals[0][0] << " " << start_normals[0][1] << " " << start_normals[0][2] << "\n\n";

    return result;
}