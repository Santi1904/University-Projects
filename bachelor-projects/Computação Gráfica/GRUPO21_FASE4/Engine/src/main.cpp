#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <IL/il.h>

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

GLuint buffers[3];
unordered_map<string,VBO> points;
unordered_map<string,int> textures;
int Translate::flag_curves = 0;
int timebase = 0, frame = 0;
float alfa = 0.0, _beta=0.0, radius=1.0;
float camX, camY, camZ;
int startX, startY, tracking = 0;
GLenum mode = GL_FILL;
bool axis = false;

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


void draw_models(vector<Model> models){
	for (int i=0; i<models.size(); i++){
		models[i].color.apply_color();

		VBO vbo = points[models[i].filename];
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.buffers[0]);
		glBindBuffer(GL_ARRAY_BUFFER,vbo.buffers[1]);
 		glVertexPointer(3,GL_FLOAT,0,0);
		glBindBuffer(GL_ARRAY_BUFFER,vbo.buffers[2]);
		glNormalPointer(GL_FLOAT,0,0);
		if (models[i].flag_texture){
			glBindTexture(GL_TEXTURE_2D, textures[models[i].texture_file]);
			glBindBuffer(GL_ARRAY_BUFFER,vbo.buffers[3]);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
		}

		glDrawElements(GL_TRIANGLES,vbo.indexCount,GL_UNSIGNED_INT,NULL);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}


void draw_group(Group *_group){
	glPushMatrix();
	for(Transformation *t : _group->transformations){
		t->apply_transformation();
	}
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
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	Point lookAt = _data->settings.lookAt;
	Point up = _data->settings.up;
	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
		      lookAt.x,lookAt.y,lookAt.z,
			  up.x,up.y,up.z);

	for(Light *l : _data->lights){
		l->apply_light();
	}

	// put axis drawing in here
	if(axis){
		glDisable(GL_LIGHTING);
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
		glEnable(GL_LIGHTING);
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

int loadTexture(string s) {
	unsigned int t,tw,th;
	unsigned char *texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)("../textures/" + s).c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	
	glGenTextures(1,&texID);

	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

void handle_3Dfiles_group(Group *g){
	for(Model m : g->models){
		textures[m.texture_file] = loadTexture(m.texture_file);
		string model = "../models/" + m.filename;
		
		VBO vbo = VBO();
		vector<float> pts;  		// vertices
		vector<float> n; 			// normals
		vector<float> t; 			// texCoord
		vector<unsigned int> ind;   // indexes

		ifstream file(model);

		string line;
		getline(file,line);
		istringstream ssline(line);
    	int numPoints;
    	ssline >> numPoints;
		float x,y,z, n1, n2, n3 , t1, t2;
    	for(int i = 0; i < numPoints; i++){
        	getline(file,line);
			istringstream ssline(line);
        	ssline >> x >> y >> z >> n1 >> n2 >> n3 >> t1 >> t2;
			pts.push_back(x);
			pts.push_back(y);
			pts.push_back(z);
			n.push_back(n1);
			n.push_back(n2);
			n.push_back(n3);
			t.push_back(t1);
			t.push_back(t2);
			ind.push_back(i);
    	}
		
		// Indexes
		vbo.indexCount = ind.size();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vbo.buffers[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*ind.size(),ind.data(),GL_STATIC_DRAW);


		// Vertixes
		vbo.vertixCount = pts.size();
		glBindBuffer(GL_ARRAY_BUFFER,vbo.buffers[1]);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pts.size(), pts.data(), GL_STATIC_DRAW);

		// Normals
		glBindBuffer(GL_ARRAY_BUFFER,vbo.buffers[2]);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*n.size(), n.data(), GL_STATIC_DRAW);

		// Textures
		glBindBuffer(GL_ARRAY_BUFFER,vbo.buffers[3]);
    	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*t.size(), t.data(), GL_STATIC_DRAW);

		points[m.filename] = vbo;
		
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

void init(){
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glClearColor(0, 0, 0, 0);

    glEnable(GL_LIGHTING);
    GLfloat light_ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_global[4] = { 0.3f, 0.3f , 0.3f, 1.0f };

    GLenum lights[8] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
    for(int i=0; i<_data->lights.size(); i++){
        glEnable(lights[i]);
        glLightfv(lights[i], GL_AMBIENT, light_ambient);
        glLightfv(lights[i], GL_DIFFUSE, light_diffuse);
        glLightfv(lights[i], GL_SPECULAR, light_specular);
    }

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global);
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

	
    // Keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	

	#ifndef __APPLE__
	glewInit();
	#endif
	

	init();

	handle_3Dfiles();

    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}