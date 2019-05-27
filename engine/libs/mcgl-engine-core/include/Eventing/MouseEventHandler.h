#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <map>
#include <iostream>

#include "MouseEvent.h"
#include "../Definition/mcgl_engine_def.h"


namespace eventing {


class MouseEventHandler {
public:	
	static void registerCallback( GLFWwindow* window, MCGL_MOUSE_EVENT_CALLBACK callback );

private:
	MouseEventHandler();

	static GLFWwindow* pWindow_;
	static MCGL_MOUSE_EVENT_CALLBACK callback_;
	static std::map<int, double> pressedButtons_;

	static void positionCallback( GLFWwindow* window, double xPos, double yPos );

	static void buttonCallback( GLFWwindow* window, int button, int action, int mods );

	static void scrollCallback( GLFWwindow* window, double xOffset, double yOffset );

	static inline void invokeCallback( const MouseEvent& mouseEvent ) {
		if ( callback_ ) {
			callback_( mouseEvent );
		}
	}

};


}
