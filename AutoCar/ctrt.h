#ifndef _CTRT_H
#define _CTRT_H

#include "AutoCar_def.h"

// 函数声明
void updateCTRTState(void);  // 更新红外传感器状态
bool isAllLow(void);         // 判断是否所有传感器都为低电平
bool isAllHigh(void);        // 判断是否所有传感器都为高电平

// 外部变量声明
extern bool CTRTState[CTRT_CNT][MEMORY_CNT];  // 红外传感器状态数组

#endif
