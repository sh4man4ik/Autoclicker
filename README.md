# What is it?

This is a simple mouse autoclicker that can click with both the left and right mouse buttons.

# Quick Start

1. Download the *.exe* file from GitHub Releases
2. Create a *settings.json* file next to the *.exe* file with the following content (**you can use your own keys; these are just defaults**):
```json
{
	"start_key_left": "L",
	"start_key_right": "R",
	"stop_key": "S",
	"exit_key": "E",
	"clicks_per_second": 5
}
```

# Tech Stack

The following technologies are used to develop the bot: **C++**, **CMake**, **vcpkg** and **nlohmann/json**.