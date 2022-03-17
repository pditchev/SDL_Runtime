#ifndef INCLUDE_GAME_PIECES_PIECEHANDLER_H_
#define INCLUDE_GAME_PIECES_PIECEHANDLER_H_
//C system headers

//C++ system headers
#include <cstdint>
#include <vector>
#include <array>
#include <memory>
#include <functional>

//Other libraries headers

//Own components headers
#include "game/pieces/PieceHandlerPopulator.h"

//Forward declaration
struct GameBoardProxy;
struct King;

class PieceHandler {
public:
	int32_t init(GameBoardProxy* gameBoardProxy,
				 int32_t whitePiecesRsrcId,
				 int32_t blackPiecesRsrcId,
				 int32_t unfinishedPieceTextId);

	void draw() const;
	void handleEvent(const InputEvent& e);

	int32_t promotePiece(PieceType pieceType);

	//my::
	std::function<Defines::PlayerId()> getCurrPlayerId;
	std::function<void()> finishTurn;
	std::function<void()> setCheck;
	std::function<void()> removeCheck;
	std::function<void(const Defines::PlayerId&)> checkMate;

//	void setWidgetFlip(WidgetFlip flipType);

	std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> _pieces; //set public to be able to reduce pawn Promotion

private:
	void handlePieceGrabbedEvent(const InputEvent& e);
	void handlePieceUngrabbedEvent(const InputEvent& e);
	void doMovePiece(const BoardPos& boardPos);

	//my
	bool doAchieveCheck(const std::unique_ptr<ChessPiece> &piece) const;

	bool isFreeBetweenKingAndRook(const Defines::RookDefines& rook) const;

	void discoverCheckNearbyKing(King* &piece) const;

	BoardPos getKingPos(const Defines::PlayerId& player) const;

	GameBoardProxy* _gameBoardProxy = nullptr;

	int32_t _selectedPieceId = 0;

	bool _isPieceGrabbed = false;
};

#endif /* INCLUDE_GAME_PIECES_PIECEHANDLER_H_ */
