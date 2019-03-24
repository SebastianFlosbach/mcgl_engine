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
		auto func = []( GLFWwindow* window, int key, int scancode, int action, int mods ) {
			static_cast<KeyEventHandler*>(glfwGetWindowUserPointer( window ))->keyCallback( window, key, scancode, action, mods );
		};
		glfwSetKeyCallback( window, func );
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

	MCGL_KEY_EVENT_CALLBACK callback_;

	std::map<int, double> pressedKeys_;

	void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
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
				if ( pressedKeys_.find( key ) != pressedKeys_.end() ) {
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
};