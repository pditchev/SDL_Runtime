#ifndef INCLUDE_GAME_PROXIES_GAMEPROXY_H_
#define INCLUDE_GAME_PROXIES_GAMEPROXY_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers

//Forward declaration

class GameProxy {
public:
	virtual ~GameProxy() = default;

//	virtual void onGameTurnFinished() = 0;

//	virtual void onPawnPromotion() = 0;

//	virtual void promotePiece(PieceType pieceTye) = 0;

	//my ...
//	virtual int32_t getCurrPlayerId() const = 0;

	virtual void onBoardAnimFinished() = 0;

	virtual void setWidgetFlip(WidgetFlip flipType) = 0;

};



#endif /* INCLUDE_GAME_PROXIES_GAMEPROXY_H_ */
