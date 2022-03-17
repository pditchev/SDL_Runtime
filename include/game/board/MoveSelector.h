#ifndef INCLUDE_GAME_BOARD_MOVESELECTOR_H_
#define INCLUDE_GAME_BOARD_MOVESELECTOR_H_
//C system headers

//C++ system headers
#include <array>

//Other libraries headers

//Own components headers
#include "game/defines/ChessDefines.h"
#include "game/defines/ChessStructs.h"
#include "manager_utils/drawing/Image.h"

//Forward declaration

class MoveSelector {
public:
	int32_t init(int32_t rsrcId);
	void draw() const;
	void markTiles(const std::vector<TileData> &markedTiles);
	void unmarkTiles();

	enum InternalDefines {
		MAX_ACTIVE_TILES = 28
	};
	std::array<Image, MAX_ACTIVE_TILES> _tileImgs;

	size_t _activeTiles { 0 };
};

#endif /* INCLUDE_GAME_BOARD_MOVESELECTOR_H_ */
