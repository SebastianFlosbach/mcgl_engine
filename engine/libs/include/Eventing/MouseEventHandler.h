#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>
#include <iostream>

#include "MouseEvent.h"
#include "../Definition/mcgl_engine_def.h"


class MouseEventHandler {
public:	

	static void registerCallback( GLFWwindow* window, MCGL_MOUSE_EVENT_CALLBACK callback ) {
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
		if ( callback_ ) {
			callback_( { MouseEventType::MouseMove, { xPos, yPos } } );
		}
	}

	static std::map<int, double> pressedButtons_;

	static void buttonCallback( GLFWwindow* window, int button, int action, int mods ) {
		MouseEvent mEvent;

		switch ( action ) {
			case GLFW_PRESS:
			{
				mEvent = { MouseEventType::ButtonPess, { button, 0.0 } };
				pressedButtons_.insert( button, glfwGetTime() );
			}
				break;
			case GLFW_RELEASE:
			{
				if ( pressedButtons_.find( button ) == pressedButtons_.end() ) {
					std::cout << "Released mouse button that was not pressed" << std::endl;
					mEvent = { MouseEventType::ButtonRelease, { button, 0.0 } };
				} else {
					double pressedSince = pressedButtons_.at( button );
					mEvent = { MouseEventType::ButtonRelease, { button, glfwGetTime() - pressedSince } };
					pressedButtons_.erase( button );
				}
			}
				break;
			default:
				break;
		}

		if ( callback_ ) {
			callback_( mEvent );
		}
	}

	static void scrollCallback( GLFWwindow* window, double xOffset, double yOffset ) {
		if ( callback_ ) {
			callback_( { MouseEventType::Scroll, { xOffset, yOffset } } );
		}
	}

};