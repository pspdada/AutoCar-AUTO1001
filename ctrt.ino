#include "ctrt.h"
//---------------------------------------红外模块----------------------------------------------*/

// 更新红外模块的记忆数组,数组CTRTstate[i][j]，i表示模块代号，j表示第i个模块的第j个记忆
void updateCTRTstate(void) {

  // 越界则只更新第一、二层的数据，否则更新一、二、三层数据
  for (unsigned char i = MEMORY_CNT - isCross - 1; i > 0; --i) {
    for (unsigned char j = 0; j < CTRT_CNT; ++j) {
      CTRTstate[j][i] = CTRTstate[j][i - 1];
    }
  }

  // 红外模块在检测到黑线输出高电平1，白线输出低电平0
  CTRTstate[0][0] = digitalRead(CTRT_PIN_L3);
  CTRTstate[1][0] = digitalRead(CTRT_PIN_L2);
  CTRTstate[2][0] = digitalRead(CTRT_PIN_L1);
  CTRTstate[3][0] = digitalRead(CTRT_PIN_M);
  CTRTstate[4][0] = digitalRead(CTRT_PIN_R1);
  CTRTstate[5][0] = digitalRead(CTRT_PIN_R2);
  CTRTstate[6][0] = digitalRead(CTRT_PIN_R3);


}

bool isAllLow(void) {
  if ((CTRTstate[0][0] == LOW) && (CTRTstate[1][0] == LOW) && (CTRTstate[2][0] == LOW)
      && (CTRTstate[3][0] == LOW) && (CTRTstate[4][0] == LOW) && (CTRTstate[5][0] == LOW)
      && (CTRTstate[6][0] == LOW)) {
    return 1;
  } else {
    return 0;
  }
}

bool isAllHigh(void) {
  if ((CTRTstate[0][0] == HIGH) && (CTRTstate[1][0] == HIGH) && (CTRTstate[2][0] == HIGH)
      && (CTRTstate[3][0] == HIGH) && (CTRTstate[4][0] == HIGH) && (CTRTstate[5][0] == HIGH)
      && (CTRTstate[6][0] == HIGH)) {
    return 1;
  } else {
    return 0;
  }
}
