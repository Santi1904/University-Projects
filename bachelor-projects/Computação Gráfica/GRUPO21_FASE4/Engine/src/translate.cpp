#include "../include/translate.hpp"

Translate::Translate(float _time, int _align, vector<Point> curves){
    cat_points = curves;
    point_count = curves.size();
    time = _time;
	flag_align = _align;
    flag_g = 0;
}

Translate::Translate(float px,float py,float pz){
    t = Point(px,py,pz);
    flag_g = 1;
} 


void buildRotMatrix(Point x, Point y, Point z, float *m) {
	m[0] = x.x; m[1] = x.y; m[2] = x.z; m[3] = 0;
	m[4] = y.x; m[5] = y.y; m[6] = y.z; m[7] = 0;
	m[8] = z.x; m[9] = z.y; m[10] = z.z; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(Point a, Point b, Point &res) {

	res.x = a.y*b.z - a.z*b.y;
	res.y = a.z*b.x - a.x*b.z;
	res.z = a.x*b.y - a.y*b.x;
}

float length(Point a) {

	return sqrt(a.x*a.x + a.y * a.y + a.z * a.z);
}

void normalize(Point &a) {

	float l = length(a);
	a.x = a.x/l;
	a.y = a.y/l;
	a.z = a.z/l;
}


void Translate::multMatrixVector(float *m, float *v, float *res) {
	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void Translate::getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, Point &pos, Point &deriv) {

	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
	

	float T[4] = {t*t*t, t*t, t, 1};
	float T_deriv[4] = {3*t*t, 2*t, 1, 0}; 

	for (int i=0; i<3; i++){

		float Px[4] = {p0.x, p1.x, p2.x, p3.x};
		float Py[4] = {p0.y, p1.y, p2.y, p3.y};
		float Pz[4] = {p0.z, p1.z, p2.z, p3.z};

		// Compute A = M * P
		float Ax[4], Ay[4], Az[4];
		multMatrixVector((float*) m, Px, Ax);
		multMatrixVector((float*) m, Py, Ay);
		multMatrixVector((float*) m, Pz, Az);

		
		// Compute pos = T * A
		pos.x = T[0] * Ax[0] + T[1] * Ax[1] + T[2] * Ax[2] + T[3] * Ax[3];
		pos.y = T[0] * Ay[0] + T[1] * Ay[1] + T[2] * Ay[2] + T[3] * Ay[3];
		pos.z = T[0] * Az[0] + T[1] * Az[1] + T[2] * Az[2] + T[3] * Az[3];

		
		// compute deriv = T' * A
		deriv.x = T_deriv[0] * Ax[0] + T_deriv[1] * Ax[1] + T_deriv[2] * Ax[2] + T_deriv[3] * Ax[3];
		deriv.y = T_deriv[0] * Ay[0] + T_deriv[1] * Ay[1] + T_deriv[2] * Ay[2] + T_deriv[3] * Ay[3];
		deriv.z = T_deriv[0] * Az[0] + T_deriv[1] * Az[1] + T_deriv[2] * Az[2] + T_deriv[3] * Az[3];

			
	}
}

// given  global t, returns the point in the curve
void Translate::getGlobalCatmullRomPoint(float gt, Point &pos, Point &deriv) {

	float t = gt * point_count; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4]; 
	indices[0] = (index + point_count-1)%point_count;	
	indices[1] = (indices[0]+1)%point_count;
	indices[2] = (indices[1]+1)%point_count; 
	indices[3] = (indices[2]+1)%point_count;

	getCatmullRomPoint(t, cat_points[indices[0]], cat_points[indices[1]], cat_points[indices[2]], cat_points[indices[3]], pos, deriv);
}

void Translate::renderCatmullRomCurve() {

	Point pos = Point(0,0,0);
	Point deriv = Point(0,0,0);
	float tesselation = 0.01;

	// draw curve using line segments with GL_LINE_LOOP
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 1; i+=tesselation) {
		getGlobalCatmullRomPoint(i, pos, deriv);
		glVertex3f(pos.x, pos.y, pos.z);
	}
	glEnd();
}

void Translate::apply_transformation(){
	if (flag_g){
    	glTranslatef(t.x,t.y,t.z);
	}
	else{
		if(flag_curves) renderCatmullRomCurve();
		Point pos = Point(0,0,0);
		Point deriv = Point(0,0,0);
		Point Yi = Point(0,1,0);
		float t = ((float)glutGet(GLUT_ELAPSED_TIME) / 1000) / ((float)time);
    	getGlobalCatmullRomPoint(t, pos, deriv);
		glTranslatef(pos.x,pos.y,pos.z);
		if(flag_align){
			float M[16];
			Point Xi = Point(deriv.x,deriv.y,deriv.z);
			Point Zi;
			cross(Xi, Yi, Zi);
			cross(Zi, Xi, Yi);
			normalize(Xi);
			normalize(Yi);
			normalize(Zi);
			buildRotMatrix(Xi, Yi, Zi, M);
			glMultMatrixf(M);
		}
	}
}