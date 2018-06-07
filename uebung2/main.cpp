#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SphereRenderer.h"
#include "shader.h"
#include "Sphere.h"

// Farblocation im Shader ( uniform )
GLuint colorLocation, mvpLocation;

//Kugeln
Sphere* sonne;
Sphere* erde;

//Kamera
UserCamera* camera;

// Breite und Höhe des Fensters
const int width = 1024;
const int height = 768;

/// <summary>
/// Initialisiert den Viewport, Shader und Vertexdaten
/// </summary>

void init()
{
	// Viewport, wo OpenGL rendert
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Initialisiert den Standardshader aus shader.h
	SphereRenderer::init(initShader());

	//GENERATE SPHERE HERE
	sonne = new Sphere(2.0f);
	erde = new Sphere(1.0f);
	//GENERATE SPHERE HERE

	//GENERATE CAMERA HERE
	camera = new UserCamera();
	camera->aspectRatio = ((float)width /(float) height);
	camera->farClippingPlane = 100.0f;
	camera->nearClippingPlane = 1.0f;
	camera->fieldOfView = glm::radians(29.0f);

	camera->moveAhead(-10.0f);

	SphereRenderer::setCamera(camera);
	//GENERATE CAMERA HERE
}

/// <summary>
/// Hauptrenderfunktion
/// </summary>
void render()
{


	//RENDER HERE
	SphereRenderer::render(sonne);
	//RENDER HERE

	// Buffer wechseln (double buffering, wegen GLUT_DOUBLE in der glutInitDisplayMode(..) Funktion)
	glutSwapBuffers();
}


void keyboardFunction(unsigned char key, int mousex, int mousey)
{
	switch (key) {
		case 'a':
			camera->moveSideways(-0.01f);
			break;
		case 'd':
			camera->moveSideways(-0.01f);
			break;
		case 'w':
			camera->moveAhead(0.01f);
			break;
		case 's':
			camera->moveAhead(-0.01f);
			break;
		case 'r':
			camera->farClippingPlane += 5.0f;
			break;
		case 'f':
			camera->farClippingPlane -= 5.0f;
			break;
		case 't':
			camera->nearClippingPlane += 0.5f;
			break;
		case 'g':
			camera->nearClippingPlane -= 0.5f;
			break;
		case '+':
			camera->fieldOfView -= glm::radians(1.0f);
			break;
		case '-':
			camera->fieldOfView += glm::radians(1.0f);
			break;
		default:
			break;
	}
}

void passiveMotionFunction(int x, int y) {
	static int lastMouseX = width / 2;
	static int lastMouseY = height / 2;

	int deltaX = lastMouseX - x;
	int deltaY = lastMouseY - y;

	lastMouseX = x;
	lastMouseY = y;

	camera->yaw((float)deltaX / 500.0f);
	camera->pitch((float)deltaY / 500.0f);
}

/// <summary>
/// Diese Funktion wird immer dann ausgeführt wenn keine Events stattfinden
/// </summary>
void idleFunction()
{
	// Zeichne das Fenster neu
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(250, 250);
	glutInitWindowSize(width, height);
	glutCreateWindow("Aufgabe 03 - Computergrafik I");
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboardFunction);
	glutPassiveMotionFunc(passiveMotionFunction);
	glutIdleFunc(idleFunction);
	glewInit();
	init();
	glutMainLoop();
	return 0;
}
