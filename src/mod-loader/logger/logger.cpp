#include "logger.hpp"

#include <format>

Logger::Logger() : debugFilePathIsPrintedInFull(false), levelFilter(Level::Debug)
{

}

Logger::~Logger()
{

}

void Logger::PrintWithLevel(Level msgLevel, const char* msg, std::source_location callingFunc)
{
	const char* logLevelText = nullptr;

	if (msgLevel > levelFilter)
	{
		return;
	}

	switch (msgLevel)
	{
	case Level::Error:
	{
		logLevelText = "[ ERROR ]";
		break;
	}
	case Level::Warning:
	{
		logLevelText = "[ WARNING ]";
		break;
	}
	case Level::Info:
	{
		logLevelText = "[ INFO ]";
		break;
	}
	case Level::Debug:
	{
		logLevelText = "[ DEBUG ]";
		break;
	}
	default:
	{
		logLevelText = "[ MESSAGE ]";
		break;
	}
	}

#ifdef DEBUG
	std::string filenamePath(callingFunc.file_name());

	if (!debugFilePathIsPrintedInFull)
	{
		const uint32_t LAST_SEPARATOR_INDEX = filenamePath.find_last_of("/\\");

		if (LAST_SEPARATOR_INDEX < filenamePath.length())
		{
			filenamePath.erase(0, LAST_SEPARATOR_INDEX + 1);
		}
	}

	std::string messageWithLevel = std::format("{}[ {}:{}:{} ]: {}\n",
											   logLevelText,
											   filenamePath,
											   callingFunc.line(),
											   callingFunc.function_name(),
											   msg);
#else
	std::string messageWithLevel = std::format("{}: {}\n", logLevelText, msg);
#endif

	if (file.is_open())
	{
		file << messageWithLevel;
		file.flush();
	}

	std::cout << messageWithLevel;
}
