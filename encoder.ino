#include "encoder.h"

/*---------------------------------编码器中断函数------------------------*/
//获取电机1的编码器值
void getEncoder_L(void) {
  if (digitalRead(ENCODER_LEFT_A) == LOW) {
    if (digitalRead(ENCODER_LEFT_B) == LOW) {
      encoderVal_LEFT--;
    } else {
      encoderVal_LEFT++;
    }
  } else {
    if (digitalRead(ENCODER_LEFT_B) == LOW) {
      encoderVal_LEFT++;
    } else {
      encoderVal_LEFT--;
    }
  }
}
//获取电机2的编码器值
void getEncoder_R(void) {
  if (digitalRead(ENCODER_RIGHT_A) == LOW) {
    if (digitalRead(ENCODER_RIGHT_B) == LOW) {
      encoderVal_RIGHT--;
    } else {
      encoderVal_RIGHT++;
    }
  } else {
    if (digitalRead(ENCODER_RIGHT_B) == LOW) {
      encoderVal_RIGHT++;
    } else {
      encoderVal_RIGHT--;
    }
  }
}