#include "SphereRenderer.h"
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
static UserCamera* camera;

SphereRenderer::SphereRenderer()
{
}


SphereRenderer::~SphereRenderer()
{
}

void SphereRenderer::render(Sphere* sphere)
{
	// once per frame
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader);
	glm::mat4 projectionview = camera->getViewProjectionMatrix();

	// once per sphere per frame
	modelviewprojection = projectionview * sphere->getModelMatrix();

	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(modelviewprojection));
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_STRIP, sizeof(indices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

inline void SphereRenderer::push_indices(GLuint * indices, int index, int sectors, int r, int s)
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

void SphereRenderer::fillSphereArray(GLfloat * interleaved, GLuint * indices)
{
	std::cout << "Creating Sphere vertices" << std::endl;
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

			interleaved[index] = x; //Position
			interleaved[index + 1] = y;
			interleaved[index + 2] = z;

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

void SphereRenderer::init(GLuint shaderProgram)
{
	std::cout << "Initializing SphereRenderer" << std::endl;
	shader = shaderProgram;
	mvpLocation = glGetUniformLocation(shaderProgram, "MVP");
	fillSphereArray(vertices, indices);
	generateBuffers();
}


///<summary>
/// Set the camera from which to get the projection and view matrix
///</summary>
void SphereRenderer::setCamera(UserCamera* newCamera)
{
	camera = newCamera;
}

void SphereRenderer::generateBuffers()
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

