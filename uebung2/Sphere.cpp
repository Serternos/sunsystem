#include "sphere.h"



Sphere::Sphere(float radius)
{
	this->radius = radius;
}


Sphere::~Sphere()
{
}

glm::mat4 Sphere::getModelMatrix()
{
	return glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}


