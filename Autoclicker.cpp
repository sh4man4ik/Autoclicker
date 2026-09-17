#include <iostream>
#include <fstream>
#include <windows.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void click(bool& canLeftClick, bool& canRightClick)
{
	INPUT inputs[2] = {};

	inputs[0].type = INPUT_MOUSE;
	inputs[1].type = INPUT_MOUSE;

	if (canLeftClick)
	{
		inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	}
	else
	{
		inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	}

	SendInput(2, inputs, sizeof(INPUT));
}

void autoclicker(char& startLeftKey, char& startRightKey, char& stopKey, bool& canLeftClick, bool& canRightClick, double& clickInterval)
{
	while (true)
	{
		if (GetAsyncKeyState(startLeftKey) & 0x8000 && !canLeftClick && !canRightClick)
		{
			std::cout << "Clicking started" << std::endl;
			canLeftClick = true;
		}

		if (GetAsyncKeyState(startRightKey) & 0x8000 && !canRightClick && !canLeftClick)
		{
			std::cout << "Clicking started" << std::endl;
			canRightClick = true;
		}

		if (canLeftClick || canRightClick)
		{
			click(canLeftClick, canRightClick);

			for (int i = 0; i < clickInterval; i += 10)
			{
				Sleep(10);

				if (GetAsyncKeyState(stopKey) & 0x8000)
				{
					std::cout << "Clicking stopped" << std::endl;
					canLeftClick = false;
					canRightClick = false;
					break;
				}
			}
		}
		else
		{
			Sleep(10);
		}
	}
}

void displayStartText(char& startLeftKey, char& startRightKey, char& stopKey, double& clicksPerSecond)
{
	std::cout << "Mouse autoclicker launched successfully" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Autoclicker settings:" << std::endl;
	std::cout << "Start Left Key: " << startLeftKey << std::endl;
	std::cout << "Start Right Key: " << startRightKey << std::endl;
	std::cout << "Stop Key: " << stopKey << std::endl;
	std::cout << "Clicks Per Second: " << clicksPerSecond << std::endl;
	std::cout << "" << std::endl;
}

void setKeys(char& startLeftKey, char& startRightKey, char& stopKey, double& clicksPerSecond, json& data)
{
	try
	{
		std::string startKeyLeftString = data.value("start_key_left", "L");
		startLeftKey = startKeyLeftString[0];

		std::string startRightKeyString = data.value("start_key_right", "R");
		startRightKey = startRightKeyString[0];

		std::string stopKeyString = data.value("stop_key", "S");
		stopKey = stopKeyString[0];

		clicksPerSecond = data.value("clicks_per_second", 1);
		if (clicksPerSecond <= 0)
		{
			clicksPerSecond = 1;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		throw;
	}
}

json readSettings()
{
	std::ifstream settings("settings.json");
	json data;

	if (settings.is_open())
	{
		try
		{
			data = json::parse(settings);
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
			data = "error";
		}
	}
	else
	{
		data = "error";
	}

	return data;
}

int main()
{
	json data = readSettings();

	if (data == "error")
	{
		std::cout << "Error: Failed to read settings.json" << std::endl;
		return 0;
	}

	bool canLeftClick = false;
	bool canRightClick = false;
	char startKeyLeft;
	char startKeyRight;
	char stopKey;
	double clicksPerSecond;
	double clickInterval;

	try
	{
		setKeys(startKeyLeft, startKeyRight, stopKey, clicksPerSecond, data);
		clickInterval = 1000 / clicksPerSecond;
		displayStartText(startKeyLeft, startKeyRight, stopKey, clicksPerSecond);
		autoclicker(startKeyLeft, startKeyRight, stopKey, canLeftClick, canRightClick, clickInterval);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
