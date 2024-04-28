#ifndef INIT_H
#define INIT_H

#include <common.h>
/* 初始化时的读入。 */
void init_read();

/* 每一帧的读入；返回：是否跳帧。 */
bool frame_read(int nowFrame);

#endif
