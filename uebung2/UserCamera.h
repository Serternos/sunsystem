#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class UserCamera
{
public:
	UserCamera();
	~UserCamera();

	float fieldOfView;
	float nearClippingPlane;
	float farClippingPlane;
	float aspectRatio;

	void moveAhead(float direction);
	void moveSideways(float directon);

	void pitch( float amount);
	void yaw(float amount);

	glm::mat4 getProjectionViewMatrix();

private:
	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 right();
	glm::vec3 forward();
};

