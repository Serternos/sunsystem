#ifndef _SPHEREGENERATOR_H
#define _SPHEREGENERATOR_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

const int rings = 16;
const int sectors = 16;

#define VERTICES_COUNT_OF_SPHERE 32*32
#define INDICE_COUNT_OF_SPHERE 32*32*6 
#define BUFFER_ARRAY_SIZE VERTICES_COUNT_OF_SPHERE*(3+3+2)

// Hilfsfunktion für createSphere um Indices zu erstellen
inline void push_indices(GLuint* indices, int index, int sectors, int r, int s) {
	index *= 6;
	int curRow = r * sectors;
	int nextRow = (r + 1) * sectors;
	int nextS = (s + 1) % sectors;

	indices[index] = curRow + s;
	indices[index+1] = nextRow + s;
	indices[index+2] = nextRow + nextS;

	indices[index+3] = curRow + s;
	indices[index+4] = nextRow + nextS;
	indices[index+5] = curRow + nextS;
}

// Erstellung der Kugel mit Hilfe von Polarkoordinaten
void createSphere(GLfloat* interleaved, GLuint* indices,
	float radius)
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

#endif // _SPHEREGENERATOR_H
