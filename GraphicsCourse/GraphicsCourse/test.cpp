#include <gl/glut.h>
#include <math.h>


static int time = 0;
static int delay = 100;  // 100ms = 0.1s


void init();
void display();

void timer(int t);

int main(int argc, char * argv[]) {

	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sphere");
	glutDisplayFunc(display);

	glutTimerFunc(delay, timer, 1);
	init();
	glutMainLoop();

	return 0;

}

void init() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -5.0, 5.0);
	glEnable(GL_DEPTH_TEST);

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16);  // draw the sun
	glRotatef(-90, 1.0, 0.0, 0.0);

	glPushMatrix();  // push sun's matrix into stack
	 
      glRotatef((360.0 / 365.0) * time / 24.0, 0.0, 1.0, 0.0); // the earth revolves around the sun  
	  glTranslatef(0.7, 0.0, 0.0);
	  glRotatef(-23.5, 0.0, 0.0, 1.0); // the slope of the Earth's axis of rotation (23.5 degree)
	   
	  glRotatef((360.0 / 365.0) * time * 24.0, 0.0, 1.0, 0.0);    // the rotation of the earth


	  glColor3f(0.5, 0.6, 0.7);
	  glutWireSphere(0.1, 10, 8);  // draw the earth

	  glRotatef(-((360.0 / 365.0) * time * 24.0), 0.0, 1.0, 0.0);
	  glRotatef(23.5, 0.0, 0.0, 1.0);    // turn the frame back to the previous value for draw the moon.

	  glPushMatrix(); // push earth's matrix into stack
	
	    glRotatef((360.0 / 365.0) * time / 2.0, 0.0, 1.0, 0.0);  // the moon revolves around the earth per 30 days
		glTranslatef(0.2, 0.0, 0.0);
		glColor3f(0.9, 0.8, 0.2);
		glutWireSphere(0.04, 10, 8); //draw moon

	    glPopMatrix(); // pop earth's matrix
	  glPopMatrix(); // pop sun's matrix
	glutSwapBuffers();

	glFlush();
}


void timer(int t) {
	time += 1;
	if (time >= 8760) time -= 8760;   // 1 year is 8760 hours
	glutPostRedisplay();
	glutTimerFunc(delay, timer, 1);
}