// Corresponding Header
#include "game/pieces/types/Pawn.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "game/utils/BoardUtils.h"

int32_t Pawn::init(const ChessPieceCfg& cfg) {
	if(EXIT_SUCCESS != ChessPiece::init(cfg)){
		std::cerr << "ChessPiece::init() failed" << std::endl;
	}

	_MOVE_DIRECTION = (_playerId == Defines::WHITE_PLAYER_ID) ?
											Defines::UP : Defines::DOWN;

	_INITIAL_ROW = (_playerId == Defines::WHITE_PLAYER_ID) ?
			Defines::WHITE_PLAYER_START_PAWN_ROW : Defines::BLACK_PLAYER_START_PAWN_ROW;

	_BACKWARDS_ROW = (_playerId == Defines::WHITE_PLAYER_ID) ? - 1 :  + 1;

	_END_ROW = (_playerId == Defines::WHITE_PLAYER_ID) ?
			Defines::WHITE_PLAYER_START_END_ROW : Defines::BLACK_PLAYER_START_END_ROW;

	_DIRS = (_playerId == Defines::WHITE_PLAYER_ID) ?
			std::array<Defines::Direction, allowedNumOfDirs>
						{ Defines::UP_LEFT, Defines::UP_RIGHT, Defines::UP }
		  : std::array<Defines::Direction, allowedNumOfDirs>
						{ Defines::DOWN_LEFT, Defines::DOWN_RIGHT, Defines::DOWN };

	return EXIT_SUCCESS;
}

void Pawn::setBoardPos(const BoardPos& boardPos, const bool derived){
	ChessPiece::setBoardPos(boardPos);

	if( derived && _END_ROW == _boardPos.row && isPromotionAllowed ){
		selfPromotion(getPlayerId());
	}
}

std::unordered_map<Defines::Direction, MoveDirection> Pawn::getBoardMoves() const {
	std::unordered_map<Defines::Direction, MoveDirection> boardMoves;

	for(const auto& dir : _DIRS){
		BoardPos futurePos = BoardUtils::getAdjacentPos(dir, _boardPos);
		if(BoardUtils::isInsideBoard(futurePos)){
			boardMoves[dir].push_back(futurePos);
		}
		if(dir == _MOVE_DIRECTION){
			boardMoves[dir].push_back( BoardUtils::getAdjacentPos(dir, futurePos) );
		}
	}

	return boardMoves;
}

std::vector<TileData> Pawn::getMoveTiles(
			const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces,
			[[maybe_unused]]const bool firstCall) const {

	std::vector<TileData> moveTiles;

	const auto boardMoves = getBoardMoves();

	const auto opponentId = BoardUtils::getOpponentId(_playerId);

	for (const auto& [dir, vBoardPos] : boardMoves) {
		if (vBoardPos.empty()) {
			continue;
		}

		for(const auto& boardPos : vBoardPos){
			TileType tileType = BoardUtils::getTileType(boardPos,
													    activePieces[_playerId],
													    activePieces[opponentId]);

			if(tileType == TileType::MOVE){
				int32_t collisionIdx = -1;
				if(BoardUtils::doCollideWithPawnEnPassant(boardPos,
														  activePieces[opponentId],
														  collisionIdx)){
					tileType = TileType::TAKE;
				}
			}

			TileData tileData;
			tileData.boardPos = boardPos;
			tileData.tileType = tileType;

			if(dir == _MOVE_DIRECTION && tileType != TileType::MOVE){
				break;
			}

			if(dir != _MOVE_DIRECTION && tileType == TileType::MOVE){
				continue;
			}

			if(boardPos != vBoardPos.front() && (_boardPos.row != _INITIAL_ROW)){
				continue;
			}

			if(firstCall){
				if(!isDangerOfCheck(tileData.boardPos, activePieces)){
					moveTiles.push_back(tileData);
				}
			} else {
				moveTiles.push_back(tileData);
			}

			if(TileType::MOVE != tileType){
				break;
			}
		}
	}

	return moveTiles;
}


int32_t Pawn::getInitialRow() const {
	return _INITIAL_ROW;
}

Defines::Direction Pawn::getMoveDir() const {
	return _MOVE_DIRECTION;
}

BoardPos Pawn::getBoardPosBack() const {
	return BoardPos(_boardPos.row - _BACKWARDS_ROW, _boardPos.col);
}




