#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <map>
#include <iostream>
#include <mutex>

#include "KeyEvent.h"
#include "../Definition/mcgl_engine_def.h"


namespace eventing {


class KeyEventHandler {
public:
	static void registerCallback( GLFWwindow* window, MCGL_KEY_EVENT_CALLBACK callback );
	
	static void pollEvents();

private:
	KeyEventHandler();

	static GLFWwindow* pWindow_;

	static std::mutex mEvent_;

	static MCGL_KEY_EVENT_CALLBACK callback_;

	static std::map<int, double> pressedKeys_;
	static std::map<int, double> downKeys_;
	static std::map<int, double> releasedKeys_;

	static void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );

	static inline void invokeCallback( const KeyEvent& keyEvent ) {
		if ( callback_ ) {
			callback_( keyEvent );
		}
	}
};


}