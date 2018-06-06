#ifndef _SPHERE_H
#define _SPHERE_H
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Sphere
{
public:
	Sphere(float radius);
	~Sphere();

	//PLUS TEXTURE-->LATER
	float radius;

	std::vector<Sphere*> children;

	glm::vec4 color;

	glm::vec3 rotation;

	glm::vec3 translation;
};

#endif // _SPHERE_H
