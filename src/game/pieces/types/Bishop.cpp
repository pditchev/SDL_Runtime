// Corresponding Header
#include "game/pieces/types/Bishop.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "game/utils/BoardUtils.h"

std::unordered_map<Defines::Direction, MoveDirection> Bishop::getBoardMoves() const {
	std::unordered_map<Defines::Direction, MoveDirection> boardMoves;

	for(const auto& dir : bishopDirs){
		boardMoves[dir].reserve(maxRootMoves);

		BoardPos futurePos = BoardUtils::getAdjacentPos(dir, _boardPos);
		while(BoardUtils::isInsideBoard(futurePos)){
			boardMoves[dir].push_back(futurePos);
			futurePos = BoardUtils::getAdjacentPos(dir, futurePos);
		}
	}

	return boardMoves;
}
