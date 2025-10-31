#define _USE_MATH_DEFINES
#include <math.h>
#include "../include/sphere.hpp"


Sphere::Sphere(float _radius, int _slices, int _stacks) {
    radius = _radius;
    slices = _slices;
    stacks = _stacks;
}


std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> Sphere::generate_points(){
    std::pair<std::vector<std::vector<Point>>, std::vector<std::pair<float,float>>> allCoords;
	std::vector<std::pair<float,float>> textCoords;
	std::vector<Point> points;
	std::vector<Point> normals;
	std::vector<std::vector<Point>> result;
	float alpha,_beta,px,py,pz,s,t;
	float alphaVar = 2*M_PI/slices; 
	float betaVar = M_PI/stacks;
	int stackPoint,slicePoint;
	for(stackPoint=0;stackPoint<stacks;stackPoint++){
		_beta = stackPoint * betaVar;
		for(slicePoint=0;slicePoint<slices;slicePoint++){
			alpha = slicePoint * alphaVar;
			px = radius * cos(M_PI/2 - _beta) * sin(alpha);
			py = radius * sin(M_PI/2 - _beta);
			pz = radius * cos(M_PI/2 - _beta) * cos(alpha);
			points.push_back(Point(px,py,pz));
			normals.push_back(Point(px,py,pz).normalize_point());
			s = (float)slicePoint/slices;
			t = 1 -((float)stackPoint/stacks);

			textCoords.push_back(std::pair<float,float>(s,t));
			px = radius * cos(M_PI/2-(_beta+betaVar)) * sin(alpha);
			py = radius * sin(M_PI/2-(_beta+betaVar));
			pz = radius * cos(M_PI/2-(_beta+betaVar)) * cos(alpha);
			points.push_back(Point(px,py,pz));
			normals.push_back(Point(px,py,pz).normalize_point());
            s = (float)slicePoint/slices;
			t = 1-((float)(stackPoint+1)/stacks);
			textCoords.push_back(std::pair<float,float>(s,t));
			px = radius * cos(M_PI/2-(_beta+betaVar)) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2-(_beta+betaVar));
			pz = radius * cos(M_PI/2-(_beta+betaVar)) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));
			normals.push_back(Point(px,py,pz).normalize_point());
            s = (float)(slicePoint+1)/slices;
			t = 1-((float)(stackPoint+1)/stacks);
			textCoords.push_back(std::pair<float,float>(s,t));

			px = radius * cos(M_PI/2 - _beta) * sin(alpha);
			py = radius * sin(M_PI/2 -_beta);
			pz = radius * cos(M_PI/2 -_beta) * cos(alpha);
			points.push_back(Point(px,py,pz));
			normals.push_back(Point(px,py,pz).normalize_point());
            s = (float)slicePoint/slices;
			t = 1-((float)stackPoint/stacks);
			textCoords.push_back(std::pair<float,float>(s,t));
			px = radius * cos(M_PI/2-(_beta+betaVar)) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2-(_beta+betaVar));
			pz = radius * cos(M_PI/2-(_beta+betaVar)) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));
			normals.push_back(Point(px,py,pz).normalize_point());
            s = (float)(slicePoint+1)/slices;
			t = 1-((float)(stackPoint+1)/stacks);
			textCoords.push_back(std::pair<float,float>(s,t));
            px = radius * cos(M_PI/2 - _beta) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2 - _beta);
			pz = radius * cos(M_PI/2 - _beta) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));
			normals.push_back(Point(px,py,pz).normalize_point());
            s = (float)(slicePoint+1)/slices;
			t = 1-((float)stackPoint/stacks);
			textCoords.push_back(std::pair<float,float>(s,t));
		}
	}
	
	result.push_back(points);
	result.push_back(normals);
	allCoords.first = result;
	allCoords.second = textCoords;
	return allCoords;
}