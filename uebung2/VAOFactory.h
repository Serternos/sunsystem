#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define _USE_MATH_DEFINES

#include <math.h>
#include "Sphere.h"

#define VERTICES_COUNT_OF_SPHERE 32*32
#define INDICE_COUNT_OF_SPHERE 32*32*6 
#define BUFFER_ARRAY_SIZE VERTICES_COUNT_OF_SPHERE*(3+3+2)

class VAOFactory
{
public:
	VAOFactory();
	~VAOFactory();

	static void render(Sphere* sphere);
	static void init(GLuint shaderProgram);

private:
	static inline void push_indices(GLuint* indices, int index, int sectors, int r, int s);
	static void fillSphereArray(GLfloat* interleaved, GLuint* indices, float radius);

	static void generateMVP(glm::vec3 rotation);
	static void generateBuffers();
};

