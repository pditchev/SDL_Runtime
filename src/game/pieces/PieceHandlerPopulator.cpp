// Corresponding Header
#include "game/pieces/PieceHandlerPopulator.h"

// C system includes

// C++ system includes
#include <variant>

// Third party includes

// Own includes
#include "game/pieces/types/Rook.h"
#include "game/pieces/types/Pawn.h"
#include "game/pieces/types/Bishop.h"
#include "game/pieces/types/Queen.h"
#include "game/pieces/types/Knight.h"
#include "game/pieces/types/King.h"
//my:
#include "common/CommonDefines.h"

//Forward Declarations

namespace {
constexpr auto STARTING_PIECES_COUNT = 16;
constexpr auto PAWNS_COUNT = 8;
constexpr auto WHITE_PLAYER_START_PAWN_ROW = 6;
constexpr auto BLACK_PLAYER_START_PAWN_ROW = 1;

std::unique_ptr<ChessPiece> createPiece(PieceType pieceType){
	switch(pieceType){
	case PieceType::QUEEN:
		return std::make_unique<Queen>();
		break;
	case PieceType::ROOK:
		return std::make_unique<Rook>();
		break;
	case PieceType::PAWN:
		return std::make_unique<Pawn>();
		break;
	case PieceType::BISHOP:
		return std::make_unique<Bishop>();
		break;
	case PieceType::KNIGHT:
		return std::make_unique<Knight>();
		break;
	case PieceType::KING:
		return std::make_unique<King>();
		break;
	default:
		std::cerr << "Error! Received unknown pieceType: " << static_cast<int32_t>(pieceType) << std::endl;
		break;
	}

	return nullptr;
}

int32_t populateWhitePieces(//[[maybe_unused]]GameProxy* gameProxy,
							int32_t rsrcId,
							int32_t unfinishedPieceTextId,
							ChessPiece::PlayerPieces& whites){

	whites.reserve(STARTING_PIECES_COUNT);

	ChessPieceCfg _pieceCfg;
	_pieceCfg._boardPos.row = WHITE_PLAYER_START_PAWN_ROW;
	_pieceCfg._playerId = Defines::WHITE_PLAYER_ID;
	_pieceCfg.rsrcId = rsrcId;
	_pieceCfg._pieceType = PieceType::PAWN;
	_pieceCfg.unfinishedPieceTextId = unfinishedPieceTextId;

	for(auto i = 0; i < PAWNS_COUNT; ++i){
		whites.push_back(createPiece(_pieceCfg._pieceType));

		_pieceCfg._boardPos.col = i;
		if(EXIT_SUCCESS != whites[i]->init(_pieceCfg)){
			std::cerr << "Error! _piece.init() failed" << std::endl;
			return EXIT_FAILURE;
		}
	}

	constexpr auto nonPawnsCount = PAWNS_COUNT;
	constexpr PieceType nonPawnsTypes[nonPawnsCount] = {
			PieceType::ROOK,
			PieceType::KNIGHT,
			PieceType::BISHOP,
			PieceType::QUEEN,
			PieceType::KING,
			PieceType::BISHOP,
			PieceType::KNIGHT,
			PieceType::ROOK
	};

	_pieceCfg._boardPos.row = WHITE_PLAYER_START_PAWN_ROW + 1;
	for(auto i = PAWNS_COUNT; i < STARTING_PIECES_COUNT; ++i){
		_pieceCfg._boardPos.col = i - PAWNS_COUNT;
		_pieceCfg._pieceType = nonPawnsTypes[i - PAWNS_COUNT];

		whites.push_back(createPiece(_pieceCfg._pieceType));

		if(EXIT_SUCCESS != whites[i]->init(_pieceCfg)){
			std::cerr << "Error! _piece.init() failed" << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

int32_t populateBlackPieces(int32_t rsrcId,
							int32_t unfinishedPieceTextId,
							ChessPiece::PlayerPieces& blacks){

	blacks.reserve(STARTING_PIECES_COUNT);

	ChessPieceCfg _pieceCfg;
	_pieceCfg._boardPos.row = BLACK_PLAYER_START_PAWN_ROW;
	_pieceCfg._playerId = Defines::BLACK_PLAYER_ID;
	_pieceCfg.rsrcId = rsrcId;
	_pieceCfg._pieceType = PieceType::PAWN;
	_pieceCfg.unfinishedPieceTextId = unfinishedPieceTextId;

	for(auto i = 0; i < PAWNS_COUNT; ++i){
		blacks.push_back(createPiece(_pieceCfg._pieceType));

		_pieceCfg._boardPos.col = i;
		if(EXIT_SUCCESS != blacks[i]->init(_pieceCfg)){
			std::cerr << "Error! _piece.init() failed" << std::endl;
			return EXIT_FAILURE;
		}
	}

	constexpr auto nonPawnsCount = PAWNS_COUNT;
	constexpr PieceType nonPawnsTypes[nonPawnsCount] = {
			PieceType::ROOK,
			PieceType::KNIGHT,
			PieceType::BISHOP,
			PieceType::QUEEN,
			PieceType::KING,
			PieceType::BISHOP,
			PieceType::KNIGHT,
			PieceType::ROOK
	};

	_pieceCfg._boardPos.row = BLACK_PLAYER_START_PAWN_ROW - 1;
	for(auto i = PAWNS_COUNT; i < STARTING_PIECES_COUNT; ++i){
		_pieceCfg._boardPos.col = i - PAWNS_COUNT;
		_pieceCfg._pieceType = nonPawnsTypes[i - PAWNS_COUNT];

		blacks.push_back(createPiece(_pieceCfg._pieceType));

		if(EXIT_SUCCESS != blacks[i]->init(_pieceCfg)){
			std::cerr << "Error! _piece.init() failed" << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

} //end of namespace


int32_t PieceHandlerPopulator::populatePieceHandler(int32_t whitePiecesRsrcId,
													int32_t blackPiecesRsrcId,
													int32_t unfinishedPieceTextId,
													std::array<ChessPiece::PlayerPieces,
															Defines::PLAYERS_COUNT> &outPieces){

	ChessPiece::PlayerPieces& whites = outPieces[Defines::WHITE_PLAYER_ID];
	if(EXIT_SUCCESS != populateWhitePieces(whitePiecesRsrcId,
										   unfinishedPieceTextId,
										   whites)){
		std::cerr << "Error, populateWhitePieces() for rsrcId: " << whitePiecesRsrcId << " failed" << std::endl;
		return EXIT_FAILURE;
	}

	ChessPiece::PlayerPieces& blacks = outPieces[Defines::BLACK_PLAYER_ID];
	if(EXIT_SUCCESS != populateBlackPieces(blackPiecesRsrcId,
										   unfinishedPieceTextId,
										   blacks)){
		std::cerr << "Error, populateBlackPieces() for rsrcId: " << blackPiecesRsrcId << " failed" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t PieceHandlerPopulator::promotePiece(PieceType pieceType,
											int32_t playerId,
											int32_t oldPieceId,
											std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &outPieces ) {

	auto rsrcId = (playerId == Defines::WHITE_PLAYER_ID) ?
			TextureId::WHITE_PIECES : TextureId::BLACK_PIECES;

	ChessPieceCfg _pieceCfg;
	_pieceCfg._boardPos = outPieces[playerId][oldPieceId]->getBoardPos();
	_pieceCfg._playerId = playerId;
	_pieceCfg.rsrcId = rsrcId;
	_pieceCfg._pieceType = pieceType;
	_pieceCfg.unfinishedPieceTextId = FontId::ANGELINE_VINTAGE_40;

	outPieces[playerId][oldPieceId] = createPiece(pieceType);

	if(EXIT_SUCCESS != outPieces[playerId][oldPieceId]->init(_pieceCfg)){
		std::cerr << "Error! _piece[" << playerId << "][" << oldPieceId << "]->init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}












