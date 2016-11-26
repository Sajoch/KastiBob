#ifndef __UTILS_HPP
#define __UTILS_HPP

enum class ClientState { 
	NONE, LOGIN, ENTER_GAME, GAME,
};
enum class ClientDirectory {
	NORTH, EAST, SOUTH, WEST, NE, SE, SW, NW
};

#endif
