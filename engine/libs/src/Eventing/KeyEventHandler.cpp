#include "Eventing/KeyEventHandler.h"

GLFWwindow* KeyEventHandler::pWindow_{};
MCGL_KEY_EVENT_CALLBACK KeyEventHandler::callback_{};
std::map<int, double> KeyEventHandler::pressedKeys_{};