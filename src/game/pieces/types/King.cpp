// Corresponding Header
#include "game/pieces/types/King.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "game/utils/BoardUtils.h"

void King::setBoardPos(const BoardPos& boardPos, const bool derived){
	ChessPiece::setBoardPos(boardPos);

	if( derived ){
		isQueenSideCastlePossible = false;
		isKingSideCastlePossible = false;
	}
}

std::unordered_map<Defines::Direction, MoveDirection> King::getBoardMoves() const {
	std::unordered_map<Defines::Direction, MoveDirection> boardMoves;

	for(const auto& dir : kingDirs){
		int32_t additionToDir = 0;
		auto isCastlePossible = true;
		auto freePositionsInbetween = false;
		auto isAttack = true;

		switch(dir){
		case Defines::LEFT:
			additionToDir = 1;
			isCastlePossible = isQueenSideCastlePossible;
			freePositionsInbetween = isFreeToQueenSideRook;
			isAttack = isCheckOnTheLeft;
			break;
		case Defines::RIGHT:
			additionToDir = 1;
			isCastlePossible = isKingSideCastlePossible;
			freePositionsInbetween = isFreeToKingSideRook;
			isAttack = isCheckOnTheRight;
			break;
		default:
			break;
		}

		boardMoves[dir].reserve(maxRootMoves + additionToDir);

		BoardPos futurePos = BoardUtils::getAdjacentPos(dir, _boardPos);
		if(BoardUtils::isInsideBoard(futurePos)){
				boardMoves[dir].push_back(futurePos);
		}

		if( isCastlePossible
		 && additionToDir  //additionToDir is used instead of checking if dir == Defines::LEFT or dir == Defines::RIGHT !!!
		 && freePositionsInbetween
		 && !isAttack)
		{
			futurePos = BoardUtils::getAdjacentPos(dir, futurePos);
			boardMoves[dir].push_back(futurePos);
		}
	}

	return boardMoves;
}














