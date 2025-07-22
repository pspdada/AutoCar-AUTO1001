#include "robotic_arm.h"

/*-----------------------------------机械臂相关-------------------------------------*/
void servoGrap() {
    /*
    // 松开爪子
    for (PWM_2 = 2000; PWM_2 > 1500; PWM_2 -= 20) {
      servo_2.writeMicroseconds(PWM_2);              // 给舵机写入PWM
      delay(5);
    }
    delay(100);
    */
    // 放倒机械臂
    for (PWM_1 = 1500; PWM_1 < 2500; PWM_1 += 10) {
        servo_1.writeMicroseconds(PWM_1);
        delay(5);
    }
    delay(100);
    // 夹紧爪子
    for (PWM_2 = 1000; PWM_2 < 1600; PWM_2 += 10) {
        servo_2.writeMicroseconds(PWM_2);
        delay(5);
    }
    delay(50);
    // 立起机械臂
    for (PWM_1 = 2500; PWM_1 > 1600; PWM_1 -= 10) {
        servo_1.writeMicroseconds(PWM_1);
        delay(5);
    }
}

void servoDrop() {
    // 放倒机械臂
    for (PWM_1 = 1600; PWM_1 < 2500; PWM_1 += 10) {
        servo_1.writeMicroseconds(PWM_1);
        delay(5);
    }
    delay(200);
    // 松开爪子
    for (PWM_2 = 1550; PWM_2 > 1000; PWM_2 -= 10) {
        servo_2.writeMicroseconds(PWM_2);
        delay(5);
    }
    delay(50);
    // 立起机械臂
    for (PWM_1 = 2500; PWM_1 > 1500; PWM_1 -= 20) {
        servo_1.writeMicroseconds(PWM_1);
        delay(2);
    }
    delay(50);
    /*
    // 夹紧爪子
    for (PWM_2 = 1500; PWM_2 < 2000; PWM_2 += 20) {
      servo_2.writeMicroseconds(PWM_2);
      delay(2);
    }
    */
}