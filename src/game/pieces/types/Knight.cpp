// Corresponding Header
#include "game/pieces/types/Knight.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "game/utils/BoardUtils.h"

std::unordered_map<Defines::Direction, MoveDirection> Knight::getBoardMoves() const {
	std::unordered_map<Defines::Direction, MoveDirection> boardMoves;

	for(const auto& dir : knightDirs){
		boardMoves[static_cast<Defines::Direction>(dir)].reserve(maxRootMoves);

		BoardPos futurePos = BoardUtils::getKnightAdjPos(dir, _boardPos);
		if(BoardUtils::isInsideBoard(futurePos)){
			boardMoves[static_cast<Defines::Direction>(dir)].push_back(futurePos);
		}
	}

	return boardMoves;
}

