#include "Eventing/MouseEventHandler.h"

GLFWwindow* MouseEventHandler::pWindow_{};
MCGL_MOUSE_EVENT_CALLBACK MouseEventHandler::callback_{};
std::map<int, double> MouseEventHandler::pressedButtons_{};


void MouseEventHandler::registerCallback( GLFWwindow* window, MCGL_MOUSE_EVENT_CALLBACK callback ) {
	pWindow_ = window;
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

void MouseEventHandler::positionCallback( GLFWwindow* window, double xPos, double yPos ) {
	invokeCallback( { MouseEventType::MouseMove, xPos, yPos } );
}

void MouseEventHandler::buttonCallback( GLFWwindow* window, int button, int action, int mods ) {
	switch ( action ) {
		case GLFW_PRESS:
		{
			pressedButtons_.insert( { button, glfwGetTime() } );
			invokeCallback( { MouseEventType::ButtonPess, button, 0.0 } );
		}
		break;
		case GLFW_RELEASE:
		{
			if ( pressedButtons_.find( button ) == pressedButtons_.end() ) {
				std::cout << "Released mouse button that was not pressed" << std::endl;
				invokeCallback( { MouseEventType::ButtonRelease, button, 0.0 } );
			} else {
				double pressedSince = pressedButtons_.at( button );
				pressedButtons_.erase( button );
				invokeCallback( { MouseEventType::ButtonRelease, button, glfwGetTime() - pressedSince } );
			}
		}
		break;
		default:
			break;
	}
}

void MouseEventHandler::scrollCallback( GLFWwindow* window, double xOffset, double yOffset ) {
	invokeCallback( { MouseEventType::Scroll, xOffset, yOffset } );
}