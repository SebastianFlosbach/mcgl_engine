#include "Eventing/KeyEventHandler.h"


namespace eventing {


GLFWwindow* KeyEventHandler::pWindow_{};
MCGL_KEY_EVENT_CALLBACK KeyEventHandler::callback_{};
std::map<int, double> KeyEventHandler::pressedKeys_{};
std::map<int, double> KeyEventHandler::downKeys_{};
std::map<int, double> KeyEventHandler::releasedKeys_{};

std::mutex KeyEventHandler::mEvent_{};


void KeyEventHandler::registerCallback( GLFWwindow* window, MCGL_KEY_EVENT_CALLBACK callback ) {
	pWindow_ = window;
	callback_ = callback;
	if ( callback != nullptr ) {
		glfwSetKeyCallback( window, keyCallback );
	} else {
		glfwSetKeyCallback( window, NULL );
	}
}

void KeyEventHandler::pollEvents() {
	std::lock_guard<std::mutex> lock( mEvent_ );

	double currentTime = glfwGetTime();

	for ( auto& key : pressedKeys_ ) {
		invokeCallback( { KeyEventType::Pressed, key.first, 0.0 } );
	}

	for ( auto& key : downKeys_ ) {
		invokeCallback( { KeyEventType::Down, key.first, currentTime - key.second } );
	}

	for ( auto& key : releasedKeys_ ) {
		invokeCallback( { KeyEventType::Released, key.first, currentTime - key.second } );
	}

	releasedKeys_.clear();

	for ( auto& key : pressedKeys_ ) {
		downKeys_.insert( key );
	}

	pressedKeys_.clear();
}

void KeyEventHandler::keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	std::lock_guard<std::mutex> lock( mEvent_ );

	double currentTime = glfwGetTime();

	switch ( action ) {
		case GLFW_PRESS:
		{
			if ( pressedKeys_.find( key ) != pressedKeys_.end() || downKeys_.find( key ) != downKeys_.end() ) {
				std::cout << "Pressed key that was already pressed" << std::endl;
			} else {
				pressedKeys_.insert( { key, currentTime } );
			}
		}
		break;
		case GLFW_RELEASE:
		{
			if ( pressedKeys_.find( key ) != pressedKeys_.end() ) {
				double pressedSince = pressedKeys_[key];
				pressedKeys_.erase( key );
				releasedKeys_.insert( { key, currentTime - pressedSince } );
			} else if( downKeys_.find( key ) != downKeys_.end() ) {
				double pressedSince = downKeys_[key];
				downKeys_.erase( key );
				releasedKeys_.insert( { key, currentTime - pressedSince } );
			} else {
				std::cout << "Released key without pressing it" << std::endl;
			}
		}
		break;
		default:
			return;
	}
}


}
