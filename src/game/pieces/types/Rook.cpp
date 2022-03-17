// Corresponding Header
#include "game/pieces/types/Rook.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "game/utils/BoardUtils.h"

void Rook::setBoardPos(const BoardPos& boardPos){
	ChessPiece::setBoardPos(boardPos);
}

std::unordered_map<Defines::Direction, MoveDirection> Rook::getBoardMoves() const {
	std::unordered_map<Defines::Direction, MoveDirection> boardMoves;
	for(const auto& dir : rookDirs){
		boardMoves[dir].reserve(maxRootMoves);

		BoardPos futurePos = BoardUtils::getAdjacentPos(dir, _boardPos);

		while(BoardUtils::isInsideBoard(futurePos)){
			boardMoves[dir].push_back(futurePos);
			futurePos = BoardUtils::getAdjacentPos(dir, futurePos);
		}
	}

	return boardMoves;
}














