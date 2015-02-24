/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 */

#include "main.h"


/** Variable to hold reference to the drive task */
TaskHandle drivingTask;
/** Variable to hold reference to the manipulator task */
TaskHandle manipulatorTask;
/** Variable to hold reference to the speaker task */
TaskHandle speakerTask;

/**
 * This task drives the motors required to move the robot. \n
 * Motor Assignments: \n
 * 	Front Left = 2 \n
 * 	Front Right = 3 \n
 * 	Back Left = 4 \n
 * 	Back Right = 5 \n
 */
void DrivingTask(void *arg) {
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
	while (1) {
		Y1 = (abs(joystickGetAnalog(1, 4)) > threshold ? joystickGetAnalog(1, 4) : 0);
		X1 = (abs(joystickGetAnalog(1, 1)) > threshold ? joystickGetAnalog(1, 1) : 0);
		X2 = (abs(joystickGetAnalog(1, 3)) > threshold ? -joystickGetAnalog(1, 3) : 0);

		if (X1 < 14 && X1 > -14) {
			motorSet(2, Y1 + X2 + X1);
			motorSet(3, Y1 - X2 - X1);
			motorSet(4, Y1 + X2 - X1);
			motorSet(5, Y1 - X2 + X1);
		} else {
			motorSet(2, -X1);
			motorSet(5, X1);
			motorSet(3, -X1);
			motorSet(4, X1);
		}
	}
}

/**
 * This task drives the motors required to use our manipulator. \n
 * Motor Assignments: \n
 * Bottom Motor = 6 \n
 * Top Motor = 7 \n
 * Very tip top motor = 8
 */
void ManipulatorTask(void *arg) {
	while (1) {
		if (joystickGetDigital(1, 6, JOY_UP)) {
			motorSet(6, 127);
			motorSet(7, 127);
			motorSet(8, 127);
		} else if (joystickGetDigital(1, 6, JOY_DOWN)) {
			motorSet(6, -127);
			motorSet(7, -127);
			motorSet(8, -127);
		} else {
			motorSet(6, 0);
			motorSet(7, 0);
			motorSet(8, 0);
		}
	}
}

/** RTTL songs */
const char * songs[10] = {
		"Ride:d=4,o=5,b=160:a,32e,8a,c6,8p,a,8p,c6,32a,8c6,e6,8p,c6,8p,e6,32c6,8e6,g6,8p, g,8p,c6,32g,8c6,2e6,p",
		"TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5",
		"MonkeyWr:d=32,o=6,b=45:g,g,f,f,e,e,d,d,f,f,e,e,d,d,c,c,d,d,c,c,a5,a5,c,c,d,d,c,c,d,d,e,d,g,g,f,f,e,e,d,d,f,f,e,e,d,d,c,c,d,d,c,c,a5,a5,c,c,d,d,c,c,d,d,e,d",
		"MyHero:d=16,o=6,b=40:32p,c,c,d.,c,8c.,a5,32c,4a5,c,c,d.,c,8c.,a5,32c,4a5,8e,8f,g.,32f,32d,32d,8c.,32c,32a,g,g,f,8c",
		"FinalCou:d=4,o=5,b=140:16c#6,32b,32p,8c#.6,16p,f#,p.,32d6,32p,32c#6,32p,32d6,16p.,32c#6,16p.,b.,p,32d6,32p,32c#6,32p,d6,f#,p.,32b,32p,32a,32p,32b,16p.,32a,16p.,32g#,16p.,32b,16p.,a.,32c#6,32p,32b,32p,c#6,2f#,p,16p,32d6,32p,32c#6,32p,32d6,16p.,32c#6,16p.,b.,p,32d6,32p,32c#6,32p,d6,f#,p.,32b,32p,32a,32p,32b,16p.,32a,16p.,32g#,16p.,32b,16p.,2a,16p,32g#,32p,32a,32p,b.,16a,16b,8c#6,8b,8a,8g#,f#,d6,1c#6,8p,16c#6,16d6,16c#6,16b,2c#.6,16p",
		"Theme:d=4,o=6,b=127:8c5,16d5,16d5,8d5,d5,8c5,8c5,8c5,8c5,16d_5,16d_5,8d_5,d_5,8d5,8d5,8d5,8c5,16d5,16d5,8d5,d5,8c5,8c5,8c5,8c5,16d_5,16d_5,8d_5,d_5,8d5,8c_5,8c5,8c,2b,8g,8f,2g",
		"",
};

/** Last time a song was played */
long lastPlayed;

/**
 * This task controls the output of the speaker on our robot.
 */
void SpeakerTask(void *arg) {
	speakerInit();
	//speakerPlayRtttl(songs[rand() % sizeof(songs)]);
	while (1) {
		//if (lastPlayed + 10000 < millis()) {
			if (joystickGetDigital(2, 7, JOY_UP)) {
				speakerPlayRtttl(songs[0]);
				lastPlayed = millis();
			} else if (joystickGetDigital(2, 7, JOY_DOWN)) {
				speakerPlayRtttl(songs[1]);
				lastPlayed = millis();
			} else if (joystickGetDigital(2, 7, JOY_LEFT)) {
				speakerPlayRtttl(songs[2]);
				lastPlayed = millis();
			} else if (joystickGetDigital(2, 7, JOY_RIGHT)) {
				speakerPlayRtttl(songs[3]);
				lastPlayed = millis();
			} else if (joystickGetDigital(2, 8, JOY_UP)) {
				speakerPlayRtttl(songs[4]);
				lastPlayed = millis();
			} else if (joystickGetDigital(2, 8, JOY_LEFT)) {
				speakerPlayRtttl(songs[5]);
				lastPlayed = millis();
			} else if (joystickGetDigital(2, 8, JOY_RIGHT)) {
				speakerPlayRtttl(songs[6]);
				lastPlayed = millis();
			}
		//}
	}
}

/**
 * Record of last time we have announced robot version to serial connection.
 */
long lastAnnounce;

/**
 * Operator control code.
 */
void operatorControl() {
	pinMode(12, INPUT);
	pinMode(11, INPUT);
	if (digitalRead(12) == false) {
		autonomous();
	} else {
		if (digitalRead(11) == false) {
			drivingTask = taskCreate(DrivingTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
			manipulatorTask = taskCreate(ManipulatorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
			speakerTask = taskCreate(SpeakerTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

			while(1) {
				if (lastAnnounce + 5000 > millis())
					continue;

				fputs("joshbot v1.0 connected we rowdy", uart1);
				lastAnnounce = millis();
			}
		} else {
			manipulatorTask = taskCreate(ManipulatorTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
			speakerTask = taskCreate(SpeakerTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

			while(1) {
				if (lastAnnounce + 5000 > millis())
					continue;

				fputs("joshbot v1.0 connected we rowdy", uart1);
				lastAnnounce = millis();

				char* strBuff;
				char* ret = fgets(strBuff, 6, uart1);

				if (ret != NULL) {
					//Packet Example:
					// Send a int like this:
					// 012710 (Sets motor 10 to -127)
					// 000010 (Sets motor 10 to 0)
					// 112710 (Sets motor 10 to 127)
					// 112701 (Sets motor 1 to 127)
					bool positive = false;
					char dirChar = ret[0];
					if (dirChar == '0') {
						positive = false;
					} else {
						positive = true;
					}
					char* motorValue[3];
					strncpy(motorValue, ret + 1, 3);

				}
			}
		}
	}
}
