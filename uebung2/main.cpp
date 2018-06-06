#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VAOFactory.h"
#include "shader.h"
#include "Sphere.h"

// Farblocation im Shader ( uniform )
GLuint colorLocation, mvpLocation;

//Kugeln
Sphere* kugelEins;

// Breite und Höhe des Fensters
const int width = 800;
const int height = 600;

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
	VAOFactory::init(initShader());

	//GENERATE SPHERE HERE
	kugelEins = new Sphere(2.0f);
	//GENERATE SPHERE HERE
}

/// <summary>
/// Hauptrenderfunktion
/// </summary>
void render()
{


	//RENDER HERE
	VAOFactory::render(kugelEins);
	//RENDER HERE

	// Buffer wechseln (double buffering, wegen GLUT_DOUBLE in der glutInitDisplayMode(..) Funktion)
	glutSwapBuffers();
}


/// <summary>
/// Funktion für die Tastatureingaben
/// </summary>
/// <param name="key"></param>
/// <param name="mousex"></param>
/// <param name="mousey"></param>
void keyboardFunction(unsigned char key, int mousex, int mousey)
{

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
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Aufgabe 02 - Computergrafik I");
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboardFunction);
	glutIdleFunc(idleFunction);
	glewInit();
	init();
	glutMainLoop();
	return 0;
}
