#include "logger/logger.hpp"
#include <sstream>
#include <exception>

Logger* mainLoggerPtr = nullptr;

std::initializer_list<std::string> ext_whitelist
{
	".dll",
	".asi",
};

bool ends_with(std::string const& value, std::string const& ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
void initLogger()
{
	if (mainLoggerPtr == nullptr)
	{
		mainLoggerPtr = new Logger();
	}
	else
	{
		delete mainLoggerPtr;
		mainLoggerPtr = new Logger();
	}
}

void init()
{
	initLogger();
	if (mainLoggerPtr == nullptr)
	{
		throw std::runtime_error("An error was encountered while trying to create the main logger.");
	}

	mainLoggerPtr->init("Haggle Mod Loader");
	std::printf("----- Haggle Mod Loader -----\n");

	std::stringstream dirDescription;
	dirDescription << "In directory \"" << std::filesystem::absolute(std::filesystem::path("./")).string() << "\"";
	LOG_INFO(mainLoggerPtr, "%s", dirDescription.str().c_str());

	if (!std::filesystem::exists("./mods/"))
	{
		LOG_ERROR(mainLoggerPtr, "No mods folder found!");
		LOG_INFO(mainLoggerPtr, "Make a mods folder in your Peggle directory");
	}
	else
	{
		std::filesystem::path orig_path = std::filesystem::current_path();
		std::filesystem::current_path("./mods/");

		std::vector<std::string> files;
		for (const auto& entry : std::filesystem::directory_iterator("./"))
		{
			if (!entry.is_directory())
			{
				files.emplace_back(entry.path().string());
			}
		}

		LOG_INFO(mainLoggerPtr, "Loading Mods...");
		static int count = 0;
		for (const auto& bin : files)
		{
			for (const auto& ext : ext_whitelist)
			{
				if (ends_with(bin, ext))
				{
					LoadLibraryA(bin.c_str());

					if (GetLastError() != 0)
					{
						LOG_ERROR(mainLoggerPtr, "%s errored! (%i)", bin.c_str(), GetLastError());
					}
					else
					{
						LOG_INFO(mainLoggerPtr, "%s loaded!", bin.c_str());
						++count;
					}
				}
			}
		}

		std::filesystem::current_path(orig_path);

		if (count == 1)
		{
			LOG_INFO(mainLoggerPtr, "1 mod loaded");
		}
		else if (count > 1)
		{
			LOG_INFO(mainLoggerPtr, "%i mods loaded", count);
		}
		else if (count <= 0)
		{
			LOG_WARNING(mainLoggerPtr, "No mods loaded");
		}

		LOG_INFO(mainLoggerPtr, "Ready!");
	}
}

DWORD WINAPI OnAttachImpl(LPVOID lpParameter)
{
	init();
	return 0;
}

DWORD WINAPI OnAttach(LPVOID lpParameter)
{
	__try
	{
		return OnAttachImpl(lpParameter);
	}
	__except (0)
	{
		FreeLibraryAndExitThread((HMODULE)lpParameter, 0xDECEA5ED);
	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, OnAttach, hModule, 0, nullptr);
		return true;
	}

	return false;
}
