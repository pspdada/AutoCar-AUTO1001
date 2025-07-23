#ifndef _AUTOCAR_DEF_H
#define _AUTOCAR_DEF_H

#include <MsTimer2.h>  // 调用定时器库
#include <Servo.h>     // 调用舵机库
#include <math.h>

// 基础速度，用于调整小车的整体速度
#define base_V 16.0
// 定时器中断周期，单位：毫秒
#define PERIOD 10
// 圆周率
#define PI 3.14159

/*-------------------------------------引脚定义-------------------------------------*/
// 编码器引脚
#define ENCODER_LEFT_A 2   // 左轮电机编码器A相，中断引脚
#define ENCODER_LEFT_B 4   // 左轮电机编码器B相
#define ENCODER_RIGHT_A 3  // 右轮电机编码器A相，中断引脚
#define ENCODER_RIGHT_B 5  // 右轮电机编码器B相

// 电机驱动引脚
#define PWM_LEFT 9    // 左轮电机PWM控制引脚，用于调节电机速度
#define IN_L1 12      // 左轮电机方向控制引脚1
#define IN_L2 11      // 左轮电机方向控制引脚2
#define PWM_RIGHT 10  // 右轮电机PWM控制引脚，用于调节电机速度
#define IN_R1 6       // 右轮电机方向控制引脚1
#define IN_R2 8       // 右轮电机方向控制引脚2

// 红外寻迹模块引脚
#define CTRT_CNT 7      // 红外寻迹模块数量
#define CTRT_PIN_L3 30  // 左侧最外侧红外传感器
#define CTRT_PIN_L2 24  // 左侧第二个红外传感器
#define CTRT_PIN_L1 16  // 左侧第三个红外传感器
#define CTRT_PIN_M 17   // 中间红外传感器
#define CTRT_PIN_R1 18  // 右侧第三个红外传感器
#define CTRT_PIN_R2 19  // 右侧第二个红外传感器
#define CTRT_PIN_R3 20  // 右侧最外侧红外传感器

// 舵机引脚
#define SERVO_CNT 2  // 舵机数量
#define SERVO_1 13   // 底部舵机，控制机械臂上下运动
#define SERVO_2 7    // 顶部舵机，控制夹爪开合

// 测距模块引脚
#define TRIG_PIN 26  // 测距模块Trig引脚，触发信号输入
#define ECHO_PIN 28  // 测距模块Echo引脚，回响信号输出

// 按键引脚
#define BUTTON_PIN 21  // 按钮引脚，用于启动/停止小车

/*---------------------------------PID参数-------------------------------*/
// 左轮PID参数
#define Kp_L 10.0  // 比例增益
#define Ki_L 20.0  // 积分增益
#define Kd_L 0.05  // 微分增益

// 右轮PID参数
#define Kp_R 10.0  // 比例增益
#define Ki_R 20.0  // 积分增益
#define Kd_R 0.05  // 微分增益

// 红外传感器记忆层数
#define MEMORY_CNT 4

/*---------------------------------数据类型定义------------------------------*/
// 运行模式枚举
typedef enum {
    _STOP = 0,          // 停转
    SLOW_ON,            // 低速前进
    STRAIGHT_ON,        // 全速直行
    TURN_LEFT_LOW,      // 低速左转
    TURN_LEFT_MID,      // 中速左转
    TURN_LEFT_HIGH,     // 高速左转
    TURN_LEFT_HIGH_F,   // 快速左转
    TURN_RIGHT_LOW,     // 低速右转
    TURN_RIGHT_MID,     // 中速右转
    TURN_RIGHT_HIGH,    // 高速右转
    TURN_RIGHT_HIGH_F,  // 快速右转
    REVERSE,            // 倒车
    CIRCLE              // 转圈
} run_mode;

#endif
