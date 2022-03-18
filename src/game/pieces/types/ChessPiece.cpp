// Corresponding Header
#include "game/pieces/types/ChessPiece.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "sdl_utils/InputEvent.h"
#include "game/utils/BoardUtils.h"
#include "game/pieces/types/Pawn.h"

int32_t ChessPiece::init(const ChessPieceCfg& cfg){
	if(cfg._pieceType == PieceType::UNKNOWN){
		std::cerr << "Error, invalid _pieceType provided: " << static_cast<int32_t>(cfg._pieceType) << std::endl;
		return EXIT_FAILURE;
	}

	if(cfg.rsrcId == INVALID_RSRC_ID){
		std::cerr << "Error, invalid RsrcId provided" << std::endl;
		return EXIT_FAILURE;
	}

	_boardPos = cfg._boardPos;
	_playerId = static_cast<Defines::PlayerId>(cfg._playerId);
	_pieceType = cfg._pieceType;

	_pieceImg.create(cfg.rsrcId, BoardUtils::getAbsPos(_boardPos));
	_pieceImg.setFrame(static_cast<int32_t>(_pieceType));

	return EXIT_SUCCESS;
}

void ChessPiece::draw() const{
	_pieceImg.draw();
}

bool ChessPiece::containsEvent(const InputEvent& e) const {
	return _pieceImg.containsPoint(e.pos);
}

void ChessPiece::setBoardPos(const BoardPos& boardPos, [[maybe_unused]] const bool derived) {
	_boardPos = boardPos;
	_pieceImg.setPosition(BoardUtils::getAbsPos(_boardPos));
}

BoardPos ChessPiece::getBoardPos() const {
	return _boardPos;
}

int32_t ChessPiece::getPlayerId() const {
	return _playerId;
}

PieceType ChessPiece::getPieceType() const {
	return _pieceType;
}

//void ChessPiece::setWidgetFlip(WidgetFlip flipType){
//	_pieceImg.setFlipType(flipType);
//}

std::vector<TileData> ChessPiece::getMoveTiles(
			const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces,
			const bool firstCall) const {

	std::vector<TileData> moveTiles;

	const auto boardMoves = getBoardMoves();
	const auto opponentId = BoardUtils::getOpponentId(_playerId);

	for (const auto& [dir, vBoardPos] : boardMoves) {
		if (vBoardPos.empty()) {
			continue;
		}

		for(const auto& boardPos : vBoardPos){
			const auto tileType = BoardUtils::getTileType(	boardPos,
															activePieces[_playerId],
															activePieces[opponentId] );

			TileData tileData;
			tileData.boardPos = boardPos;
			tileData.tileType = tileType;

			if(firstCall){
				if(!isDangerOfCheck(tileData.boardPos, activePieces)){
					if(getPieceType() == PieceType::KING){
						if(TileType::GUARD == tileType){
							break;
						}
					}
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

bool ChessPiece::isDangerOfCheck(const BoardPos& boardPos,
		const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const {

	const auto& currPlayer = _playerId;
	const auto& opponent = BoardUtils::getOpponentId(currPlayer);
	const auto& targetPos = boardPos;

	bool oppPieceErased = false;
	BoardPos tempBoardPosOpp;
	const auto& iBoardPos = BoardPos{-1, -1};

	if(getPieceType() == PieceType::PAWN){
		static_cast<const Pawn*>(this)->isPromotionAllowed = false;
	}

	// if we can attack -> let's attack:
	int32_t collisionIdx = -1;
	if(BoardUtils::doCollideWithPiece(targetPos, activePieces[opponent], collisionIdx)){
		tempBoardPosOpp = activePieces[opponent][collisionIdx]->getBoardPos();
		activePieces[opponent][collisionIdx]->setBoardPos(iBoardPos);
		oppPieceErased = true;
	} else if(getPieceType() == PieceType::PAWN){
		if(BoardUtils::doCollideWithPawnEnPassant(targetPos, activePieces[opponent], collisionIdx )){
			tempBoardPosOpp = activePieces[opponent][collisionIdx]->getBoardPos();
			activePieces[opponent][collisionIdx]->setBoardPos(iBoardPos);
			oppPieceErased = true;
		}
	}

	// let's move to the new position:
	int32_t currPiece = -1;
	BoardPos prevBoardPos;
	for(const auto& piece : activePieces[currPlayer]){
		++currPiece;
		if(piece->getBoardPos() == _boardPos){
			prevBoardPos = _boardPos;
			piece->setBoardPos(targetPos);
			break;
		}
	}

	auto rollback = [&] {	
		activePieces[currPlayer][currPiece]->setBoardPos(prevBoardPos);
		if(oppPieceErased){
			activePieces[opponent][collisionIdx]->setBoardPos(tempBoardPosOpp);
		}
		if(getPieceType() == PieceType::PAWN){
			static_cast<const Pawn*>(this)->isPromotionAllowed = true;
		}
	};

	//let's check if we opened a hole :(
	for(const auto& attackers : activePieces[opponent]){

		const auto& possibleMoves = attackers->getMoveTiles(activePieces, false);

		for(const auto& candidateMove : possibleMoves){
			if(candidateMove.boardPos != getKingPos(activePieces[currPlayer])){
				continue;
			}
			
			// if we reached here -> we can be checked ... roll back everything!!!
			rollback();

			// ...and announce: "there is danger of being checked":
			return true;
		}
	}

	// if we got here -> no problem discovered, and again ... roll back everything:
	rollback();

	// ... and announce: "everything is OK! no check is possible":
	return false;
}

BoardPos ChessPiece::getKingPos( const ChessPiece::PlayerPieces& pieces) const {
	for(const auto& piece : pieces){
		if(piece->getPieceType() == PieceType::KING){
			return piece->getBoardPos();
		}
	}

	return BoardUtils::getBoardPos(Point::UNDEFINED);
}

