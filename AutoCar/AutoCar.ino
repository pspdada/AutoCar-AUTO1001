#include "AutoCar_def.h"
//------------------------------------------全局变量--------------------------------------------*/
float TARGET_V_LEFT = 0, f_V_L = 0, ff_V_L = 0;   // 左轮目标速度 当前、上一时刻、上上时刻
float TARGET_V_RIGHT = 0, f_V_R = 0, ff_V_R = 0;  // 右轮目标速度 当前、上一时刻、上上时刻
volatile long encoderVal_LEFT = 0;                // 左轮编码器值
volatile long encoderVal_RIGHT = 0;               // 右轮编码器值
float cur_V_LEFT = 0;                             // 左轮实际转速
float cur_V_RIGHT = 0;                            // 右轮实际转速
short T = PERIOD;                                 // 周期
short Output_R = 0, Output_L = 0;
// pid输出量u、偏差e(k)、e(k-1)、e(k-2)
float u_L = 0, LEFT_eI = 0, LEFT_eII = 0, LEFT_eIII = 0;     // 左轮
float u_R = 0, RIGHT_eI = 0, RIGHT_eII = 0, RIGHT_eIII = 0;  // 右轮

float temp_time, distance;                      // 超声波模块读出来的距离
unsigned long time_base_l = 0, time_now_l = 0;  // LOOP用于loop循环的时间
unsigned long time_base_a = 0, time_now_a = 0;  // AVOID用于避障功能的时间，find表示发现障碍物的时间，end表示执行完避障的时间
unsigned long time_base_f = 0, time_now_f = 0;  // FINISH用于完成寻迹的时间

// 将CTRT读取的数据存入二维数组中，实现记忆功能
bool CTRTstate[CTRT_CNT][MEMORY_CNT];

bool isCross = 0;                // 判断是否越线，0代表没有越界，正常读取正常输出，1代表越界，进入记忆模式
bool isFinish = 0;               // 判断是否到达终点，0代表没有到达终点，正常寻迹，1代表到达终点
bool isBarrier = 0;              // 判断是否遇到障碍物
bool nowDrop = 0;                // 现在放下东西
volatile char quarter_turn = 0;  // 在记忆模式下判断是否需要直角转弯
volatile bool car_state = 1;     // 按下按钮后改变车的状态

// 创建舵机对象
Servo servo_1;
Servo servo_2;

// 存储舵机角度位置，1底部 2顶部
unsigned short PWM_1 = 1500, PWM_2 = 1000;

// 定义引脚
void pinModeInit() {
    pinMode(ENCODER_LEFT_A, INPUT);
    pinMode(ENCODER_LEFT_B, INPUT);
    pinMode(ENCODER_RIGHT_A, INPUT);
    pinMode(ENCODER_RIGHT_B, INPUT);
    pinMode(PWM_LEFT, OUTPUT);
    pinMode(IN_L1, OUTPUT);
    pinMode(IN_L2, OUTPUT);
    pinMode(PWM_RIGHT, OUTPUT);
    pinMode(IN_R1, OUTPUT);
    pinMode(IN_R2, OUTPUT);
    pinMode(CTRT_PIN_R1, INPUT);
    pinMode(CTRT_PIN_R2, INPUT);
    pinMode(CTRT_PIN_R3, INPUT);
    pinMode(CTRT_PIN_L1, INPUT);
    pinMode(CTRT_PIN_L2, INPUT);
    pinMode(CTRT_PIN_L3, INPUT);
    pinMode(CTRT_PIN_M, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT);
}

/*---------------------------------------主函数---------------------------------------*/
void setup() {
    pinModeInit();
    TCCR1B = TCCR1B & B11111000 | B00000001;                                  // 9,10 两个管脚的 PWM 由定时器 TIMER1 产生，这句程序改变 PWM 的频率
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonPress, RISING);  // 设置21引脚为中断
    Serial.begin(9600);
    memset(CTRTstate, 0, sizeof(bool) * CTRT_CNT * MEMORY_CNT);
    while (car_state != 0) {
    }  // 等待按下按钮

    attachInterrupt(digitalPinToInterrupt(2), getEncoder_L, CHANGE);  // 设置2引脚为中断
    attachInterrupt(digitalPinToInterrupt(3), getEncoder_R, CHANGE);  // 设置3引脚为中断

    // 剩余可用于中断的引脚：18 19 20

    // 舵机初始化
    servo_1.attach(SERVO_1);  // 将引脚与声明的舵机对象连接起来
    servo_2.attach(SERVO_2);
    servo_1.writeMicroseconds(PWM_1);
    servo_2.writeMicroseconds(PWM_2);
    delay(500);
    servoGrab();
    delay(200);
    MsTimer2::set(PERIOD, motorControl);  // 计数器：设定每隔PERIOD时间，执行一次motorControl函数
    MsTimer2::start();                    // 启动计时器
    time_base_l = millis();
}

