#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>
#include <iostream>

#include "KeyEvent.h"
#include "../Definition/mcgl_engine_def.h"

class KeyEventHandler {
public:
	KeyEventHandler( GLFWwindow* window ) : pWindow_( window ) {
		glfwSetWindowUserPointer( window, this );
		auto func = []( GLFWwindow* window, int key, int scancode, int action, int mods ) {
			auto keyEventHandler = static_cast<KeyEventHandler*>( glfwGetWindowUserPointer( window )  );
			keyEventHandler->keyCallback( keyEventHandler, window, key, scancode, action, mods );
		};
		glfwSetKeyCallback( window, func );
	}

	~KeyEventHandler() {
		glfwSetKeyCallback( pWindow_, NULL );
	}

	KeyEventHandler( const KeyEventHandler& other ) = delete;
	KeyEventHandler& operator=( const KeyEventHandler& other ) = delete;

	KeyEventHandler( KeyEventHandler&& other ) = delete;
	KeyEventHandler& operator=( KeyEventHandler&& other ) = delete;

	void registerCallback( MCGL_KEY_EVENT_CALLBACK callback ) {
		callback_ = callback;
	}

private:
	GLFWwindow* pWindow_;

	MCGL_KEY_EVENT_CALLBACK callback_ { nullptr };

	std::map<int, double> pressedKeys_ { };

	static void keyCallback( KeyEventHandler* keyEventHandler, GLFWwindow* window, int key, int scancode, int action, int mods ) {
		if ( !keyEventHandler ) {
			return;
		}

		double currentTime = glfwGetTime();

		KeyEvent keyEvent;

		switch ( action ) {
			case GLFW_PRESS:
			{
				if ( keyEventHandler->pressedKeys_.find( key ) == keyEventHandler->pressedKeys_.end() ) {
					keyEventHandler->pressedKeys_.insert( { key, currentTime } );
					keyEvent = { KeyEventType::Pressed, key, 0.0 };
				} else {
					double pressedSince = keyEventHandler->pressedKeys_.at( key );
					keyEvent = { KeyEventType::Down, key, currentTime - pressedSince };
				}
			}
			break;
			case GLFW_RELEASE:
			{
				if ( keyEventHandler->pressedKeys_.find( key ) == keyEventHandler->pressedKeys_.end() ) {
					std::cout << "Released key without pressing it" << std::endl;
					keyEvent = { KeyEventType::Released, key, 0.0 };
				} else {
					double pressedSince = keyEventHandler->pressedKeys_.at( key );
					keyEvent = { KeyEventType::Released, key, currentTime - pressedSince };
					keyEventHandler->pressedKeys_.erase( key );
				}
			}
			break;
			default:
				return;
		}

		if ( keyEventHandler->callback_ ) {
			keyEventHandler->callback_( keyEvent );
		}
	}
};