#pragma once

#include <string>
#include <spdlog/spdlog.h>


namespace logging {


class ILogger {
public:
	ILogger() = default;
	virtual ~ILogger() = default;

	virtual void log( spdlog::level::level_enum level, const std::string& message ) const = 0;
};

void trace( const ILogger& logger, const std::string& message );
void debug( const ILogger& logger, const std::string& message );
void info( const ILogger& logger, const std::string& message );
void warn( const ILogger& logger, const std::string& message );
void error( const ILogger& logger, const std::string& message );
void critical( const ILogger& logger, const std::string& message );

char* to_string( spdlog::level::level_enum level );


}
