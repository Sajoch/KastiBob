#ifndef __UTILS_HPP
#define __UTILS_HPP

#include <string>

void Error(std::string text, std::string file, int line);

#define DEBUG(text) Error(text, __FILE__, __LINE__);

enum class ClientState {
	NONE, LOGIN, ENTER_GAME, GAME,
};
enum class ClientDirectory {
	STOP,
	LOOK_NORTH, LOOK_EAST, LOOK_SOUTH, LOOK_WEST,
	NORTH, EAST, SOUTH, WEST, NE, SE, SW, NW
};

#endif
