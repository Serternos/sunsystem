#include "UserCamera.h"

static const glm::vec3 originalForward = glm::vec3(0.0f, 0.0f, -1.0f);
static const glm::vec3 originalRight = glm::vec3(1.0f, 0.0f, 0.0f);

UserCamera::UserCamera()
{
}


UserCamera::~UserCamera()
{
}

void UserCamera::moveAhead(float direction)
{
	this->position = this->position - (this->forward() * direction);
}

void UserCamera::moveSideways(float direction)
{
	this->position = this->position - (this->right() * direction);
}

void UserCamera::pitch(float amount)
{
	this->rotation.x += amount;
}

void UserCamera::yaw(float amount)
{
	this->rotation.y += amount;
}

glm::mat4 UserCamera::getProjectionViewMatrix()
{
	glm::mat4 view = glm::rotate(glm::mat4(1.0f), this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, this->position);
	glm::mat4 proj = glm::perspective(
		this->fieldOfView, 
		this->aspectRatio, 
		this->nearClippingPlane, 
		this->farClippingPlane);
	return proj * view;
}

glm::vec3 UserCamera::right()
{
	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rot = glm::rotate(rot, this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	return glm::mat3(rot) * originalRight;
}

glm::vec3 UserCamera::forward()
{	
	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rot = glm::rotate(rot, this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	return glm::mat3(rot) * originalForward;
}
