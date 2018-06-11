#include "sphere.h"

Sphere::Sphere(float sphereRadius, float rotationSpeed, float orbitRadius, float orbitSpeed)
{
	this->sphereRadius = sphereRadius;
	this->rotationSpeed = rotationSpeed;
	this->orbitRadius = orbitRadius;
	this->orbitSpeed = orbitSpeed;

	this->children = std::vector<Sphere*>();
}

glm::mat4 Sphere::getModelMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
	model = glm::rotate(model, this->rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(sphereRadius, sphereRadius, sphereRadius));
	return model;
}

void Sphere::update(float deltaTime, glm::vec3 translation)
{
	//update own revolution
	this->rotation += rotationSpeed * 0.1f * deltaTime;

	//update position. only use parent position to decouple from rotation & scale
	this->orbitAngle += orbitSpeed * 0.1f * deltaTime;
	glm::mat4 pr = glm::rotate(glm::mat4(1.0f), orbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 pos4 = pr * (this->orbitRadius * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
	this->position = glm::vec3(pos4) + translation;

	for (int i = 0; i < this->children.size(); i++) {
		this->children.at(i)->update(deltaTime, this->position);
	}
}

Sphere::~Sphere()
{
}