void loop() {
    // 程序的最后一步，在转完半圈后执行
    if (nowDrop) {
        nowDrop == 0;
        MsTimer2::stop();
        detachInterrupt(digitalPinToInterrupt(2));
        detachInterrupt(digitalPinToInterrupt(3));
        detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
        analogWrite(PWM_LEFT, 0);
        analogWrite(PWM_RIGHT, 0);
        servoDrop();
        while (true) {
            analogWrite(PWM_LEFT, 0);
            analogWrite(PWM_RIGHT, 0);
        }
    }

    time_now_l = millis();
    // 每100ms执行一次
    if (time_now_l - time_base_l >= 100) {
        time_base_l += 100;
        // 给Trig发送一个短时间脉冲,触发测距
        digitalWrite(TRIG_PIN, LOW);                 // 给Trig发送一个低电平
        delayMicroseconds(2);                        // 等待2微妙
        digitalWrite(TRIG_PIN, HIGH);                // 给Trig设置高电平
        delayMicroseconds(10);                       // 等待10微妙
        digitalWrite(TRIG_PIN, LOW);                 // 给Trig设置低电平
        temp_time = float(pulseIn(ECHO_PIN, HIGH));  // 存储回波等待时间
        distance = (temp_time * 17) / 1000;          // 把回波时间换算成cm
        if (distance < 15 && isBarrier == 0) {
            time_base_a = millis();
            isBarrier = 1;
        }

        // 用于调试，打印数据
        /*
        Serial.print("Output_L:");
        Serial.println(Output_L);
        Serial.print("Output_R:");
        Serial.println(Output_R);

        Serial.print("cur_V_LEFT:");
        Serial.println(cur_V_LEFT);
        Serial.print("cur_V_RIGHT:");
        Serial.println(cur_V_RIGHT);
        Serial.print("TARGET_V_LEFT:");
        Serial.println(TARGET_V_LEFT);
        Serial.print("TARGET_V_RIGHT:");
        Serial.println(TARGET_V_RIGHT);
        Serial.print("\n");

        Serial.print("car_state:");
        Serial.println(digitalRead(car_state));

        Serial.print("distance:");
        Serial.println(distance);
        Serial.print("isBarrier:");
        Serial.println(isBarrier);

        Serial.print(CTRTstate[0][0]);
        Serial.print("\t");
        Serial.print(CTRTstate[1][0]);
        Serial.print("\t");
        Serial.print(CTRTstate[2][0]);
        Serial.print("\t");
        Serial.print(CTRTstate[3][0]);
        Serial.print("\t");
        Serial.print(CTRTstate[4][0]);
        Serial.print("\t");
        Serial.print(CTRTstate[5][0]);
        Serial.print("\t");
        Serial.print(CTRTstate[6][0]);
        Serial.print("\t");
        Serial.print(isCross);
        Serial.print("\n");

        Serial.print("quarter_turn:");
        Serial.println(quarter_turn);

        Serial.print(CTRTstate[0][1]);
        Serial.print("\t");
        Serial.print(CTRTstate[1][1]);
        Serial.print("\t");
        Serial.print(CTRTstate[2][1]);
        Serial.print("\t");
        Serial.print(CTRTstate[3][1]);
        Serial.print("\t");
        Serial.print(CTRTstate[4][1]);
        Serial.print("\t");
        Serial.print(CTRTstate[5][1]);
        Serial.print("\t");
        Serial.print(CTRTstate[6][1]);
        Serial.print("\n");
        Serial.print(CTRTstate[0][2]);
        Serial.print("\t");
        Serial.print(CTRTstate[1][2]);
        Serial.print("\t");
        Serial.print(CTRTstate[2][2]);
        Serial.print("\t");
        Serial.print(CTRTstate[3][2]);
        Serial.print("\t");
        Serial.print(CTRTstate[4][2]);
        Serial.print("\t");
        Serial.print(CTRTstate[5][2]);
        Serial.print("\t");
        Serial.print(CTRTstate[6][2]);
        Serial.print("\n");
        Serial.print("\n");
        */
    }
}
