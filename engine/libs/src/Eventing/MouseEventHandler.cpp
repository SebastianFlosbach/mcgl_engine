#include "Eventing/MouseEventHandler.h"

GLFWwindow* MouseEventHandler::pWindow_{};
MCGL_MOUSE_EVENT_CALLBACK MouseEventHandler::callback_{};
std::map<int, double> MouseEventHandler::pressedButtons_{};