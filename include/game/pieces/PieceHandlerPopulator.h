#ifndef INCLUDE_GAME_PIECES_PIECEHANDLERPOPULATOR_H_
#define INCLUDE_GAME_PIECES_PIECEHANDLERPOPULATOR_H_
//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "game/pieces/types/ChessPiece.h"

//Forward declaration
struct InputEvent;

class PieceHandlerPopulator {
public:
	PieceHandlerPopulator() = delete;
	virtual ~PieceHandlerPopulator() = default;

	static int32_t populatePieceHandler(int32_t whitePiecesRsrcId,
										int32_t blackPiecesRsrcId,
										int32_t unfinishedPieceTextId,
										std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &outPieces);

	static int32_t promotePiece(PieceType pieceType,
								int32_t playerId,
								int32_t oldPieceId,
								std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &outPieces );
};

#endif /* INCLUDE_GAME_PIECES_PIECEHANDLERPOPULATOR_H_ */
