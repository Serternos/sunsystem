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
	///<summary>
	/// Data structure for a planet
	///</summary>
	///<param name='sphereRadius'>Radius of the sphere</param>
	///<param name='rotationFreq'>frequency of revolution around sphere's center in rpm</param>
	///<param name='orbitRadius'>distance between the spheres center and the world origin</param>
	///<param name='orbitFreq'>frequency of orbit around world origin in rpm</param>
	Sphere(float sphereRadius, float rotationFreq, float orbitRadius, float orbitFreq);
	~Sphere();

	//PLUS TEXTURE-->LATER
	float sphereRadius, rotationSpeed, orbitRadius, orbitSpeed;
	std::vector<Sphere*> children;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


	///<summary>
	/// get the model matrix for this sphere
	///</summary>
	glm::mat4 getModelMatrix();

	void update(float deltaTime);

private:
	glm::vec3 rotation;	
	glm::vec3 position;
};

#endif // _SPHERE_H
