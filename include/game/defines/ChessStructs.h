#ifndef INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_
#define INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_
//C system headers

//C++ system headers
#include <vector>

//Other libraries headers

//Own components headers
#include "game/utils/BoardPos.h"

//Forward declaration

struct TileData {
	BoardPos boardPos;
	TileType tileType = TileType::MOVE;

};

using MoveDirection = std::vector<BoardPos>;



#endif /* INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_ */
