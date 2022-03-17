#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGR_H_

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "manager_utils/managers/MgrBase.h"
#include "sdl_utils/Renderer.h"
#include "sdl_utils/MonitorWindow.h"

//Own includes

//Forward declaration
struct DrawMgrCfg;

class DrawMgr: public MgrBase {
public:
	DrawMgr() = default;

	DrawMgr(const DrawMgr& other)= delete;
	DrawMgr(DrawMgr&& other) = delete;
	DrawMgr& operator=(const DrawMgr& other) = delete;
	DrawMgr& operator=(DrawMgr&& other) = delete;

	int32_t init(const DrawMgrCfg& cfg);

	void deinit() final;
	void process() final;

	void clearScreen();

	void finishFrame();

	void addDrawCmd(const DrawParams &drawParams) const;

	void setWidgetBlendMode(const DrawParams &drawParams, BlendMode blendMode);

	void setWidgetOpacity(const DrawParams &drawParams, int32_t opacity);

	int64_t getMaxFrameRate() const;

private:
  SDL_Texture* getTextureInternal(const DrawParams &drawParams) const;

  Renderer _renderer;

  MonitorWindow _window;

  //Hold maximum frame rate cap
  int64_t _maxFrames { 0 };
};

extern DrawMgr *gDrawMgr;

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_DRAWMGR_H_ */
