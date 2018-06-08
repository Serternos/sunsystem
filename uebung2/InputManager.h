#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <GL/freeglut.h>
#include <iostream>

class InputManager
{
public:
	InputManager();
	~InputManager();

	static void init(int newWidth, int newHeight, float sensitivity);

	static void keyboardDownFunc(unsigned char key, int mousex, int mousey);
	static void keyboardUpFunc(unsigned char key, int mousex, int mousey);
	static void passiveMotionFunc(int x, int y);

	static glm::vec2 getMouseDeltas();
	static bool getKey(unsigned char key);
};

#endif //_INPUTMANAGER_H_