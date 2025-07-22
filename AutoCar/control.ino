#include "control.h"

// 根据红外传感器的输出来决定小车运动模式
uint8_t runMode(void) {
    if (!isFinish) updateCTRTstate();  // 更新CTRT数据
    /*
    Serial.print(2);
    Serial.print("\t");
    */

    if (isFinish == 1) {  // 到达终点时，执行最后的动作(开环控制)
        time_now_f = millis();
        // 记录：16速时 200 1000 1100 1800 2000
        // 记录：20速时 200 800 900 1500 1700
        if (time_now_f - time_base_f <= 200) {
            return _STOP;
        } else if (time_now_f - time_base_f <= 1000) {
            return CIRCLE;
        } else if (time_now_f - time_base_f <= 1100) {
            return _STOP;
        } else if (time_now_f - time_base_f <= 1800) {
            return REVERSE;
        } else if (time_now_f - time_base_f <= 2000) {
            return _STOP;
        } else {
            nowDrop = 1;
            return _STOP;
        }
    }
    if (isBarrier == 1) {  // 发现障碍物时，优先躲避障碍物(开环控制)
        time_now_a = millis();
        // 记录：16速时 雪糕桶15cm 800 1300 2000 2400 2800
        // 记录：16速时 水壶15cm 700 1100 1700 2100 2800
        if (time_now_a - time_base_a <= 700) {
            return TURN_LEFT_MID;
        } else if (time_now_a - time_base_a <= 1100) {
            return STRAIGHT_ON;
        } else if (time_now_a - time_base_a <= 1700) {
            return TURN_RIGHT_MID;
        } else if (time_now_a - time_base_a <= 2100) {
            return STRAIGHT_ON;
        } else if (time_now_a - time_base_a <= 2800) {
            return TURN_LEFT_MID;
            if (!isAllLow()) {  // 再次检测到黑线，则退出避障模式
                isBarrier = 0;
            }
        } else {
            isBarrier = 0;
        }
    }

    while (true) {
        if (isCross == 0) {  // 根据红外传感器的输出来决定运动模式
            if (isAllLow())  // 未检测到黑线时，进入记忆模式
            {
                // return SLOW_ON;  // 调试用
                // return REVERSE;  // 调试用
                // 寻迹用
                isCross = 1;
                quarter_turn = NOPE;
            } else if (isAllHigh() && isFinish == 0)  // 全为黑线时，到达终点
            {
                // 寻迹用
                isFinish = 1;
                time_base_f = millis();
                // 调试用
                // turnAroundandDrop();
                return SLOW_ON;
            } else if (CTRTstate[6][0] == HIGH)  // 直角右转
            {
                return TURN_RIGHT_HIGH_F;
            } else if (CTRTstate[5][0] == HIGH)  // 中右转
            {
                return TURN_RIGHT_MID;
            } else if (CTRTstate[0][0] == HIGH)  // 直角左转
            {
                return TURN_LEFT_HIGH_F;
            } else if (CTRTstate[1][0] == HIGH)  // 中左转
            {
                return TURN_LEFT_MID;
            } else if (CTRTstate[2][0] == HIGH)  // 低左转
            {
                return TURN_LEFT_LOW;
            } else if (CTRTstate[4][0] == HIGH)  // 低右转
            {
                return TURN_RIGHT_LOW;
            } else if (CTRTstate[3][0] == HIGH)  // 直走
            {
                return STRAIGHT_ON;
            } else  // 直走
            {
                return _STOP;
            }
        }
        if (isCross == 1) {  // 记忆模式
            /* // 效果不好
            if (quarter_turn == QT_L && (CTRTstate[0][0] == HIGH || CTRTstate[1][0] == HIGH)) {
              isCross = 0;
              quarter_turn = NOPE;
              return TURN_LEFT_HIGH;
            } else if (quarter_turn == QT_R && (CTRTstate[6][0] == HIGH || CTRTstate[5][0] == HIGH)) {
              isCross = 0;
              quarter_turn = NOPE;
              return TURN_RIGHT_HIGH;
            } else if ((quarter_turn == NOPE) && (!isAllLow())) {
              isCross = 0;
              return SLOW_ON;
            }
            */
            if (!isAllLow()) {  // 再次检测到黑线，则退出记忆模式
                isCross = 0;
            }
            if (CTRTstate[0][1] == HIGH || CTRTstate[0][2] == HIGH || CTRTstate[0][3] == HIGH)  // 直角左转
            {
                quarter_turn = QT_L;
                return TURN_LEFT_HIGH_F;
            } else if (CTRTstate[6][1] == HIGH || CTRTstate[6][2] == HIGH || CTRTstate[6][3] == HIGH)  // 直角右转
            {
                quarter_turn = QT_R;
                return TURN_RIGHT_HIGH_F;
            } else if (CTRTstate[1][1] == HIGH || CTRTstate[1][2] == HIGH || CTRTstate[1][3] == HIGH)  // 中左转
            {
                // return TURN_LEFT_MID;
                return TURN_LEFT_HIGH;
            } else if (CTRTstate[5][1] == HIGH || CTRTstate[5][2] == HIGH || CTRTstate[5][3] == HIGH)  // 中右转
            {
                // return TURN_RIGHT_MID;
                return TURN_RIGHT_HIGH;
            } else if (CTRTstate[2][1] == HIGH || CTRTstate[2][2] == HIGH || CTRTstate[2][3] == HIGH)  // 低左转
            {
                // return TURN_LEFT_LOW;
                return TURN_LEFT_HIGH;
            } else if (CTRTstate[4][1] == HIGH || CTRTstate[4][2] == HIGH || CTRTstate[4][3] == HIGH)  // 低右转
            {
                // return TURN_RIGHT_LOW;
                return TURN_RIGHT_HIGH;
            } else {
                return SLOW_ON;
            }
        }
    }
}

