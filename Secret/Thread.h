#pragma once

#include <mutex>

extern std::mutex RenderThreadInitLock;
extern bool IsRenderThreadStart;

void	threadRender(int Width, int Height, bool FullScreen);
void	threadCallback();