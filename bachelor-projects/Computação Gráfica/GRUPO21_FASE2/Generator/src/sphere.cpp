#define _USE_MATH_DEFINES
#include <math.h>
#include "../include/sphere.hpp"


Sphere::Sphere(float _radius, int _slices, int _stacks) {
    radius = _radius;
    slices = _slices;
    stacks = _stacks;
}


std::vector<Point> Sphere::generate_points(){
    
	std::vector<Point> points;
	float alpha,beta,px,py,pz;
	float alphaVar = 2*M_PI/slices; 
	float betaVar = M_PI/stacks;
	int stackPoint,slicePoint;
	for(stackPoint=0;stackPoint<stacks;stackPoint++){
		beta = stackPoint * betaVar;
		for(slicePoint=0;slicePoint<slices;slicePoint++){
			alpha = slicePoint * alphaVar;
			px = radius * cos(M_PI/2 - beta) * sin(alpha);
			py = radius * sin(M_PI/2 - beta);
			pz = radius * cos(M_PI/2 - beta) * cos(alpha);
			points.push_back(Point(px,py,pz));
			px = radius * cos(M_PI/2-(beta+betaVar)) * sin(alpha);
			py = radius * sin(M_PI/2-(beta+betaVar));
			pz = radius * cos(M_PI/2-(beta+betaVar)) * cos(alpha);
			points.push_back(Point(px,py,pz));
			px = radius * cos(M_PI/2-(beta+betaVar)) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2-(beta+betaVar));
			pz = radius * cos(M_PI/2-(beta+betaVar)) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));

			px = radius * cos(M_PI/2 - beta) * sin(alpha);
			py = radius * sin(M_PI/2 -beta);
			pz = radius * cos(M_PI/2 -beta) * cos(alpha);
			points.push_back(Point(px,py,pz));
			px = radius * cos(M_PI/2-(beta+betaVar)) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2-(beta+betaVar));
			pz = radius * cos(M_PI/2-(beta+betaVar)) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));
            		px = radius * cos(M_PI/2 - beta) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2 - beta);
			pz = radius * cos(M_PI/2 - beta) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));
		}
	}
return points;
}