// 根据小车运动模式选择小车两轮的目标速度
void motorControl(void) {
    /*
    Serial.print(1);
    Serial.print("\t");
    */
    if (!isFinish) updateCTRTstate();  // 更新CTRT数据
    char mode = runMode();
    /*
    Serial.print(3);
    Serial.print("\t");
    */
    switch (mode) {
        case _STOP:  // 停转
            TARGET_V_LEFT = 0;
            TARGET_V_RIGHT = 0;
            break;
        case STRAIGHT_ON:  // 全速直行
            TARGET_V_LEFT = -base_V * 0.9;
            TARGET_V_RIGHT = base_V * 0.9;
            break;
        case SLOW_ON:  // 减速直行
            TARGET_V_LEFT = -base_V * 0.5;
            TARGET_V_RIGHT = base_V * 0.5;
            break;
        case TURN_RIGHT_MID:  // 中右转
            TARGET_V_LEFT = -base_V * 0.75;
            TARGET_V_RIGHT = base_V * 0.15;
            break;
        case TURN_RIGHT_HIGH:  // 直角右转
            TARGET_V_LEFT = -base_V;
            TARGET_V_RIGHT = 0;
            break;
        case TURN_RIGHT_HIGH_F:  // 直角右转
            TARGET_V_LEFT = -base_V * 1.5;
            TARGET_V_RIGHT = 0;
            break;
        case REVERSE:  // 倒车
            TARGET_V_LEFT = +base_V * 0.5;
            TARGET_V_RIGHT = -base_V * 0.5;
            break;
        case TURN_LEFT_LOW:  // 低左转
            TARGET_V_LEFT = -base_V * 0.5;
            TARGET_V_RIGHT = base_V * 0.85;  // 0.9
            break;
        case TURN_LEFT_MID:  // 中左转
            TARGET_V_LEFT = -base_V * 0.15;
            TARGET_V_RIGHT = base_V * 0.75;
            break;
        case TURN_LEFT_HIGH:  // 直角左转
            TARGET_V_LEFT = 0;
            TARGET_V_RIGHT = base_V;
            break;
        case TURN_LEFT_HIGH_F:  // 直角左转_快速
            TARGET_V_LEFT = 0;
            TARGET_V_RIGHT = base_V * 1.5;
            break;
        case TURN_RIGHT_LOW:  // 低右转
            TARGET_V_LEFT = -base_V * 0.85;
            TARGET_V_RIGHT = base_V * 0.5;
            break;
        case CIRCLE:  // 转圈
            TARGET_V_LEFT = +base_V * 0.7;
            TARGET_V_RIGHT = base_V * 0.7;
            break;
        default:  // 停车
            TARGET_V_LEFT = 0;
            TARGET_V_RIGHT = 0;
            break;
    }

    // 平滑输出
    TARGET_V_LEFT = TARGET_V_LEFT * 0.5 + f_V_L * 0.3 + ff_V_L * 0.2;
    TARGET_V_RIGHT = TARGET_V_RIGHT * 0.5 + f_V_R * 0.3 + ff_V_R * 0.2;

    // 计算轮子转动速度（弧度制的速度，2π Rn）
    cur_V_LEFT = (encoderVal_LEFT / 780.0) * PI * 2 * (1000 / PERIOD);
    cur_V_RIGHT = (encoderVal_RIGHT / 780.0) * PI * 2 * (1000 / PERIOD);

    encoderVal_RIGHT = 0;
    encoderVal_LEFT = 0;

    carRun();

    // 储存速度
    ff_V_L = f_V_L;
    f_V_L = TARGET_V_LEFT;
    ff_V_R = f_V_R;
    f_V_R = TARGET_V_RIGHT;
}

// 根据小车两轮的目标速度来输出 PWM 波控制小车
void carRun(void) {
    Output_L = pidController_L(TARGET_V_LEFT, cur_V_LEFT);
    if (TARGET_V_LEFT == 0) {
        digitalWrite(IN_L1, HIGH);
        digitalWrite(IN_L2, HIGH);
    } else {
        if (Output_L > 0) {
            digitalWrite(IN_L1, LOW);
            digitalWrite(IN_L2, HIGH);
            analogWrite(PWM_LEFT, Output_L);
        } else {
            digitalWrite(IN_L1, HIGH);
            digitalWrite(IN_L2, LOW);
            analogWrite(PWM_LEFT, abs(Output_L));
        }
    }
    Output_R = pidController_R(TARGET_V_RIGHT, cur_V_RIGHT);
    if (TARGET_V_RIGHT == 0) {
        digitalWrite(IN_R1, HIGH);
        digitalWrite(IN_R2, HIGH);
    } else {
        if (Output_R > 0) {
            digitalWrite(IN_R1, LOW);
            digitalWrite(IN_R2, HIGH);
            analogWrite(PWM_RIGHT, Output_R);
        } else {
            digitalWrite(IN_R1, HIGH);
            digitalWrite(IN_R2, LOW);
            analogWrite(PWM_RIGHT, abs(Output_R));
        }
    }
}

void buttonPress() {
    if (car_state == 1)
        car_state = 0;
    else
        car_state = 1;
}