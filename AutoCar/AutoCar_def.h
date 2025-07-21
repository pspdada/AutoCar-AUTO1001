#ifndef _AUTOCAR_DEF_H
#define _AUTOCAR_DEF_H

#include <MsTimer2.h>  // 调用定时器库
#include <Servo.h>     // 调用Servo.h库
#include <math.h>

#define base_V 16.0  // 基础速度，实力的象征
#define PERIOD 10    // 周期
#define PI 3.14159

/*-------------------------------------管脚-------------------------------------*/
#define ENCODER_LEFT_A 2  // 左轮电机的编码器A项接Arduino的2中断口，用于编码器计数
#define ENCODER_LEFT_B 4
#define ENCODER_RIGHT_A 3  // 右轮电机的编码器A项接Arduino的3中断口，用于编码器计数
#define ENCODER_RIGHT_B 5
#define PWM_LEFT 9  // 用于左轮电机的PWM输出，调节电机速度
#define IN_L1 12    // 11、12引脚用于左轮电机的转动方向控制
#define IN_L2 11
#define PWM_RIGHT 10  // 用于右轮电机的PWM输出，调节电机速度
#define IN_R1 6       // 6和8引脚用于右轮电机的转动方向控制
#define IN_R2 8

// 7个光电寻迹模块
#define CTRT_CNT 7
#define CTRT_PIN_L3 30  // 左红外
#define CTRT_PIN_L2 24
#define CTRT_PIN_L1 16
#define CTRT_PIN_M 17   // 中红外
#define CTRT_PIN_R1 18  // 右红外
#define CTRT_PIN_R2 19
#define CTRT_PIN_R3 20

// 2个舵机
// 由于机械原因，机械臂的参数可能会变，需要及时调整
#define SERVO_CNT 2
#define SERVO_1 13  // 底部舵机 可用范围：1500-2500 增大时向后放倒，1500初始竖直位置，2500水平位置
#define SERVO_2 7   // 顶部舵机 可用范围：1000-1500 增大时夹紧，1000初始位置，1500夹紧位置

// 测距模块
#define TRIG_PIN 26  // 引脚Trig触发控制信号输入
#define ECHO_PIN 28  // 引脚Echo回响信号输出

#define BUTTON_PIN 21  // 按钮，按下为LOW，松开为HIGH

/*---------------------------------定义常值-------------------------------*/
// PID参数
#define Kp_L 10.0
#define Ki_L 20.0
#define Kd_L 0.05
#define Kp_R 10.0
#define Ki_R 20.0
#define Kd_R 0.05

#define MEMORY_CNT 4  // CTRT的记忆层数

/*---------------------------------数据类型------------------------------*/
typedef enum run_mode_e {
    _STOP = 0,         // 停转
    SLOW_ON,           // 低速前进
    STRAIGHT_ON,       // 全速直行
    TURN_LEFT_LOW,     // 低左转
    TURN_LEFT_MID,     // 中左转
    TURN_LEFT_HIGH,    // 直角左转
    TURN_LEFT_HIGH_F,  // 直角左转_快速
    TURN_RIGHT_LOW,
    TURN_RIGHT_MID,
    TURN_RIGHT_HIGH,
    TURN_RIGHT_HIGH_F,
    REVERSE,  // 倒车
    CIRCLE    // 转圈
} run_mode;

// 判断是否需要直角转弯
enum quarter_turn_e {
    NOPE = 0,
    QT_L,  // 直角左转
    QT_R,  // 直角右转
};

#endif
