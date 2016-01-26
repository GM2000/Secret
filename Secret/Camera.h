#pragma once

#include <mutex>
#include "Location.h"

namespace camera
{
	//ˢ��Uniform
	void refreshUniform();

	//����ע�⣡ÿ���޸�����ʱ����Ҫ����
	extern std::mutex CameraLock;

	extern double Speed;

	extern float XRot;
	extern float YRot;

	extern location Loc;

	extern bool HasChange;
}