#include "Logging/ILogger.h"

void trace( const ILogger& logger, const std::string& message ) {
	logger.log( spdlog::level::level_enum::trace, message );
}

void debug( const ILogger& logger, const std::string& message ) {
	logger.log( spdlog::level::level_enum::debug, message );
}

void info( const ILogger& logger, const std::string& message ) {
	logger.log( spdlog::level::level_enum::info, message );
}

void warn( const ILogger& logger, const std::string& message ) {
	logger.log( spdlog::level::level_enum::warn, message );
}

void error( const ILogger& logger, const std::string& message ) {
	logger.log( spdlog::level::level_enum::err, message );
}

void critical( const ILogger& logger, const std::string& message ) {
	logger.log( spdlog::level::level_enum::critical, message );
}


char* to_string( spdlog::level::level_enum level ) {
	switch ( level ) {
		case spdlog::level::trace:
			return "trace";
		case spdlog::level::debug:
			return "debug";
		case spdlog::level::info:
			return "info";
		case spdlog::level::warn:
			return "warn";
		case spdlog::level::err:
			return "error";
		case spdlog::level::critical:
			return "critical";
		case spdlog::level::off:
			return "off";
		default:
			return "<undefined>";
	}
}