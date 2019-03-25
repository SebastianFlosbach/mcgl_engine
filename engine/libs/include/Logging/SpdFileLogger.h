#pragma once

#include "ILogger.h"

#include <spdlog/sinks/rotating_file_sink.h>

class SpdFileLogger : ILogger {
	SpdFileLogger( const std::string& name, const std::string& path ) {
		auto rotating_logger = spdlog::rotating_logger_mt( name, path, 1048576 * 5, 3 );
	}

	void log( LogLevel level, std::string message ) const override {
		if ( level >= logLevel_ ) {
			std::cout << "[" << to_string( level ) << "]" << message << std::endl;
		}
	}

private:
	LogLevel logLevel_{ LogLevel::Debug };
};