#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Time.h"
#include "InputManager.h"

class UserCamera
{
public:
	UserCamera();
	~UserCamera();

	//projection parameters
	float fieldOfView, nearClippingPlane, farClippingPlane, aspectRatio;

	//translation speed in units/second
	float moveSpeed;

	void moveAhead(float amount);
	void moveSideways(float amount);

	void pitch( float amount);
	void yaw(float amount);

	glm::mat4 getProjectionViewMatrix();

	void update(float deltaTime);

private:
	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 right();
	glm::vec3 forward();
};

