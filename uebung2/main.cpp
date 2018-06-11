#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>

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
GLuint load_texture(const char* file);

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
	sonne = new Sphere(2.0f, 0.3f, 0.0f, 0.0f);
	Sphere* erde = new Sphere(0.3f, 8.0f, 4.0f, 2.6f);
	Sphere* mars = new Sphere(0.2f, 7.0f, 8.0f, 1.5f);
	Sphere* mond = new Sphere(0.1f, 30.0f, 0.6f, -30.0f);
	Sphere* jupiter = new Sphere(1.0f, 5.0f, 12.0f, 1.0f);
	sonne->children.push_back(erde);
	sonne->children.push_back(mars);
	sonne->children.push_back(jupiter);
	erde->children.push_back(mond);

	sonne->mat.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	sonne->mat.emissive = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);
	sonne->mat.texture = load_texture("res/sun.jpg");

	erde->mat.diffuse = glm::vec4(0.5f, 0.4f, 1.0f, 1.0f);
	erde->mat.specular = glm::vec4(1.0f);
	erde->mat.texture = load_texture("res/earth.jpg");
	erde->mat.smoothness = 50.0f;

	mars->mat.diffuse = glm::vec4(1.0f, 0.7f, 0.7f, 1.0f);
	mars->mat.specular = glm::vec4(0.0f);
	mars->mat.texture = load_texture("res/mars.jpg");
	mars->mat.smoothness = 1.0f;

	jupiter->mat.diffuse = glm::vec4(1.0f, 0.8f, 0.8f, 1.0f);
	jupiter->mat.specular = glm::vec4(1.0f, 0.9f, 0.9f, 1.0f);
	jupiter->mat.texture = load_texture("res/jupiter.jpg");
	jupiter->mat.smoothness = 7.0f;

	mond->mat.diffuse = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	mond->mat.specular = glm::vec4(0.0f);
	mond->mat.texture = load_texture("res/moon.jpg");
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

GLuint load_texture(const char* file) {
	//int width, height, channels;
	//unsigned char* buffer = SOIL_load_image(file, &width, &height, &channels, SOIL_LOAD_RGBA);

	GLuint tex_id = SOIL_load_OGL_texture
	(
		file,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

	/* check for an error during the load process */
	std::cout << "SOIL: " << SOIL_last_result() << " id: " << tex_id << std::endl;

	//int save_result = SOIL_save_image
	//(
	//	"new_terrain.bmp",
	//	SOIL_SAVE_TYPE_BMP,
	//	width, height, 3,
	//	tex_id
	//);

	return tex_id;
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
