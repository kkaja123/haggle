#pragma once

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdarg>
#include <source_location>


#define LOG_ERROR(loggerPtr, __FMT__, ...)  \
        LOG_WRAPPER_WITH_LEVEL(loggerPtr, Logger::Level::Error, std::source_location::current(), __FMT__, __VA_ARGS__)

#define LOG_WARNING(loggerPtr, __FMT__, ...)  \
        LOG_WRAPPER_WITH_LEVEL(loggerPtr, Logger::Level::Warning, std::source_location::current(), __FMT__, __VA_ARGS__)

#define LOG_INFO(loggerPtr, __FMT__, ...)  \
        LOG_WRAPPER_WITH_LEVEL(loggerPtr, Logger::Level::Info, std::source_location::current(), __FMT__, __VA_ARGS__)

#define LOG_DEBUG(loggerPtr, __FMT__, ...)  \
        LOG_WRAPPER_WITH_LEVEL(loggerPtr, Logger::Level::Debug, std::source_location::current(), __FMT__, __VA_ARGS__)

#define LOG_WRAPPER_WITH_LEVEL(loggerPtr, messageLevel, srcLoc, __FMT__, ...)  \
        loggerPtr->PrintWithLevel(messageLevel, Logger::FormatLogMessage(__FMT__, __VA_ARGS__).c_str(), srcLoc);

/// Logs messages at various severity levels by printing to the stdout and to a log file.
class Logger
{
public:
	enum class Level : uint8_t
	{
		_Silent = 0,  // A message shouldn't ever be logged with this level. This level can be used to silence all log messages when used as the log filter.
		Error = 10,
		Warning = 20,
		Info = 30,
		Debug = 40
	};

	Logger();
	~Logger();

	void init(const char* title, const std::string& logFilename = "mods/haggle-console.log")
	{
		if (GetConsoleWindow() == NULL)
		{
			std::ios_base::sync_with_stdio(false);

			file.open(logFilename, std::ios_base::out | std::ios_base::binary);

			AllocConsole();
			SetConsoleTitleA(title);

			std::freopen("CONOUT$", "w", stdout);
			std::freopen("CONIN$", "r", stdin);
		}
	}

	/** @brief Formats a log message according to standard C string formatting rules (printf).
	 *
	 * @return Formatted string object.
	 */
	static std::string FormatLogMessage(const char* fmt, ...)
	{
		va_list va;
		va_start(va, fmt);
		char result[512]{};
		std::vsprintf(result, fmt, va);
		return result;
	}

	/** @brief Prints a log message with its associated severity level to the
	 * stdout and the log file.
	 *
	 * @details *It is recommended that the macros be used for ease-of-use
	 * (e.g. `PRINT_ERROR()`).*
	 *
	 * If this is built in a Debug configuration, the calling context
	 * of the log message is included in the output.
	 *
	 * @param msgLevel    The severity level of the log message.
	 * @param msg         The message contents to log. Use FormatLogMessage()
	 *                      for `printf()`-like string formatting for this
	 *                      parameter.
	 * @param callingFunc The calling context where this function is called.
	 *                      This is only included when compiling in a Debug
	 *                      configuration.
	 */
	void PrintWithLevel(Level msgLevel, const char* msg, std::source_location callingFunc = std::source_location::current());

	/** @brief Changes how file paths are represented when they are logged
	 * when this is built in a Debug configuration.
	 *
	 * @param isFullPath    True: The full path is printed.
	 *                      False: Only the name of the file and its extension
	 *                        are printed.
	 */
	void SetDebugFilenamePathStyle(bool isFullPath)
	{
		debugFilePathIsPrintedInFull = isFullPath;
	}

	/** @brief Sets the minimum severity level of log messages that can be logged.
	 *
	 * @details The severity levels are sorted like this:
	 * _Silent > Error > Warning > Info > Debug
	 *
	 * @param filterLevel   The minimum level of log messages that will be logged.
	 *                          If messages with a lower severity are sent to the
	 *                          logger, they will be ignored.
	 */
	void SetLogFilterLevel(Level filterLevel)
	{
		levelFilter = filterLevel;
	}

private:
	/// Log messages are additional written to this file stream.
	std::fstream file;

	/// When this is built in Debug mode, the calling context file path will
	/// be printed in full (true) or it will be abbreviated to just the file
	/// name and extension (false).
	bool debugFilePathIsPrintedInFull;

	Level levelFilter;
};
