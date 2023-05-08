#include "PF_Motors.h"

#define MSS currentMotorSpeeds.structure // Shorthand for internal use
#define MSA currentMotorSpeeds.array // Shorthand for internal use
#define MIS motorIn.structure // Shorthand for internal use
#define MIA motorIn.array // Shorthand for internal use

void initPFMotors() {
	MSS.A = 0;
	MSS.B = 0;
	MSS.C = 0;
	MSS.D = 0;

	MIS.A = 0;
	MIS.B = 0;
	MIS.C = 0;
	MIS.D = 0;

	initFlag = 1;
}

int getPFMotorSpeed(int motor) {
	return MSA[motor];
}

task updateMotors() {
	for(;;) {
		for(int i = 0; i < 4; i++) {
			// For each motor, update speed if a change is detected
			if(MIA[i] > MSA[i]) {
				if(MIA[i] - MSA[i] > 1) {
					// Change detected, update motor speeds
					motor[mArray[i]] = MSA[i];
					MSA[i] = MIA[i];
				}
			} else {
				if(MSA[i] - MIA[i] > 1) {
					// Change detected, update motor speeds
					motor[mArray[i]] = MSA[i];
					MSA[i] = MIA[i];
				}
			}
			// Update motor speeds
			if(pulsed[i] && MSA[i] != 0) {
				// We are pulsed, go to requested speed
				motor[mArray[i]] = MSA[i];
				} else {
				if(MSA[i] > 0) {
					motor[mArray[i]] = MSA[i] - 1;
					} else {
					motor[mArray[i]] = MSA[i] + 1;
				}
			}
			pulsed[i] = !pulsed[i];
		}
	}
}

	void startMotorTask() {
		if(initFlag < 1) {
			// Not printf in RobotC yikes dawg
			} else {
			startTask(updateMotors);
		}
	}

	void exampleSetSpeedFunction() {
		// Set MotorA speed to 100:
		motorIn.structure.A = 100;   // <--
		// Or                               Both these functions set the same address in memory, they are just different ways of addressing it.
		motorIn.array[0] = 100;  // <--

		// Set MotorB speed to -50:
		motorIn.structure.B = -50;   // <--
		// Or                               Both these functions set the same address in memory, they are just different ways of addressing it.
		motorIn.array[1] = -50;  // <--
	}