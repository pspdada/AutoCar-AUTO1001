#include "pid.h"

/*------------------------------------------------PID 控制器------------------------------------------------*/
// 左轮的PID算法
short pidController_L(float TARGET_V, float cur_V) {
    LEFT_eI = TARGET_V - cur_V;
    u_L += Kp_L * (LEFT_eI - LEFT_eII) + Ki_L * LEFT_eI + Kd_L * (LEFT_eI + LEFT_eIII - 2 * LEFT_eII);
    // 输出限位
    if (u_L > 255 - 0.01) {
        u_L = 255;
    } else if (u_L < -255 + 0.01) {
        u_L = -255;
    }
    LEFT_eIII = LEFT_eII;
    LEFT_eII = LEFT_eI;
    return (short)u_L;
}
// 右轮的PID算法
short pidController_R(float TARGET_V, float cur_V) {
    RIGHT_eI = TARGET_V - cur_V;
    u_R += Kp_R * (RIGHT_eI - RIGHT_eII) + Ki_R * RIGHT_eI + Kd_R * (RIGHT_eI + RIGHT_eIII - 2 * RIGHT_eII);
    // 输出限位
    if (u_R > 255 - 0.01) {
        u_R = 255;
    } else if (u_R < -255 + 0.01) {
        u_R = -255;
    }
    RIGHT_eIII = RIGHT_eII;
    RIGHT_eII = RIGHT_eI;
    return (short)u_R;
}