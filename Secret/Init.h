#pragma once

//初始化OpenGL窗体
bool initGLWindow(int, int, bool);

//初始化线程
bool initThread(int, char*[]);

//加载shader
void initShader();

//初始化Callback
void initCallback();