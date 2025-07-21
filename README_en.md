# AutoCar: Automated Line-Following Car for AUTO1001 <!-- omit in toc -->

<div align="center">
    <a href="/README.md">中文</a> | <b>English</b>
</div>

## Contents <!-- omit in toc -->

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Detailed Implementation](#detailed-implementation)
- [Code Execution Logic](#code-execution-logic)
- [Usage](#usage)

## Introduction

This project contains the code for the 2022 Harbin Institute of Technology (Shenzhen) AUTO1001 – [Automation Cognition and Practice](https://github.com/HITSZ-OpenAuto/AUTO1001) course assessment project: _Automated Line-Following Car_, written by [pspdada](https://github.com/pspdada), provided for reference by interested students.

The assessment consists of two parts, **Speed Racing** and **Obstacle Avoidance**, which can be completed with different code:

- **Speed Racing**
  The car must pick up a cylinder at the start of a fixed track using a custom-designed mechanical gripper, then follow the line to the finish. Along the way, it will encounter semicircular curves, right-angle turns, and other complex situations that require flexible handling. Upon reaching the finish line, the car must smoothly place the cylinder down.

- **Obstacle Avoidance**
  This part tests the car’s ability to detect obstacles and react accordingly. After avoiding an obstacle, the car must return to the track and continue driving.

Development board: Arduino Mega 2560
Assessment date and score: March 19, 2023 15:00 – 35/35

## Project Structure

- `AutoCar_def`
  Defines constants and pins; modify according to your setup.
- `control`
  Controls the car’s motion, consisting of three parts:
  - `runMode`: Determines the car’s motion mode based on infrared sensor input
  - `motorControl`: Sets the target speeds for the two wheels according to the motion mode
  - `carRun`: Outputs PWM signals to control the car based on the target wheel speeds
- `ctrt`
  Infrared module–related functions
- `encoder`
  Encoder interrupt routines
- `pid`
  PID controller
- `robotic_arm`
  Mechanical arm control

## Detailed Implementation

The most challenging part of the assessment is the right-angle turn, which easily causes the car to leave the predefined track when using conventional control methods. Therefore, we employ a register + boundary-detection approach: even if the infrared detection module (`ctrt`) mounted at the front of the car can no longer detect the line, we can infer from its previous state whether to turn left or right. This allows us to correct the trajectory before the car completely leaves the track and returns it to the predefined path.

## Code Execution Logic

```
1、Power on, execute initialization code, then pause
2、Press the button to resume program execution
3、Mechanical arm moves and grips the object
4、Infrared module reads data and determines the motion mode (e.g., left turn, straight)
5、Set the target speeds for the left and right wheels according to the motion mode
6、Calculate the current wheel speeds based on encoder readings
7、Use PID to compute the outputs from target and current speeds to drive the motors
8、When an obstacle is encountered, avoid it first
9、When the finish line is reached, perform the final action and then stop
```

## Usage

- Modify the definitions in `AutoCar_def.h` according to your wiring
- Upload the code to the development board
