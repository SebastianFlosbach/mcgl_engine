#pragma once

#include "ILogger.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <fstream>
#include <stdlib.h>

class SpdFileLogger : public ILogger {
public:
	SpdFileLogger( const std::string& name, const std::string& path ) {
		
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fileName[_MAX_FNAME];
		char ext[_MAX_EXT];

		if ( _splitpath_s( path.c_str(), drive, dir, fileName, ext ) ) {
			throw std::runtime_error( "Could not parse log file path" );
		}

		CreateDirectory( dir, NULL );
		std::ofstream( path.c_str(), std::ios::app );

		logger_ = spdlog::rotating_logger_mt( name, path, 1048576, 3 );
		logger_->set_level( spdlog::level::level_enum::debug );
	}

	void log( spdlog::level::level_enum level, const std::string& message ) const override {
		logger_->log( level, message );
		logger_->flush();
	}

private:
	std::shared_ptr<spdlog::logger> logger_;
};