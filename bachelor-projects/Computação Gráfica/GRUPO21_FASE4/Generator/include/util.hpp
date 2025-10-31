#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "point.hpp"

std::vector<float> split(const std::string& s, char separator);
std::vector<std::vector<float>> matrix_mult (std::vector<std::vector<float>> matrix1, std::vector<std::vector<float>> matrix2);
std::vector<std::vector<Point>> point_matrix_mult (std::vector<std::vector<Point>> matrix1, std::vector<std::vector<float>> matrix2);
std::vector<std::vector<Point>> matrix_point_mult (std::vector<std::vector<float>> matrix1, std::vector<std::vector<Point>> matrix2);
std::vector<float> normalize(std::vector<float> vector);
std::vector<float> vector_mult(std::vector<float> u, std::vector<float> v);
std::vector<std::vector<float>> init_normals(std::vector<Point> points);
std::vector<std::vector<float>> normals_calc(std::vector<Point> points);


#endif