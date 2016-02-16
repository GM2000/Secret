#pragma once

#include <mutex>

extern bool IsRenderThreadStart;

void threadRefresh();
void threadRender(int Width, int Height, bool FullScreen);
void threadChunkRefresher();