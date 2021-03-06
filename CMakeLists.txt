cmake_minimum_required(VERSION 3.5.1)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
	${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)

project(chess LANGUAGES CXX)

find_package(SDL2 REQUIRED)

if(UNIX)
	find_package(SDL2_image REQUIRED)
	find_package(SDL2_ttf REQUIRED)
	find_package(SDL2_mixer REQUIRED)
elseif(WIN32 OR APPLE)
	find_package(SDL2_IMAGE REQUIRED)
	find_package(SDL2_TTF REQUIRED)
	find_package(SDL2_MIXER REQUIRED)
endif()

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_INC_DIR ${_BASE_DIR}/include)
set(_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} 
					${_INC_DIR}/common/CommonDefines.h
										
					${_INC_DIR}/engine/Engine.h
					${_INC_DIR}/engine/config/EngineConfig.h
					${_INC_DIR}/engine/EngineConfigLoader.h
					${_INC_DIR}/game/Game.h
					${_INC_DIR}/game/config/GameCfg.h
					${_INC_DIR}/game/board/GameBoard.h
					${_INC_DIR}/game/board/MoveSelector.h
#					${_INC_DIR}/game/board/GameBoardAnimator.h
					${_INC_DIR}/game/utils/BoardPos.h
					${_INC_DIR}/game/utils/BoardUtils.h
					${_INC_DIR}/game/defines/ChessDefines.h
					${_INC_DIR}/game/defines/ChessStructs.h
					${_INC_DIR}/game/pieces/types/ChessPiece.h
					${_INC_DIR}/game/pieces/types/Queen.h
					${_INC_DIR}/game/pieces/types/Rook.h
					${_INC_DIR}/game/pieces/types/Pawn.h
					${_INC_DIR}/game/pieces/types/Bishop.h
					${_INC_DIR}/game/pieces/types/Knight.h
					${_INC_DIR}/game/pieces/types/King.h
#					${_INC_DIR}/game/pieces/types/UnfinishedPiece.h
					${_INC_DIR}/game/pieces/PieceHandler.h
					${_INC_DIR}/game/pieces/PieceHandlerPopulator.h
					${_INC_DIR}/game/proxies/GameBoardProxy.h
					${_INC_DIR}/game/logic/GameLogic.h
#					${_INC_DIR}/game/logic/InputInverter.h
					${_INC_DIR}/game/proxies/GameProxy.h
					${_INC_DIR}/game/panels/PiecePromotionPanel.h
					${_INC_DIR}/game/panels/buttons/PiecePromotionButton.h
					${_INC_DIR}/game/panels/config/PiecePromotionPanelCfg.h
					${_INC_DIR}/game/panels/config/PiecePromotionButtonCfg.h
					${_INC_DIR}/game/panels/ManagementConsole.h
					
					${_SRC_DIR}/engine/Engine.cpp
					${_SRC_DIR}/engine/EngineConfigLoader.cpp
					${_SRC_DIR}/game/Game.cpp
					${_SRC_DIR}/game/board/GameBoard.cpp
					${_SRC_DIR}/game/board/MoveSelector.cpp
#					${_SRC_DIR}/game/board/GameBoardAnimator.cpp	
					${_SRC_DIR}/game/utils/BoardUtils.cpp
					${_SRC_DIR}/game/pieces/types/ChessPiece.cpp
					${_SRC_DIR}/game/pieces/types/Queen.cpp
					${_SRC_DIR}/game/pieces/types/Rook.cpp
					${_SRC_DIR}/game/pieces/types/Pawn.cpp
					${_SRC_DIR}/game/pieces/types/Bishop.cpp
					${_SRC_DIR}/game/pieces/types/Knight.cpp
					${_SRC_DIR}/game/pieces/types/King.cpp
#					${_SRC_DIR}/game/pieces/types/UnfinishedPiece.cpp
					${_SRC_DIR}/game/pieces/PieceHandler.cpp
					${_SRC_DIR}/game/pieces/PieceHandlerPopulator.cpp
					${_SRC_DIR}/game/logic/GameLogic.cpp
#					${_SRC_DIR}/game/logic/InputInverter.cpp
					${_SRC_DIR}/game/panels/PiecePromotionPanel.cpp
					${_SRC_DIR}/game/panels/buttons/PiecePromotionButton.cpp
					${_SRC_DIR}/game/panels/ManagementConsole.cpp
	
					${_SRC_DIR}/main.cpp
			   )

set_target_cpp_standard(${PROJECT_NAME} 17)
enable_target_warnings(${PROJECT_NAME})

target_include_directories(
	${PROJECT_NAME} 
		PRIVATE 
			${_INC_DIR}
	)
	
target_link_libraries(
	${PROJECT_NAME}
		PRIVATE
			manager_utils
	)	
	
add_subdirectory(utils)
add_subdirectory(sdl_utils)
add_subdirectory(manager_utils)



	