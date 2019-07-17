#pragma once

class Debug
{
public:
	static void Log(const std::string& context)
	{
		std::cout << context << std::endl;
	}
};