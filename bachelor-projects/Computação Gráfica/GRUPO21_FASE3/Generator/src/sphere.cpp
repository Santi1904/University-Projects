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
	float alpha,_beta,px,py,pz;
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
			px = radius * cos(M_PI/2-(_beta+betaVar)) * sin(alpha);
			py = radius * sin(M_PI/2-(_beta+betaVar));
			pz = radius * cos(M_PI/2-(_beta+betaVar)) * cos(alpha);
			points.push_back(Point(px,py,pz));
			px = radius * cos(M_PI/2-(_beta+betaVar)) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2-(_beta+betaVar));
			pz = radius * cos(M_PI/2-(_beta+betaVar)) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));

			px = radius * cos(M_PI/2 - _beta) * sin(alpha);
			py = radius * sin(M_PI/2 -_beta);
			pz = radius * cos(M_PI/2 -_beta) * cos(alpha);
			points.push_back(Point(px,py,pz));
			px = radius * cos(M_PI/2-(_beta+betaVar)) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2-(_beta+betaVar));
			pz = radius * cos(M_PI/2-(_beta+betaVar)) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));
            		px = radius * cos(M_PI/2 - _beta) * sin(alpha+alphaVar);
			py = radius * sin(M_PI/2 - _beta);
			pz = radius * cos(M_PI/2 - _beta) * cos(alpha+alphaVar);
			points.push_back(Point(px,py,pz));
		}
	}
return points;
}
