// Corresponding Header
#include "game/pieces/types/UnfinishedPiece.h"

// C system includes

// C++ system includes


// Third party includes

// Own includes
#include "game/utils/BoardUtils.h"

int32_t UnfinishedPiece::init(const ChessPieceCfg& cfg){
	if(EXIT_SUCCESS != ChessPiece::init(cfg)){
		std::cerr << "ChessPiece::init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	const auto pieceAbsPos = BoardUtils::getAbsPos(_boardPos);
	_notReadyText.create("!", cfg.unfinishedPieceTextId, Colors::RED, pieceAbsPos);

	return EXIT_SUCCESS;
}

void UnfinishedPiece::draw() const {
	ChessPiece::draw();
	_notReadyText.draw();
}

void UnfinishedPiece::setBoardPos(const BoardPos& boardPos) {
	ChessPiece::setBoardPos(boardPos);

	const auto pieceAbsPos = BoardUtils::getAbsPos(_boardPos);
	_notReadyText.setPosition(pieceAbsPos);
}

std::vector<TileData> UnfinishedPiece::getMoveTiles(
		[[maybe_unused]]const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const {


	return std::vector<TileData> { };
}






