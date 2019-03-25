#pragma once

#include "ILogger.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <fstream>

class SpdFileLogger : public ILogger {
public:
	SpdFileLogger( const std::string& name, const std::string& path ) {
		logger_ = spdlog::rotating_logger_mt( name, path, 1048576, 3 );
	}

	void log( spdlog::level::level_enum level, const std::string& message ) const override {
		logger_->log( logLevel_, message );
	}

private:
	spdlog::level::level_enum logLevel_{ spdlog::level::level_enum::debug };

	std::shared_ptr<spdlog::logger> logger_;
};