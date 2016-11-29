#ifndef __UTILS_HPP
#define __UTILS_HPP

enum class ClientState { 
	NONE, LOGIN, ENTER_GAME, GAME,
};
enum class ClientDirectory {
	STOP, 
	LOOK_NORTH, LOOK_EAST, LOOK_SOUTH, LOOK_WEST,
	NORTH, EAST, SOUTH, WEST, NE, SE, SW, NW
};

#endif
