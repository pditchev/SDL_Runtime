#ifndef INCLUDE_GAME_PIECES_TYPES_CHESSPIECE_H_
#define INCLUDE_GAME_PIECES_TYPES_CHESSPIECE_H_
//C system headers

//C++ system headers
#include <array>
#include <unordered_map>
#include <memory>
#include <functional>

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Image.h"
#include "game/utils/BoardPos.h"
#include "game/defines/ChessDefines.h"
#include "game/defines/ChessStructs.h"

//Forward declaration
struct InputEvent;

struct ChessPieceCfg{
	BoardPos _boardPos {};
	int32_t _playerId {};
	PieceType _pieceType = PieceType::UNKNOWN;
	int32_t rsrcId = INVALID_RSRC_ID;

	int32_t unfinishedPieceTextId;
};

class ChessPiece {
public:
	using PlayerPieces = std::vector<std::unique_ptr<ChessPiece>>;

	virtual ~ChessPiece() = default;
	virtual int32_t init(const ChessPieceCfg& cfg);
	virtual void draw() const;
	bool containsEvent(const InputEvent& e) const;

	virtual std::vector<TileData> getMoveTiles(
			const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces,
			const bool firstCall = true) const;

	virtual void setBoardPos(const BoardPos& boardPos, const bool derived = false);

	BoardPos getBoardPos() const;

	int32_t getPlayerId() const;

	PieceType getPieceType() const;

//	void setWidgetFlip(WidgetFlip flipType);

	std::function<bool()> isCurrPlayerInCheck;

	bool isDangerOfCheck(const BoardPos& boardPos,
			const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const;

protected:

	Image _pieceImg;
	BoardPos _boardPos;
	Defines::PlayerId _playerId;
	PieceType _pieceType;


private:
	virtual std::unordered_map<Defines::Direction, MoveDirection> getBoardMoves() const = 0;

	BoardPos getKingPos( const ChessPiece::PlayerPieces& pieces) const;
};

#endif /* INCLUDE_GAME_PIECES_TYPES_CHESSPIECE_H_ */
