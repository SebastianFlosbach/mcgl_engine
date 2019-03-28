#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>
#include <iostream>

#include "KeyEvent.h"
#include "../Definition/mcgl_engine_def.h"


class KeyEventHandler {
public:

	//KeyEventHandler( const KeyEventHandler& other ) = delete;
	//KeyEventHandler& operator=( const KeyEventHandler& other ) = delete;

	//KeyEventHandler( KeyEventHandler&& other ) = delete;
	//KeyEventHandler& operator=( KeyEventHandler&& other ) = delete;

	static void registerCallback( GLFWwindow* window, MCGL_KEY_EVENT_CALLBACK callback ) {
		pWindow_ = window;
		callback_ = callback;
		if ( callback != nullptr ) {
			glfwSetKeyCallback( window, keyCallback );
		} else {
			glfwSetKeyCallback( window, NULL );
		}
	}
	
private:
	KeyEventHandler();

	static GLFWwindow* pWindow_;

	static MCGL_KEY_EVENT_CALLBACK callback_;

	static std::map<int, double> pressedKeys_;

	static void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
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
};