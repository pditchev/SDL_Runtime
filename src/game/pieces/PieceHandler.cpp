// Corresponding Header
#include "game/pieces/PieceHandler.h"

// C system includes

// C++ system includes
//#include <functional>

// Third party includes

// Own includes
#include "game/proxies/GameBoardProxy.h"
#include "game/utils/BoardUtils.h"
#include "sdl_utils/InputEvent.h"
#include "game/pieces/types/Pawn.h"
#include "game/pieces/types/King.h"
#include "game/pieces/types/Rook.h"

namespace {
constexpr auto ROOK_QUEEN_SIDE_ID = 8;
constexpr auto ROOK_KING_SIDE_ID = 15;
constexpr auto KING_ID = 12;
constexpr auto KING_COL = 4;
}

int32_t PieceHandler::init(GameBoardProxy* gameBoardProxy,
						   int32_t whitePiecesRsrcId,
						   int32_t blackPiecesRsrcId,
						   int32_t unfinishedPieceTextId){

	if(nullptr == gameBoardProxy){
		std::cerr << "Error, nullptr provided for gameBoardProxy" << std::endl;
		return EXIT_FAILURE;
	}
	_gameBoardProxy = gameBoardProxy;

	if(EXIT_SUCCESS != PieceHandlerPopulator::populatePieceHandler(whitePiecesRsrcId,
																   blackPiecesRsrcId,
																   unfinishedPieceTextId,
																   _pieces)){

		std::cerr << "Error! PieceHandlerPopulator::populatePieceHandler() failed" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void PieceHandler::draw() const {
	for(const ChessPiece::PlayerPieces& playerPieces : _pieces){
		for(const auto& piece : playerPieces){
			piece->draw();
		}
	}
}

void PieceHandler::handleEvent(const InputEvent& e) {
	if(e.type != TouchEvent::TOUCH_RELEASE){
		return;
	}

	_isPieceGrabbed ? handlePieceGrabbedEvent(e) : handlePieceUngrabbedEvent(e);
}

void PieceHandler::handlePieceGrabbedEvent(const InputEvent& e){
	_isPieceGrabbed = false;

	if(!BoardUtils::isInsideBoard(e.pos)){
		_gameBoardProxy->onPieceUngrabbed();
		return;
	}

	const BoardPos boardPos = BoardUtils::getBoardPos(e.pos);
	if(!_gameBoardProxy->isMoveAllowed(boardPos)){
		_gameBoardProxy->onPieceUngrabbed();
		return;
	}

	doMovePiece(boardPos);
}

void PieceHandler::handlePieceUngrabbedEvent(const InputEvent& e){

	const auto& playerId = getCurrPlayerId();

	int32_t relativePieceId = 0;

	for(const auto& piece : _pieces[playerId]){

		// if(piece->getPieceType() == PieceType::KING){
		// 	auto king = static_cast<King*>(piece.get());
		// 	std::cout << std::boolalpha << king->isCheckOnTheLeft << ' ' << king->isCheckOnTheRight << std::endl;

		// 	std::cout << std::boolalpha << king->isKingSideCastlePossible << std::endl;
		// }		

		if(piece->containsEvent(e)){

			_selectedPieceId = relativePieceId;
			_isPieceGrabbed = true;

			// if(auto king = dynamic_cast<King*>(piece.get())){
			if(piece->getPieceType() == PieceType::KING){
				auto king = static_cast<King*>(piece.get());

				if(king->isQueenSideCastlePossible && king->isKingSideCastlePossible){
					discoverCheckNearbyKing(king);
					king->isFreeToQueenSideRook = isFreeBetweenKingAndRook(Defines::QUEEN_SIDE_ROOK);
					king->isFreeToKingSideRook = isFreeBetweenKingAndRook(Defines::KING_SIDE_ROOK);
				}
			}

			std::vector<TileData> moveTile = _pieces[playerId][_selectedPieceId]->getMoveTiles(_pieces);

			_gameBoardProxy->onPieceGrabbed(BoardUtils::getBoardPos(e.pos), moveTile);
			return;
		}
		++relativePieceId;
	}
}

void PieceHandler::doMovePiece(const BoardPos& targetPos){

	const auto& player = getCurrPlayerId();
	const auto& opponent = BoardUtils::getOpponentId(player);
	const auto& currentPiece = _pieces[player][_selectedPieceId];

	if(currentPiece->getPieceType() == PieceType::PAWN){
		const auto& pawn = static_cast<Pawn*>(currentPiece.get());
		if(pawn->getBoardPos().row == pawn->getInitialRow()){
			if(targetPos != BoardUtils::getAdjacentPos(pawn->getMoveDir(), pawn->getBoardPos())){
				pawn->enPassantDanger = true;
			}
		}
	}
	
	if(int32_t collisionIdx = -1; BoardUtils::doCollideWithPiece(targetPos, _pieces[opponent], collisionIdx)){
		_pieces[opponent].erase(_pieces[opponent].begin() + collisionIdx);
	} else if(currentPiece->getPieceType() == PieceType::PAWN){
		if(BoardUtils::doCollideWithPawnEnPassant(targetPos, _pieces[opponent], collisionIdx )){
			_pieces[opponent].erase(_pieces[opponent].begin() + collisionIdx);
		}
	}

	if(currentPiece->getPieceType() == PieceType::ROOK){
		for(const auto& piece : _pieces[player]){
			if(piece->getPieceType() == PieceType::KING){
				const auto& king = static_cast<King*>(piece.get());
				if(currentPiece->getBoardPos().col == Defines::QUEEN_SIDE_ROOK){
					king->isQueenSideCastlePossible = false;
				} else {
					king->isKingSideCastlePossible = false;
				}			
			}
		}
	}

//	if(currPiece->getPieceType() == PieceType::ROOK){
//		for(const auto& piece : _pieces[player]){
//			if(piece->getPieceType() != PieceType::KING){
//				continue;
//			}
//			if(currPiece->getBoardPos().col == Defines::QUEEN_SIDE_ROOK){
//				static_cast<King*>(piece.get())->isQueenSideCastlePossible = false;
//				break;
//			} else {
//				static_cast<King*>(piece.get())->isKingSideCastlePossible = false;
//				break;
//			}
//		}
//	}

	if(currentPiece->getPieceType() == PieceType::KING){
	   	if(	const auto& distance = currentPiece->getBoardPos().col - targetPos.col;	//C++17 if initializer
			distance > 1 ){	//Queen side castle
				for(const auto& piece : _pieces[player]){
					if(	piece->getPieceType() == PieceType::ROOK 
						&& piece->getBoardPos().col == Defines::QUEEN_SIDE_ROOK){
							const auto& targetPosOfRook = BoardPos(targetPos.row, targetPos.col + 1);
							piece->setBoardPos(targetPosOfRook);
					}
				}
		} else if(distance < -1){ //King side castle
				for(const auto& piece : _pieces[player]){
					if(	piece->getPieceType() == PieceType::ROOK 
						&& piece->getBoardPos().col == Defines::KING_SIDE_ROOK){
							const auto& targetPosOfRook = BoardPos(targetPos.row, targetPos.col - 1);
							piece->setBoardPos(targetPosOfRook);
					}
				}
		}
	}

	currentPiece->setBoardPos(targetPos);
	removeCheck();

	_gameBoardProxy->onPieceUngrabbed();

	for( const auto& piece : _pieces[opponent] ){
		if(piece->getPieceType() == PieceType::PAWN){
			static_cast<Pawn*>(piece.get())->enPassantDanger = false;
		}
	}

	for(const auto& piece : _pieces[player]){
		if(!doAchieveCheck(piece)){
			continue;
		}
		setCheck();
		break;
	}

	finishTurn();

	for(const auto& piece : _pieces[opponent]){

		auto moveTile = piece->getMoveTiles(_pieces);

		if(moveTile.empty()){
			continue;
		}
		return;
	}

	checkMate(player);
}

int32_t PieceHandler::promotePiece(PieceType pieceType){
	auto playerId = BoardUtils::getOpponentId(getCurrPlayerId());

	if(EXIT_SUCCESS != PieceHandlerPopulator::promotePiece(pieceType,
														   playerId,
														   _selectedPieceId,
														   _pieces)){

		std::cerr << "Error! PieceHandlerPopulator::promotePiece() for pieceType "
				  << static_cast<int32_t>(pieceType) << " failed" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

BoardPos PieceHandler::getKingPos(const Defines::PlayerId& player) const {
	for(const auto& piece : _pieces[player]){
		if(piece->getPieceType() == PieceType::KING){
			return piece->getBoardPos();
		}
	}

	return BoardUtils::getBoardPos(Point::UNDEFINED);
}

bool PieceHandler::doAchieveCheck(const std::unique_ptr<ChessPiece>& piece) const {

	const auto& playerOnTurn = getCurrPlayerId();
	const auto& opponent = BoardUtils::getOpponentId(playerOnTurn);
	const auto& threatenedPieces = piece->getMoveTiles(_pieces);

	for(const auto& candidate : threatenedPieces){
		if(candidate.boardPos != getKingPos(opponent)){
			continue;
		}
		return true;
	}

	return false;
}

//void PieceHandler::setWidgetFlip(WidgetFlip flipType){
//	for(auto& playerPieces : _pieces){
//		for(auto& piece : playerPieces){
//			piece->setWidgetFlip(flipType);
//		}
//	}
//}


bool PieceHandler::isFreeBetweenKingAndRook(const Defines::RookDefines& rook) const {
	const auto& player = getCurrPlayerId();

	auto startRow = (player == Defines::WHITE_PLAYER_ID)
		? Defines::WHITE_PLAYER_START_ROW : Defines::BLACK_PLAYER_START_ROW;

	auto rookCol = (rook == Defines::QUEEN_SIDE_ROOK) ? 0 : 7;

	for(const auto& piece : _pieces[player]){
		if(piece->getBoardPos().row == startRow){
			if(rook == Defines::QUEEN_SIDE_ROOK){
				if(piece->getBoardPos().col > rookCol && piece->getBoardPos().col < KING_COL){
					return false;
				}
			} else {
				if(piece->getBoardPos().col < rookCol && piece->getBoardPos().col > KING_COL){
					return false;
				}
			}
		}
	}

	return true;
}

void PieceHandler::discoverCheckNearbyKing(King* &king) const {

	auto kingPos = king->getBoardPos();

	for(auto i = 0; i < 3; ++i){
		if(king->isDangerOfCheck(kingPos, _pieces)){
			king->isCheckOnTheLeft = true;
			break;
		}
		kingPos = BoardUtils::getAdjacentPos(Defines::LEFT, kingPos);
		king->isCheckOnTheLeft = false;
	}

	kingPos = king->getBoardPos();

	for(auto i = 0; i < 3; ++i){
		if(king->isDangerOfCheck(kingPos, _pieces)){
			king->isCheckOnTheRight = true;
			break;
		}
		kingPos = BoardUtils::getAdjacentPos(Defines::RIGHT, kingPos);
		king->isCheckOnTheRight = false;
	}

	return;
}









