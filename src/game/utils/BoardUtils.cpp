// Corresponding Header
#include "game/utils/BoardUtils.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "utils/drawing/Rectangle.h"
#include "game/pieces/types/Pawn.h"

namespace{
constexpr auto BOARD_SIZE = 8;
constexpr auto FIRST_TILE_X_POS = 58;
constexpr auto FIRST_TILE_Y_POS = 60;
constexpr auto TILE_SIZE = 98;
}

BoardPos BoardUtils::getBoardPos(const Point& absPos){
	return { (absPos._y - FIRST_TILE_Y_POS) / TILE_SIZE,
			 (absPos._x - FIRST_TILE_X_POS) / TILE_SIZE	};
}

Point BoardUtils::getAbsPos(const BoardPos& boardPos){
	return { boardPos.col * TILE_SIZE + FIRST_TILE_X_POS,
			 boardPos.row * TILE_SIZE + FIRST_TILE_Y_POS };
}

bool BoardUtils::isInsideBoard(const BoardPos& boardPos){
	return isInsideBoard(getAbsPos(boardPos));
}

bool BoardUtils::isInsideBoard(const Point& absPos){
	const Rectangle bound { FIRST_TILE_X_POS, FIRST_TILE_Y_POS,
							BOARD_SIZE * TILE_SIZE, BOARD_SIZE * TILE_SIZE };
	return bound.isPointInside(absPos);
}


Defines::PlayerId BoardUtils::getOpponentId(int32_t activePlayerId){
	return activePlayerId == Defines::WHITE_PLAYER_ID ?
							 	 Defines::BLACK_PLAYER_ID : Defines::WHITE_PLAYER_ID;
}

BoardPos BoardUtils::getAdjacentPos(Defines::Direction dir, const BoardPos &currPos){
	BoardPos pos = currPos;
	switch(dir){
	case Defines::UP_LEFT:
		--pos.col;
		--pos.row;
		break;
	case Defines::UP:
		--pos.row;
		break;
	case Defines::UP_RIGHT:
		--pos.row;
		++pos.col;
		break;
	case Defines::RIGHT:
		++pos.col;
		break;
	case Defines::DOWN_RIGHT:
		++pos.row;
		++pos.col;
		break;
	case Defines::DOWN:
		++pos.row;
		break;
	case Defines::DOWN_LEFT:
		++pos.row;
		--pos.col;
		break;
	case Defines::LEFT:
		--pos.col;
		break;
	default:
		std::cerr << "Error! Received invalid dir: " << dir << std::endl;
		break;
	}

	return pos;
}

bool BoardUtils::doCollideWithPiece(const BoardPos &selectedPos,
								    const ChessPiece::PlayerPieces &pieces,
								    int32_t& outCollisionRelativeId) {

	const size_t size = pieces.size();
	for(size_t i = 0; i < size; ++i){
		if(selectedPos == pieces[i]->getBoardPos()){
			outCollisionRelativeId = static_cast<int32_t>(i);
			return true;
		}
	}

	return false;
}

bool BoardUtils::doCollideWithPawnEnPassant(const BoardPos &selectedPos,
											 const ChessPiece::PlayerPieces &pieces,
											 int32_t& outCollisionRelativeId){

	const size_t size = pieces.size();
	for(size_t i = 0; i < size; ++i){

		if(pieces[i]->getPieceType() != PieceType::PAWN){
			continue;
		}

		const auto& p = static_cast<Pawn*>(pieces[i].get());

		if(!p->enPassantDanger){
			continue;
		}

		if(selectedPos != p->getBoardPosBack()  ){
			continue;
		}

		outCollisionRelativeId = static_cast<int32_t>(i);
		return true;
	}

	return false;
}

BoardPos BoardUtils::getKnightAdjPos(Defines::KnightDirections dir, const BoardPos &currPos) {
	BoardPos pos = currPos;
	switch(dir){
	case Defines::KNIGHT_UP_LEFT:
		--pos.col;
		pos.row -= 2;
		break;
	case Defines::KNIGHT_UP_RIGHT:
		++pos.col;
		pos.row -= 2;
		break;
	case Defines::KNIGHT_RIGHT_UP:
		pos.col += 2;
		--pos.row;
		break;
	case Defines::KNIGHT_RIGHT_DOWN:
		pos.col += 2;
		++pos.row;
		break;
	case Defines::KNIGHT_DOWN_RIGHT:
		++pos.col;
		pos.row += 2;
		break;
	case Defines::KNIGHT_DOWN_LEFT:
		--pos.col;
		pos.row += 2;
		break;
	case Defines::KNIGHT_LEFT_DOWN:
		pos.col -= 2;
		++pos.row;
		break;
	case Defines::KNIGHT_LEFT_UP:
		pos.col -= 2;
		--pos.row;
		break;
	default:
		std::cerr << "Error! Received invalid knight_dir: " << dir << std::endl;
		break;
	}

	return pos;
}


TileType BoardUtils::getTileType(const BoardPos &boardPos,
							     const ChessPiece::PlayerPieces &playerPieces,
								 const ChessPiece::PlayerPieces &enemyPieces){

	int32_t collisionIdx = -1;
	if(doCollideWithPiece(boardPos, playerPieces, collisionIdx)){
		return TileType::GUARD;
	}

	if(doCollideWithPiece(boardPos, enemyPieces, collisionIdx)){
		return TileType::TAKE;
	}

	return TileType::MOVE;
}
















