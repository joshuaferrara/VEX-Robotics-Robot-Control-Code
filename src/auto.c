/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.*/

#include "main.h"

/**
 * Determines if we should run our bad autonomous plan.
 */
bool badPlan1 = false;

/**
 * Determines if we should run our good autonomous plan.
 */
bool goodPlan1 = true;

/**
 * Runs autonomous code. \n
 * Contains code to run our autonomous plans. \n
 */
void autonomous() {
	if (badPlan1) {
		//Lift cube
		motorSet(6, 127);
		motorSet(7, 127);
		motorSet(8, 127);
		taskDelay(2000);
		motorSet(6, 0);
		motorSet(7, 0);
		motorSet(8, 0);

		//Turns robot
		//Positive number = right; Negative number = left.
		int Y1 = 127;
		int X1 = 0;
		int X2 = 0;
		motorSet(2, Y1 + X2 + X1);
		motorSet(3, Y1 - X2 - X1);
		motorSet(4, Y1 + X2 - X1);
		motorSet(5, Y1 - X2 + X1);

		taskDelay(800);

		//Go forward
		X2 = -127;
		Y1 = 0;
		X1 = 0;
		motorSet(2, Y1 + X2 + X1);
		motorSet(3, Y1 - X2 - X1);
		motorSet(4, Y1 + X2 - X1);
		motorSet(5, Y1 - X2 + X1);

		taskDelay(2000);

		//Stop
		motorSet(2, 0);
		motorSet(5, 0);
		motorSet(3, 0);
		motorSet(4, 0);

		//Drop Cube
		motorSet(6, -127);
		motorSet(7, -127);
		motorSet(8, -127);

		taskDelay(1500);

		//Stop dropping
		motorSet(6, 0);
		motorSet(7, 0);
		motorSet(8, 0);

		//Go back
		X2 = 127;
		Y1 = 0;
		X1 = 0;
		motorSet(2, Y1 + X2 + X1);
		motorSet(3, Y1 - X2 - X1);
		motorSet(4, Y1 + X2 - X1);
		motorSet(5, Y1 - X2 + X1);

		taskDelay(1000);

		//Stop
		motorSet(2, 0);
		motorSet(5, 0);
		motorSet(3, 0);
		motorSet(4, 0);
	} else if (goodPlan1) {
		//Raise Lift
		motorSet(6, 127);
		motorSet(7, 127);
		motorSet(8, 127);

		taskDelay(150);

		//Stop lifting
		motorSet(6, 0);
		motorSet(7, 0);
		motorSet(8, 0);

		//Go forward
		int X2 = -127;
		int Y1 = 0;
		int X1 = 0;
		motorSet(2, Y1 + X2 + X1);
		motorSet(3, Y1 - X2 - X1);
		motorSet(4, Y1 + X2 - X1);
		motorSet(5, Y1 - X2 + X1);

		taskDelay(1100);

		//Stop going forward
		motorSet(2, 0);
		motorSet(3, 0);
		motorSet(4, 0);
		motorSet(5, 0);

		//Lift cube & stop lifting cube
		motorSet(6, 127);
		motorSet(7, 127);
		motorSet(8, 127);
		taskDelay(2000);
		motorSet(6, 0);
		motorSet(7, 0);
		motorSet(8, 0);

		/*
		//Turn left
		Y1 = -127;
		X1 = 0;
		X2 = 0;
		motorSet(2, Y1 + X2 + X1);
		motorSet(3, Y1 - X2 - X1);
		motorSet(4, Y1 + X2 - X1);
		motorSet(5, Y1 - X2 + X1);

		taskDelay(800);

		//Stop turning left
		motorSet(2, 0);
		motorSet(3, 0);
		motorSet(4, 0);
		motorSet(5, 0);

		//Go forward
		X2 = -127;
		Y1 = 0;
		X1 = 0;
		motorSet(2, Y1 + X2 + X1);
		motorSet(3, Y1 - X2 - X1);
		motorSet(4, Y1 + X2 - X1);
		motorSet(5, Y1 - X2 + X1);

		taskDelay(1100);

		//Stop going forward
		motorSet(2, 0);
		motorSet(3, 0);
		motorSet(4, 0);
		motorSet(5, 0);

		//Turn left
		Y1 = -127;
		X1 = 0;
		X2 = 0;
		motorSet(2, Y1 + X2 + X1);
		motorSet(3, Y1 - X2 - X1);
		motorSet(4, Y1 + X2 - X1);
		motorSet(5, Y1 - X2 + X1);

		taskDelay(1100);

		//Stop turning left
		motorSet(2, 0);
		motorSet(3, 0);
		motorSet(4, 0);
		motorSet(5, 0);

		//Go forward
		X2 = -127;
		Y1 = 0;
		X1 = 0;
		motorSet(2, Y1 + X2 + X1);
		motorSet(3, Y1 - X2 - X1);
		motorSet(4, Y1 + X2 - X1);
		motorSet(5, Y1 - X2 + X1);

		taskDelay(2200);

		//Stop going forward
		motorSet(2, 0);
		motorSet(3, 0);
		motorSet(4, 0);
		motorSet(5, 0);

		//Drop Cube
		motorSet(6, -127);
		motorSet(7, -127);
		motorSet(8, -127);

		taskDelay(1000);

		//Stop dropping
		motorSet(6, 0);
		motorSet(7, 0);
		motorSet(8, 0);
		*/
	}
}
