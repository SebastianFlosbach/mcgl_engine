#pragma once

#include "ILogger.h"

#include <iostream>

class ConsoleLogger : public ILogger {
public:
	ConsoleLogger() = default;

	void log( spdlog::level::level_enum level, const std::string& message ) const override {
		if ( level >= logLevel_ ) {
			std::cout << "[" << to_string( level ) << "]" << message << std::endl;
		}
	}

private:
	spdlog::level::level_enum logLevel_{ spdlog::level::level_enum::debug };

};