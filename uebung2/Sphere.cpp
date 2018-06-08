#include "sphere.h"

Sphere::Sphere(float sphereRadius, float rotationSpeed, float orbitRadius, float orbitSpeed)
{
	this->sphereRadius = sphereRadius;
	this->rotationSpeed = rotationSpeed;
	this->orbitRadius = orbitRadius;
	this->orbitSpeed = orbitSpeed;
}


Sphere::~Sphere()
{
}

glm::mat4 Sphere::getModelMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	return glm::scale(model, glm::vec3(sphereRadius, sphereRadius, sphereRadius));
}

void Sphere::update(float deltaTime)
{
}
