#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SphereRenderer.h"
#include "InputManager.h"
#include "shader.h"
#include "Sphere.h"
#include "Time.h"

// Farblocation im Shader ( uniform )
GLuint colorLocation, mvpLocation;

//Kugeln
Sphere* sonne;
Sphere* erde;

//Kamera
UserCamera* camera;

// Breite und Höhe des Fensters
const int width = 800;
const int height = 600;
const float sensitivity = 60.0f;

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
	InputManager::init(width, height, sensitivity);
	SphereRenderer::init(initShader());

	//GENERATE SPHERE HERE
	sonne = new Sphere(2.0f, 0.0f, 0.0f, 0.0f);
	erde = new Sphere(1.0f, 0.0f, 0.0f, 0.0f);
	//GENERATE SPHERE HERE

	//GENERATE CAMERA HERE
	camera = new UserCamera();
	camera->aspectRatio = ((float)width /(float) height);
	camera->farClippingPlane = 100.0f;
	camera->nearClippingPlane = 1.0f;
	camera->fieldOfView = glm::radians(29.0f);

	camera->moveSpeed = 3.0f;

	camera->moveAhead(-10.0f);

	SphereRenderer::setCamera(camera);
	//GENERATE CAMERA HERE
}

/// <summary>
/// Hauptrenderfunktion
/// </summary>
void render()
{
	//update
	if (InputManager::getKey('q')) glutLeaveMainLoop();
	Time::update();
	camera->update(Time::deltaTime());
	sonne->update(Time::deltaTime());

	//RENDER HERE
	SphereRenderer::render(sonne);
	//RENDER HERE

	// Buffer wechseln (double buffering, wegen GLUT_DOUBLE in der glutInitDisplayMode(..) Funktion)
	glutSwapBuffers();
}


void keyboardFunction(unsigned char key, int mousex, int mousey)
{
}

void keyboardUpFunction(unsigned char key, int mousex, int mousey){
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
	glutInitWindowPosition(400, 250);
	glutInitWindowSize(width, height);
	glutCreateWindow("Aufgabe 03 - Computergrafik I");
	glutDisplayFunc(render);
	glutKeyboardFunc(InputManager::keyboardDownFunc);
	glutKeyboardUpFunc(InputManager::keyboardUpFunc);
	glutPassiveMotionFunc(InputManager::passiveMotionFunc);
	glutIdleFunc(idleFunction);
	glewInit();
	init();
	glutMainLoop();
	return 0;
}
