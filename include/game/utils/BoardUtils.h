#ifndef INCLUDE_GAME_UTILS_BOARDUTILS_H_
#define INCLUDE_GAME_UTILS_BOARDUTILS_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "game/utils/BoardPos.h"
#include "utils/drawing/Point.h"
#include "game/defines/ChessDefines.h"
#include "game/pieces/types/ChessPiece.h"

//Forward declaration

class BoardUtils {
public:
	static BoardPos getBoardPos(const Point& absPos);
	static Point getAbsPos(const BoardPos& boardPos);
	static bool isInsideBoard(const BoardPos& boardPos);
	static bool isInsideBoard(const Point& absPos);

	static Defines::PlayerId getOpponentId(int32_t activePlayerId);
	static BoardPos getAdjacentPos(Defines::Direction dir, const BoardPos &currPos);
	static BoardPos getKnightAdjPos(Defines::KnightDirections, const BoardPos &currPos);
	static bool doCollideWithPiece(const BoardPos &selectedPos,
								   const ChessPiece::PlayerPieces &pieces,
								   int32_t& outCollisionRelativeId);

	static bool doCollideWithPawnEnPassant(const BoardPos &selectedPos,
							        const ChessPiece::PlayerPieces &pieces,
								    int32_t& outCollisionRelativeId);
	static TileType getTileType(const BoardPos &boardPos,
								const ChessPiece::PlayerPieces &playerPieces,
								const ChessPiece::PlayerPieces &enemyPieces);
};

#endif /* INCLUDE_GAME_UTILS_BOARDUTILS_H_ */
