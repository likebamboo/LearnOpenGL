//
// Created by 李文涛 on 2024/1/27.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "GL/glew.h"

#ifdef _MSC_VER
#define DEBUG_BREAK __debugbreak()
#else
#define DEBUG_BREAK {}
#endif

#define glAsset(x) if (!(x)) DEBUG_BREAK

#define glCall(x) {\
glClearError();\
x;\
glAsset(glLogCall(#x, __FILE__, __LINE__));\
}

/**
 * \brief 清理错误
 */
void glClearError();

/**
 * \brief 检查错误
 */
bool glLogCall(const char *function, const char *file, int line);


#endif //RENDERER_H
