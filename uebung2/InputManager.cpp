#include "InputManager.h"
static int halfWidth;
static int halfHeight;
static float mouseScale;

static bool keyField[256] = { false };
static glm::vec2 mouseDeltas = glm::vec2();
static bool warped = false;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::init(int width, int height, float sensitivity)
{
	mouseScale = 1.0f / sensitivity;
	glutIgnoreKeyRepeat(GLU_TRUE);
	halfWidth = width/2;
	halfHeight = height/2;
	glutWarpPointer(halfWidth, halfHeight);
}

void InputManager::keyboardDownFunc(unsigned char key, int mousex, int mousey)
{
	keyField[key] = true;
}

void InputManager::keyboardUpFunc(unsigned char key, int mousex, int mousey)
{
	keyField[key] = false;
}

void InputManager::passiveMotionFunc(int x, int y)
{
	if (warped) {
		warped = false;
		return;
	}
 	int deltaX = halfWidth - x;
	int deltaY = halfHeight - y;
	mouseDeltas += glm::vec2((float)deltaX, (float)deltaY);

	warped = true;
	glutWarpPointer(halfWidth, halfHeight);
}

glm::vec2 InputManager::getMouseDeltas()
{
	glm::vec2 ret = mouseDeltas;
	mouseDeltas = glm::vec2(0.0f, 0.0f);
	return ret * mouseScale;
}

bool InputManager::getKey(unsigned char key)
{
	return keyField[key];
}
