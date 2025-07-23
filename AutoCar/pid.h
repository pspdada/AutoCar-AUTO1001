#ifndef _PID_H
#define _PID_H

// 函数声明
short pidControllerLeft(float TARGET_V, float cur_V);   // 左轮PID控制器
short pidControllerRight(float TARGET_V, float cur_V);  // 右轮PID控制器

#endif