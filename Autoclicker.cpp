#include <iostream>
#include <windows.h>

void click()
{
	INPUT inputs[2] = {};

	inputs[0].type = INPUT_MOUSE;
	inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

	inputs[1].type = INPUT_MOUSE;
	inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

	SendInput(2, inputs, sizeof(INPUT));
}

int main()
{
	char startKey{ 'B' };
	char stopKey{ 'S' };
	double clicksPerSecond = 1;

	double clickInterval = 1000 / clicksPerSecond;
	bool canClick = false;

	std::cout << "Autoclicker launched successfully" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Autoclicker settings:" << std::endl;
	std::cout << "Start Key: " << startKey << std::endl;
	std::cout << "Stop Key: " << stopKey << std::endl;
	std::cout << "Clicks Per Second: " << clicksPerSecond << std::endl;
	std::cout << "" << std::endl;

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

	return 0;
}
