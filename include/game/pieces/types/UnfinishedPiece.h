#ifndef INCLUDE_GAME_PIECES_TYPES_UNFINISHEDPIECE_H_
#define INCLUDE_GAME_PIECES_TYPES_UNFINISHEDPIECE_H_
//C system headers

//C++ system headers
#include <iostream>
#include <array>

//Other libraries headers

//Own components headers
#include "game/pieces/types/ChessPiece.h"
#include "manager_utils/drawing/Text.h"

//Forward declaration

class UnfinishedPiece : public ChessPiece {
private:
	Text _notReadyText;
	void setBoardPos(const BoardPos& boardPos) final;

public:
	void draw() const final;

	int32_t init(const ChessPieceCfg& cfg) final;

	std::vector<TileData> getMoveTiles(
			const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const final;
};

#endif /* INCLUDE_GAME_PIECES_TYPES_UNFINISHEDPIECE_H_ */
