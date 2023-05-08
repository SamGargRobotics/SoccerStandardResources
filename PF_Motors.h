#ifndef PF_MOTORS_H_
#define PF_MOTORS_H_

#define MAX_MOTORS 4

typedef struct motorControl_s {
		long int A, B, C, D;
} t_motorControl_s;

typedef union motorControl_u {
    t_motorControl_s structure;
    long int array[4];
} t_motorControl;

t_motorControl motorIn; // Set motor speeds for all motors
t_motorControl currentMotorSpeeds; // Holds the current motor speeds

bool pulsed[4] = false;

int initFlag = 0;

tMotor mArray[4] = {motorA, motorB, motorC, motorD};

void initPFMotors(); // Init PF motors

int getPFMotorSpeed(int motor); // Get speed of each motor

task updateMotors(); // Pulse speeds

void startMotorTask(); // Start the motor task

void exampleSetSpeedFunction(); // An example function on how to set motor speeds in your main loop / program

#endif // PF_MOTORS_H_