#pragma once

#include "ILogger.h"

#include <iostream>

class ConsoleLogger : public ILogger {
public:
	ConsoleLogger() = default;

	ConsoleLogger( spdlog::level::level_enum logLevel ) : logLevel_( logLevel ) {}

	void log( spdlog::level::level_enum level, const std::string& message ) const override {
		if ( level >= logLevel_ ) {
			std::cout << "[" << to_string( level ) << "][" << std::this_thread::get_id() << "]"  << message << std::endl;
		}
	}

private:
	spdlog::level::level_enum logLevel_{ spdlog::level::level_enum::debug };

};