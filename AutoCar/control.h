#ifndef _CONTROL_H
#define _CONTROL_H

#include "AutoCar_def.h"
#include "ctrt.h"

// 函数声明
RunMode runMode(void);    // 根据传感器信息确定运行模式
void motorControl(void);  // 电机控制，设置目标速度
void carRun(void);        // 驱动小车，控制电机
void buttonPress(void);   // 按键中断函数

#endif