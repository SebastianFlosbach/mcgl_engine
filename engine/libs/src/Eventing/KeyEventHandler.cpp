#include "Eventing/KeyEventHandler.h"

GLFWwindow* KeyEventHandler::pWindow_{};
MCGL_KEY_EVENT_CALLBACK KeyEventHandler::callback_{};
std::map<int, double> KeyEventHandler::pressedKeys_{};


void KeyEventHandler::registerCallback( GLFWwindow* window, MCGL_KEY_EVENT_CALLBACK callback ) {
	pWindow_ = window;
	callback_ = callback;
	if ( callback != nullptr ) {
		glfwSetKeyCallback( window, keyCallback );
	} else {
		glfwSetKeyCallback( window, NULL );
	}
}

void KeyEventHandler::keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	double currentTime = glfwGetTime();

	KeyEvent keyEvent;

	switch ( action ) {
		case GLFW_PRESS:
		{
			if ( pressedKeys_.find( key ) == pressedKeys_.end() ) {
				pressedKeys_.insert( { key, currentTime } );
				keyEvent = { KeyEventType::Pressed, key, 0.0 };
			} else {
				double pressedSince = pressedKeys_.at( key );
				keyEvent = { KeyEventType::Down, key, currentTime - pressedSince };
			}
		}
		break;
		case GLFW_RELEASE:
		{
			if ( pressedKeys_.find( key ) == pressedKeys_.end() ) {
				std::cout << "Released key without pressing it" << std::endl;
				keyEvent = { KeyEventType::Released, key, 0.0 };
			} else {
				double pressedSince = pressedKeys_.at( key );
				keyEvent = { KeyEventType::Released, key, currentTime - pressedSince };
				pressedKeys_.erase( key );
			}
		}
		break;
		default:
			return;
	}

	if ( callback_ ) {
		callback_( keyEvent );
	}
}