#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MGRBASE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MGRBASE_H_

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers

//Own includes

//#include "drawing/DrawParams.h"

//Forward declaration
enum {
	DRAW_MGR_IDX,
	RSRC_MGR_IDX,
	TIMER_MGR_IDX,
	MANAGERS_COUNT
};

class MgrBase {
public:
  MgrBase() = default;
  virtual ~MgrBase() = default;

  MgrBase(const MgrBase& other)= delete;
  MgrBase(MgrBase&& other) = delete;
  MgrBase& operator=(const MgrBase& other) = delete;
  MgrBase& operator=(MgrBase&& other) = delete;

  virtual void deinit() = 0;
  virtual void process() = 0;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MGRBASE_H_ */
