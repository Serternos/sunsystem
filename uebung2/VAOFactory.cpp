#include "VAOFactory.h"
#include <iostream>


static const int rings = 16;
static const int sectors = 16;

static GLuint vao;
static GLuint ibo;
static GLuint interleavedVbo;
static GLuint mvpLocation;
static GLuint shader;

static GLfloat vertices[BUFFER_ARRAY_SIZE];
static GLuint indices[INDICE_COUNT_OF_SPHERE];

static glm::mat4 modelviewprojection;

VAOFactory::VAOFactory()
{
}


VAOFactory::~VAOFactory()
{
}

void VAOFactory::render(Sphere * sphere)
{
	// Setzt die Farbe bei Neuesetzung des Colorbuffers auf Schwarz
	glClearColor(0, 0, 0, 1);
	// Leert den Colorbuffer mit dem ClearColor und leert den ZBuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Setze den Shaderstate auf das Standardprogramm
	glUseProgram(shader);

	generateMVP(sphere->rotation);

	// Übergabe der MVP matrix
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelviewprojection));
	glBindVertexArray(vao);
	// Dreiecke zeichen
	glDrawElements(GL_TRIANGLE_STRIP, sizeof(indices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

inline void VAOFactory::push_indices(GLuint * indices, int index, int sectors, int r, int s)
{
	index *= 6;
	int curRow = r * sectors;
	int nextRow = (r + 1) * sectors;
	int nextS = (s + 1) % sectors;

	indices[index] = curRow + s;
	indices[index + 1] = nextRow + s;
	indices[index + 2] = nextRow + nextS;

	indices[index + 3] = curRow + s;
	indices[index + 4] = nextRow + nextS;
	indices[index + 5] = curRow + nextS;
}

void VAOFactory::fillSphereArray(GLfloat * interleaved, GLuint * indices, float radius)
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);

	int index = 0;
	int uvIndex = 0;
	int indiceIndex = 0;
	for (int r = 0; r < rings; ++r) {
		for (int s = 0; s < sectors; ++s) {
			float const y = sin(-M_PI_2 + M_PI * r * R);
			float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			interleaved[index] = x * radius; //Position
			interleaved[index + 1] = y * radius;
			interleaved[index + 2] = z * radius;

			interleaved[index + 3] = x; //Normals
			interleaved[index + 4] = y;
			interleaved[index + 5] = z;

			interleaved[index + 6] = s * S; //UV
			interleaved[index + 7] = r * R;

			if (r < rings - 1)
				push_indices(indices, indiceIndex, sectors, r, s);

			indiceIndex++;
			index += 8;
			uvIndex += 2;
		}
	}
}

void VAOFactory::init(GLuint shaderProgram)
{
	std::cout << "intitalizing VAOFactory" << std::endl;
	shader = shaderProgram;
	mvpLocation = glGetUniformLocation(shaderProgram, "MVP");
	fillSphereArray(vertices, indices, 1.0f);
	generateBuffers();
}

void VAOFactory::generateMVP(glm::vec3 rotation)
{
	//std::cout << "entering generateMVP()" << std::endl;
	// Transformation und Generierung einer Modelviewprojectionmatrix
	//TODO: get projection matrix from camera
	glm::mat4 Projection = glm::perspective(glm::radians(29.0f), 800 / (float)600, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
	glm::mat4 Model = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//	Model = glm::rotate(Model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
//	Model = glm::rotate(Model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
//	Model = glm::rotate(Model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	modelviewprojection = Projection * View * Model;
}

void VAOFactory::generateBuffers()
{
	std::cout << "Entering generateBuffers()" << std::endl;
	//Generate everything needed
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &interleavedVbo);
	glGenBuffers(1, &ibo);

	//verts und farben laden
	glBindBuffer(GL_ARRAY_BUFFER, interleavedVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(GL_FLOAT)), (GLvoid*)0);
	//normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * sizeof(GL_FLOAT)), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	//UVs
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * sizeof(GL_FLOAT)), (GLvoid*)(6 * sizeof(GL_FLOAT)));

	//indices laden
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

