# country_quiz_course_work
A fun little country quiz game that will definitely test your geography knowledge from middle school!

>This game has been developed on macOS and might not work properly on other systems. What we definitely know and can't fix is that emojis are not showing up in Windows command prompt/Terminal/PowerShell, as they don't have emoji support. If can, please use WSL terminal, as it is known to fix the issue.

### Installation
Use one of the executables available in the Releases section, compiled for your platform.

### Compiling
To compile on Windows and macOS: `g++ -std=c++11 main.cpp menu.cpp -o country_quiz`

#### Requirements
- Have `g++` installed on your machine -  included with macOS. On Windows, install it through MYSYS2 and `pacman`
- `Boost` C++ library collection needs to be compiled for your system, as it is not included in the `libs` folder of source code.