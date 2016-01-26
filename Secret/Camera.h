#pragma once

#include <mutex>
#include "Location.h"

namespace camera
{
	//刷新Uniform
	void refreshUniform();

	//锁，注意！每次修改数据时都需要上锁
	extern std::mutex CameraLock;

	extern double Speed;

	extern float XRot;
	extern float YRot;

	extern location Loc;

	extern bool HasChange;
}