#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>
#include "../include/parser.hpp"
#include "../include/xml_data.hpp"

XML *data;

float alfa = 0.0, beta=0.0, radius=1.0;
float camX, camY, camZ;
int startX, startY, tracking = 0;
GLenum mode = GL_LINE;
bool axis = true;

void spherical2Cartesian() {
	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

void cartesian2Spherical(){
	radius = sqrt(camX * camX + camY * camY + camZ * camZ);
	beta = asin(camY / radius);
	alfa = atan2(camX,camZ);
}

void draw_triangle(Point p1, Point p2, Point p3){
	//glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(p1.x,p1.y,p1.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p3.x,p3.y,p3.z);
	glEnd();
}

void draw_models(vector<string> filemodels){
	for (int i=0; i<filemodels.size(); i++){
		vector<Point> pts = parse3D_file(filemodels[i]);
		for (int j=0; j<pts.size(); j+=3){
			draw_triangle(pts[j],pts[j+1],pts[j+2]);
		}
	}
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

	for(Group *g : data->groups){
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
	Point proj = data->settings.projection;
	gluPerspective(proj.x,ratio,proj.y,proj.z);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	Point lookAt = data->settings.lookAt;
	Point up = data->settings.up;
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

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char key, int xx, int yy) {
	switch(key){
		case '1': mode = GL_FILL; break;
		case '2': mode = GL_LINE; break;
		case '3': mode = GL_POINT; break; 
		case 'f': axis = !axis; break;
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
			beta += (yy - startY);
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
		betaAux = beta + deltaY;

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


int main(int argc, char **argv) {

	data = parse(std::string(argv[1]));

	camX = data->settings.position.x; camY = data->settings.position.y; camZ = data->settings.position.z;  
	cartesian2Spherical();

    
    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(data->w_width,data->w_height);
	glutCreateWindow("3D-Engine");

    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
    // put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	



    //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}