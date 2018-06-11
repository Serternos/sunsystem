#include "SphereRenderer.h"
#include <iostream>


static const int rings = 16;
static const int sectors = 16;

static GLuint vao;
static GLuint ibo;
static GLuint interleavedVbo;
static GLuint shader;

//uniform matrix locations
static GLuint mvpLocation, mvLocation, vLocation, nLocation;

//uniform light locations
static GLuint light_position, light_ambient, light_diffuse, light_specular;

//uniform material locations
static GLuint mat_diffuse, mat_specular, mat_emissive, mat_smoothness;

static GLfloat vertices[BUFFER_ARRAY_SIZE];
static GLuint indices[INDICE_COUNT_OF_SPHERE];

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
	glBindVertexArray(vao);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader);
	glm::mat4 P = camera->getProjectionMatrix();
	glm::mat4 V = camera->getViewMatrix();
	glm::mat4 M = glm::mat4(1.0f);

	glm::mat4 VP = P * V;
	glm::mat4 MV = glm::mat4(1.0f);

	glUniformMatrix4fv(vLocation, 1, GL_FALSE, glm::value_ptr(V));

	std::vector<Sphere*> spheresToRender = std::vector<Sphere*>();
	spheresToRender.push_back(sphere);

	// once per sphere per frame
	while (spheresToRender.size() > 0) {
		//get next sphere
		Sphere* currentSphere = spheresToRender.at(spheresToRender.size() - 1);
		spheresToRender.pop_back();

		//set material uniforms
		M = currentSphere->getModelMatrix();
		MV = V*M;

		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(VP * M));
		glUniformMatrix4fv(mvLocation, 1, GL_FALSE, glm::value_ptr(MV));
		glUniformMatrix3fv(nLocation, 1, GL_FALSE, glm::value_ptr(glm::mat3(MV)));

		glUniform4fv(mat_diffuse, 1, glm::value_ptr(currentSphere->mat.diffuse));
		glUniform4fv(mat_specular, 1, glm::value_ptr(currentSphere->mat.specular));
		glUniform4fv(mat_emissive, 1, glm::value_ptr(currentSphere->mat.emissive));
		glUniform1f(mat_smoothness, currentSphere->mat.smoothness);
	
		//render it
		glDrawElements(GL_TRIANGLE_STRIP, sizeof(indices), GL_UNSIGNED_INT, 0);

		//add all children of currentSphere to spheresToRender
		spheresToRender.insert(
			spheresToRender.end(),
		    currentSphere->children.begin(),
			currentSphere->children.end()
		);
	}

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
	glUseProgram(shader);

	mvpLocation = glGetUniformLocation(shader, "MVP");
	mvLocation = glGetUniformLocation(shader, "MV");
	vLocation = glGetUniformLocation(shader, "V");
	nLocation = glGetUniformLocation(shader, "N");

	light_position = glGetUniformLocation(shader, "light_position");
	light_ambient = glGetUniformLocation(shader, "light_ambient");
	light_diffuse = glGetUniformLocation(shader, "light_diffuse");
	light_specular = glGetUniformLocation(shader, "light_specular");

	mat_diffuse = glGetUniformLocation(shader, "mat_diffuse");
	mat_specular = glGetUniformLocation(shader, "mat_specular");
	mat_emissive = glGetUniformLocation(shader, "mat_emissive");
	mat_smoothness = glGetUniformLocation(shader, "mat_smoothness");

	glUniform4fv(light_position, 1, glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
	glUniform4fv(light_ambient, 1, glm::value_ptr(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f)));
	glUniform4fv(light_diffuse, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 0.5f, 1.0f)));
	glUniform4fv(light_specular, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 0.5f, 1.0f)));

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

