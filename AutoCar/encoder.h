#ifndef _ENCODER_H
#define _ENCODER_H

#include "AutoCar_def.h"

// 函数声明
void getEncoderLeft(void);   // 获取左轮编码器值
void getEncoderRight(void);  // 获取右轮编码器值

// 外部变量声明
extern volatile long encoderValLeft;   // 左轮编码器计数
extern volatile long encoderValRight;  // 右轮编码器计数

#endif
