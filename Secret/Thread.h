#pragma once

#include <mutex>

extern std::mutex RenderThreadInitLock;
extern bool IsRenderThreadStart;

void	threadRender();