#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>
#include <iostream>

#include "MouseEvent.h"
#include "../Definition/mcgl_engine_def.h"


class MouseEventHandler {
public:	

	void registerCallback( GLFWwindow* window, MCGL_MOUSE_EVENT_CALLBACK callback ) {
		pWindow = window;
		callback_ = callback;
		if ( callback != NULL ) {
			glfwSetCursorPosCallback( window, positionCallback );
			glfwSetMouseButtonCallback( window, buttonCallback );
			glfwSetScrollCallback( window, scrollCallback );
		} else {
			glfwSetCursorPosCallback( window, NULL );
			glfwSetMouseButtonCallback( window, NULL );
			glfwSetScrollCallback( window, NULL );
		}
	}

private:
	MouseEventHandler();

	static GLFWwindow* pWindow_;
	static MCGL_MOUSE_EVENT_CALLBACK callback_;

	static void positionCallback( GLFWwindow* window, double xPos, double yPos ) {

	}

	static void buttonCallback( GLFWwindow* window, int button, int action, int mods ) {

	}

	static void scrollCallback( GLFWwindow* window, double xOffset, double yOffset ) {

	}

};