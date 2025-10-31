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