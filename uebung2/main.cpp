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

//Kugeln
Sphere* sonne;

//Kamera
UserCamera* camera;

// Breite und Höhe des Fensters
const int width = 1024;
const int height = 768;
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

	//GENERATE SPHERES HERE
	sonne = new Sphere(2.0f, 1.0f, 0.0f, 0.0f);
	Sphere* erde = new Sphere(0.3f, 33.0f, 4.0f, 8.6f);
	Sphere* mars = new Sphere(0.2f, 13.0f, 8.0f, 3.0f);
	Sphere* mond = new Sphere(0.1f, 30.0f, 0.6f, -30.0f);
	sonne->children.push_back(erde);
	sonne->children.push_back(mars);
	erde->children.push_back(mond);

	sonne->mat.diffuse = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	sonne->mat.emissive = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);

	erde->mat.diffuse = glm::vec4(0.0f, 0.2f, 1.0f, 1.0f);
	erde->mat.specular = glm::vec4(1.0f);
	erde->mat.smoothness = 12.0f;

	mars->mat.diffuse = glm::vec4(1.0f, 0.3f, 0.3f, 1.0f);
	mars->mat.specular = glm::vec4(0.0f);
	mars->mat.smoothness = 0.0f;

	mond->mat.diffuse = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	mond->mat.specular = glm::vec4(0.0f);
	mond->mat.smoothness = 0.0f;
	//GENERATE SPHERES HERE

	//GENERATE CAMERA HERE
	camera = new UserCamera();
	camera->aspectRatio = ((float)width/(float) height);
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
	sonne->update(Time::deltaTime(), glm::vec3(0.0f));

	//RENDER HERE
	SphereRenderer::render(sonne);
	//RENDER HERE

	glutSwapBuffers();
	InputManager::update();
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
