#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include "../include/parser.hpp"
#include "../include/cam_settings.hpp"


Settings camera;

void draw_triangle(Point p1, Point p2, Point p3){
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(p1.get_x(),p1.get_y(),p1.get_z());
		glVertex3f(p2.get_x(),p2.get_y(),p2.get_z());
		glVertex3f(p3.get_x(),p3.get_y(),p3.get_z());
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
	Point proj = camera.projection;
	gluPerspective(proj.get_x() ,ratio, proj.get_y() ,proj.get_z());

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camera.position.get_x(),camera.position.get_y(),camera.position.get_z(), 
		      camera.lookAt.get_x(),camera.lookAt.get_y(),camera.lookAt.get_z(),
			  camera.up.get_x(),camera.up.get_y(),camera.up.get_z());

	// put axis drawing in here
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

	glPolygonMode(GL_FRONT,GL_LINE);

	draw_models(camera.models);
	



	// End of frame
	glutSwapBuffers();
}


int main(int argc, char **argv) {

    camera = parse(std::string(argv[1]));

    

    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(camera.width,camera.height);
	glutCreateWindow("3D-Engine");

    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
    // put here the registration of the keyboard callbacks
	



    //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}