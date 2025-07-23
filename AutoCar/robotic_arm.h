#ifndef _ROBOTIC_ARM_H
#define _ROBOTIC_ARM_H

#include <Servo.h>  // 包含舵机控制库

// 函数声明
void servoGrab(void);  // 控制机械臂夹取物品
void servoDrop(void);  // 控制机械臂放下物品

// 外部变量声明
extern Servo servo1;  // 声明底部舵机对象
extern Servo servo2;  // 声明顶部舵机对象

#endif
