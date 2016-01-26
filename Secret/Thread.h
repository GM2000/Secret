#pragma once

#include <mutex>

extern std::mutex RenderThreadInitLock;
extern bool IsRenderThreadStart;

void threadRefresh();
void threadRender(int Width, int Height, bool FullScreen);