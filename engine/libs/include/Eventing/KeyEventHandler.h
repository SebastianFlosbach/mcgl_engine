#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>
#include <iostream>

#include "KeyEvent.h"
#include "../Definition/mcgl_engine_def.h"


class KeyEventHandler {
public:
	static void registerCallback( GLFWwindow* window, MCGL_KEY_EVENT_CALLBACK callback );
	
private:
	KeyEventHandler();

	static GLFWwindow* pWindow_;
	static MCGL_KEY_EVENT_CALLBACK callback_;
	static std::map<int, double> pressedKeys_;

	static void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
};