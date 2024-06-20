#ifndef _PID_H
#define _PID_H

short pidController_L(float TARGET_V, float cur_V);
short pidController_R(float TARGET_V, float cur_V);

#endif