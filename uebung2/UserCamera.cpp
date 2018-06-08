#include "UserCamera.h"

static const glm::vec3 originalForward = glm::vec3(0.0f, 0.0f, -1.0f);
static const glm::vec3 originalRight = glm::vec3(1.0f, 0.0f, 0.0f);

UserCamera::UserCamera()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}


UserCamera::~UserCamera()
{
}

void UserCamera::moveAhead(float amount)
{
	this->position = this->position - (this->forward() * amount);
}

void UserCamera::moveSideways(float amount)
{
	this->position = this->position - (this->right() * amount);
}

void UserCamera::pitch(float amount)
{
	this->rotation.x += glm::radians(amount);
	if (this->rotation.x > glm::radians(89.0f)) this->rotation.x = glm::radians(89.0f);
	else if (this->rotation.x < glm::radians(-89.0f)) this->rotation.x = glm::radians(-89.0f);
}

void UserCamera::yaw(float amount)
{
	this->rotation.y += glm::radians(amount);
}

glm::mat4 UserCamera::getProjectionViewMatrix()
{
	std::cout << "x: " << this->forward().x << " y: " << this->forward().y << " z: " << this->forward().z << std::endl;
	glm::mat4 view = glm::rotate(glm::mat4(1.0f), this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, this->position);
	glm::mat4 proj = glm::perspective(
		this->fieldOfView, 
		this->aspectRatio, 
		this->nearClippingPlane, 
		this->farClippingPlane
	);
	return proj * view;
}

void UserCamera::update(float deltaTime)
{
	if (InputManager::getKey('a')) moveSideways(-moveSpeed * Time::deltaTime());
	if (InputManager::getKey('d')) moveSideways(moveSpeed * Time::deltaTime());
	if (InputManager::getKey('w')) moveAhead(moveSpeed * Time::deltaTime());
	if (InputManager::getKey('s')) moveAhead(-moveSpeed * Time::deltaTime());

	if (InputManager::getKey('r')) farClippingPlane += 5.0f;
	if (InputManager::getKey('f')) farClippingPlane -= 5.0f;
	if (InputManager::getKey('t')) nearClippingPlane += 0.5f;
	if (InputManager::getKey('g')) nearClippingPlane -= 0.5f;

	if (InputManager::getKey('+')) fieldOfView -= glm::radians(1.0f);
	if (InputManager::getKey('-')) fieldOfView += glm::radians(1.0f);

	glm::vec2 mouseD = InputManager::getMouseDeltas();
	yaw(-mouseD.x);
	pitch(-mouseD.y);
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
