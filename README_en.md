<div align="center">

# AutoCar: Automated Line-Following Car for AUTO1001 <!-- omit in toc -->

[中文](/README.md) | **English**

</div>

## Contents <!-- omit in toc -->

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Code Execution Logic](#code-execution-logic)
- [Detailed Implementation](#detailed-implementation)
- [Usage](#usage)
- [Project Outcome Showcase](#project-outcome-showcase)
- [License](#license)

## Introduction

This project is the assessment project for the 2022 Harbin Institute of Technology (Shenzhen) AUTO1001 – [Automation Cognition and Practice](https://github.com/HITSZ-OpenAuto/AUTO1001) course: **Automated Line-Following Car**, written by [pspdada](https://github.com/pspdada), provided for reference by interested students.

The assessment includes two parts: **Speed Racing** and **Obstacle Avoidance**, which can be completed with different code:

- In the **Speed Racing** part, the car must pick up a cylinder at the start of a fixed track using a custom-designed mechanical gripper, then follow the line to the finish. Along the way, it will encounter semicircular curves, right-angle turns, and other complex situations that require flexible handling. Upon reaching the finish line, the car must smoothly place the cylinder down.
- In the **Obstacle Avoidance** part, the car is tested for its ability to detect obstacles and react accordingly. After avoiding an obstacle, the car must return to the track and continue driving.

Development board: Arduino Mega 2560

Assessment date: March 19, 2023, Score: 35/35

## Project Structure

The core code is located in the [`AutoCar`](/AutoCar) folder of this project, and includes the following `.ino` and `.h` files:

- `AutoCar_def`: Macro definitions for constants, pins, and data types used in the project; modify according to your actual setup
- `control`: Controls the car's motion, including three parts:
  - `runMode()`: Determines the car's motion mode based on infrared sensor input
  - `motorControl()`: Sets the target speeds for the two wheels according to the motion mode
  - `carRun()`: Outputs PWM signals to control the car based on the target wheel speeds
- `ctrt`: Infrared module-related functions
  - `updateCTRTState()`: Updates the infrared module's memory array
- `encoder`: Encoder interrupt functions for obtaining motor encoder values
- `pid`: Implements PID controller algorithm
- `robotic_arm`: Mechanical arm control-related functions
  - `servoGrab()`: Controls the mechanical arm to grab objects
  - `servoDrop()`: Controls the mechanical arm to drop objects

## Code Execution Logic

1.  **Initialization:** Power on, execute initialization code, then pause.
2.  **Start:** Press the button to resume program execution.
3.  **Gripping:** Mechanical arm grabs the object.
4.  **Line Following:**
    - Infrared sensors read data and determine the motion mode (straight, left turn, right turn, etc.).
    - Set the target speeds for the left and right wheels according to the motion mode.
    - Encoder reads motor values and calculates the current wheel speeds.
    - PID controller computes the output to drive the motors based on target and current speeds.
5.  **Obstacle Avoidance:** When an obstacle is encountered, avoid it first, then return to the track.
6.  **Finish:** Upon reaching the finish line, perform the drop action and stop.

## Detailed Implementation

**Right-angle turn:** Uses a "register + boundary detection" method. Even if the infrared sensors lose the track, the system can infer the turning direction from historical states, preventing the car from leaving the track.

## Usage

1.  **Configuration:** Modify the definitions in `AutoCar_def.h` according to your wiring.
2.  **Upload:** Upload the code to the Arduino Mega 2560 development board.

## Project Outcome Showcase

Below are photographs of our completed project. This project, part of the AUTO1001 course, serves as a valuable hands-on learning experience. We hope that through this project, students can gain a deeper understanding of automatic control concepts and successfully complete the project implementation.

<table align="center">
    <p align="center">
      <img src="docs/picture1.jpg" width="80%" />
    </p>
    <p align="center">
      <img src="docs/picture2.jpg" width="80%" />
    </p>
    <p align="center">
      <img src="docs/picture3.jpg" width="80%" />
    </p>
</table>

## License

This project is licensed under the Apache 2.0 License. See [LICENSE](LICENSE) for details.