#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include "../include/parser.hpp"
#include "../include/xml_data.hpp"
#include "../include/VBO.hpp"
#include <stdio.h>
#include <iostream>
#include <unordered_map>

using namespace std;

XML *_data;

GLuint indexs, buffer;
int indexCount;

unordered_map<string,VBO> points;
int Translate::flag_curves = 0;
int timebase = 0, frame = 0;
float alfa = 0.0, _beta=0.0, radius=1.0;
float camX, camY, camZ;
int startX, startY, tracking = 0;
GLenum mode = GL_LINE;
bool axis = true;

void spherical2Cartesian() {
	camX = radius * cos(_beta) * sin(alfa);
	camY = radius * sin(_beta);
	camZ = radius * cos(_beta) * cos(alfa);
}

void cartesian2Spherical(){
	radius = sqrt(camX * camX + camY * camY + camZ * camZ);
	_beta = asin(camY / radius);
	alfa = atan2(camX,camZ);
}

void draw_triangle(Point p1, Point p2, Point p3){
	glBegin(GL_TRIANGLES);
		glVertex3f(p1.x,p1.y,p1.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p3.x,p3.y,p3.z);
	glEnd();
}

void draw_models(vector<string> filemodels){
	
	for (int i=0; i<filemodels.size(); i++){
		points[filemodels[i]].draw();
	}
	//for (int j=0; j<pts.size(); j+=3){z
	//	draw_triangle(pts[j],pts[j+1],pts[j+2]);
	//}
		
	//vbo.generate_VBO(pts);
	//vbo.generate_indexVBO(pts);
	
}

//void draw_model(string filepath){
//	vector<Point> pts = parse3D_file(filepath);
//	for (int j=0; j<pts.size(); j+=3){
//		draw_triangle(pts[j],pts[j+1],pts[j+2]);
//	}
//}

void draw_group(Group *_group){
	glPushMatrix();
	for(Transformation *t : _group->transformations){
		t->apply_transformation();
	}
	_group->color.apply_color();
	//_group->color.rgb.coords();
	//glColor3f(_group->color.rgb.x,_group->color.rgb.y,_group->color.rgb.z);
	//cout << _group->color.rgb.x << " " << _group->color.rgb.y << " " << _group->color.rgb.z << endl;
	draw_models(_group->models);
	for(Group *_g : _group->groupChildren){
		draw_group(_g);
	}
	glPopMatrix();
}

void draw_groups(){

	for(Group *g : _data->groups){
		draw_group(g);
	}
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	Point proj = _data->settings.projection;
	gluPerspective(proj.x,ratio,proj.y,proj.z);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	Point lookAt = _data->settings.lookAt;
	Point up = _data->settings.up;
	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
		      lookAt.x,lookAt.y,lookAt.z,
			  up.x,up.y,up.z);

	// put axis drawing in here
	if(axis){
		glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
		glEnd();
	}

	glPolygonMode(GL_FRONT_AND_BACK,mode);
	
	draw_groups();

	float fps;
	int time;
	char s[64];
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME); 
	if (time - timebase > 1000) { 
		fps = frame*1000.0/(time-timebase); 
		timebase = time; 
		frame = 0; 
		sprintf(s, "3D-Engine  (FPS: %.2f6.2)", fps);
		glutSetWindowTitle(s);
	}

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
	switch(key){
		case '1': mode = GL_FILL; break;
		case '2': mode = GL_LINE; break;
		case '3': mode = GL_POINT; break; 
		case 'f': axis = !axis; break;
		case 'c': Translate::flag_curves = 1 - Translate::flag_curves; break;
	}

	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {
	
}


void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		cartesian2Spherical();
		if (button == GLUT_LEFT_BUTTON){
			tracking = 1;
		}
		else if (button == 4){
			radius += 2.0f;
		}
		else if (button == 3){
			radius -= 2.0f;
			if (radius < 2.0f)
				radius = 2.0f;
		}
		else
			tracking = 0;
		spherical2Cartesian();
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alfa += (xx - startX);
			_beta += (yy - startY);
		}

		tracking = 0;
	}
	glutPostRedisplay();
}


void processMouseMotion(int xx, int yy) {

	float deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	if (!tracking)
		return;
	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alfa + deltaX;
		betaAux = _beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = radius;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
	cartesian2Spherical();
	glutPostRedisplay();

}

void handle_3Dfiles_group(Group *g){
	for(string model : g->models){
		
		VBO vbo = VBO();
		
		vector<Point> pts = parse3D_file(model);
		
		// Indexes
		vector<unsigned int> i;
    	for (unsigned int j = 0; j < pts.size(); j++) {
    	    i.push_back(j);
		}
		
		vbo.indexCount = i.size();
		glGenBuffers(1,&vbo.indexes);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo.indexes);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*i.size(),i.data(),GL_STATIC_DRAW);


		// Vertixes
		vbo.vertixCount = pts.size();
		glGenBuffers(1,&vbo.vertixes);
		glBindBuffer(GL_ARRAY_BUFFER,vbo.vertixes);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(Point)*pts.size(), pts.data(), GL_STATIC_DRAW);

		points[model] = vbo;
		
	}
	for(Group *_g : g->groupChildren){
		handle_3Dfiles_group(_g);
	}
}

void handle_3Dfiles(){
	for(Group *g : _data->groups){
		handle_3Dfiles_group(g);
	}
}


int main(int argc, char **argv) {

	_data = parse(string(argv[1]));

	camX = _data->settings.position.x; camY = _data->settings.position.y; camZ = _data->settings.position.z;  
	cartesian2Spherical();

    
    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(_data->w_width,_data->w_height);
	glutCreateWindow("3D-Engine");

    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	
    // put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	

	#ifndef __APPLE__
	glewInit();
	#endif
	
	glEnableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	handle_3Dfiles();

    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}