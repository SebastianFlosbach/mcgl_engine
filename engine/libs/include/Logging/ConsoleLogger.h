#pragma once

#include "ILogger.h"

#include <iostream>

class ConsoleLogger : public ILogger {
public:
	ConsoleLogger() = default;

	void log( LogLevel level, std::string message ) const override {
		if ( level >= logLevel_ ) {
			std::cout << "[" << to_string( level ) << "]" << message << std::endl;
		}
	}

private:
	LogLevel logLevel_{ LogLevel::Debug };

};