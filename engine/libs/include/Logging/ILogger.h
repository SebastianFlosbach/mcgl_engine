#pragma once

#include <string>

enum class LogLevel {
	Fatal,
	Error,
	Info,
	Debug,
	Trace
};

class ILogger {
public:
	ILogger() = default;
	virtual ~ILogger() = default;

	virtual void log( LogLevel level, std::string message ) const = 0;
};

char* to_string( LogLevel level ) {
	switch ( level ) {
		case LogLevel::Fatal:
			return "Fatal";
		case LogLevel::Error:
			return "Error";
		case LogLevel::Debug:
			return "Debug";
		case LogLevel::Info:
			return "Info";
		case LogLevel::Trace:
			return "Trace";
		default:
			return "<Unknown>";
	}
}