#ifndef INCLUDE_GAME_PIECES_TYPES_PAWN_H_
#define INCLUDE_GAME_PIECES_TYPES_PAWN_H_
//C system headers

//C++ system headers
//#include <unordered_map>
//#include <array>
//#include <functional>

//Other libraries headers

//Own components headers
#include "game/pieces/types/ChessPiece.h"


//Forward declaration

class Pawn : public ChessPiece {
public:
	int32_t init(const ChessPieceCfg& cfg) final;

	std::vector<TileData> getMoveTiles(
				const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces,
				const bool firstCall = true) const final;

	void setBoardPos(const BoardPos& boardPos) final;

	int32_t getInitialRow() const;
	Defines::Direction getMoveDir() const;

	std::function<void(int32_t)> selfPromotion;

	bool enPassantDanger = false;

	BoardPos getBoardPosBack() const;

	mutable bool isPromotionAllowed = true;

private:

	int32_t _INITIAL_ROW;
	int32_t _BACKWARDS_ROW;

	Defines::Direction _MOVE_DIRECTION;
	int32_t _END_ROW;
	static const size_t allowedNumOfDirs = 3;
	std::array<Defines::Direction, allowedNumOfDirs> _DIRS;

	std::unordered_map<Defines::Direction, MoveDirection> getBoardMoves() const;
};

#endif /* INCLUDE_GAME_PIECES_TYPES_PAWN_H_ */
