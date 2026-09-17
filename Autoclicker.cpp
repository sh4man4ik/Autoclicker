#include <iostream>
#include <fstream>
#include <windows.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void click()
{
	INPUT inputs[2] = {};

	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	inputs[1].type = INPUT_MOUSE;
	inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	SendInput(2, inputs, sizeof(INPUT));
}

void autoclicker(char& startKey, char& stopKey, bool& canClick, double& clickInterval)
{
	while (true)
	{
		if (GetAsyncKeyState(startKey) & 0x8000 && !canClick)
		{
			std::cout << "Clicking started" << std::endl;
			canClick = true;
		}

		if (canClick)
		{
			click();

			for (int i = 0; i < clickInterval; i += 10)
			{
				Sleep(10);

				if (GetAsyncKeyState(stopKey) & 0x8000)
				{
					std::cout << "Clicking stopped" << std::endl;
					canClick = false;
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

void displayStartText(char &startKey, char &stopKey, double &clicksPerSecond)
{
	std::cout << "Autoclicker launched successfully" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Autoclicker settings:" << std::endl;
	std::cout << "Start Key: " << startKey << std::endl;
	std::cout << "Stop Key: " << stopKey << std::endl;
	std::cout << "Clicks Per Second: " << clicksPerSecond << std::endl;
	std::cout << "" << std::endl;
}

void setKeys(char &startKey, char &stopKey, double &clicksPerSecond, json &data)
{
	try
	{
		std::string startKeyString = data.value("start_key", "B");
		startKey = startKeyString[0];

		std::string stopKeyString = data.value("stop_key", "S");
		stopKey = stopKeyString[0];

		clicksPerSecond = data.value("clicks_per_second", 1);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

json readSettings()
{
	std::ifstream settings("settings.json");
	json data;

	if (settings.is_open())
	{
		data = json::parse(settings);
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
		std::cout << "Error reading settings.json file" << std::endl;
		return 0;
	}

	bool canClick = false;
	char startKey;
	char stopKey;
	double clicksPerSecond;

	setKeys(startKey, stopKey, clicksPerSecond, data);

	double clickInterval = 1000 / clicksPerSecond;

	displayStartText(startKey, stopKey, clicksPerSecond);

	autoclicker(startKey, stopKey, canClick, clickInterval);

	return 0;
}
