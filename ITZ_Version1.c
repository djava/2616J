#pragma config(Sensor, in1,    Left_Arm,       sensorPotentiometer)
#pragma config(Sensor, in2,    Right_Arm,      sensorPotentiometer)
#pragma config(Sensor, dgtl9,  drive_LeftSensor, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, drive_RightSensor, sensorQuadEncoder)
#pragma config(Motor,  port2,           drive_Right,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           mogo,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           lift_Left,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           fourBar_Left,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           fourBar_Right, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           lift_Right,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           claw,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           drive_Left,    tmotorVex393HighSpeed_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard               !!//

//---------------------------------------------------------------------------//
/*                                                                           /
/        Description: Competition template for VEX EDR                      /
/                                                                           /
/---------------------------------------------------------------------------*/
// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
#define drivethreshhold 10
#define drivelimit 127
static float  pid_Kp = 0.5;
//static float  pidRequestedValue;
//---------------------------------------------------------------------------//
/*                          Pre-Autonomous Functions                         /
/                                                                           /
/  You may want to perform some actions before the competition starts.      /
/  Do them in the following function.  You must return from this function   /
/  or the autonomous and usercontrol tasks will not be started.  This       /
/  function is only called once after the cortex has been powered on and    /
/  not every time that the robot is disabled.                               /
/---------------------------------------------------------------------------/



/-----------------------------------------------------------------------------/
/                                                                             /
/  main task                                                                  /
/                                                                             /
/-----------------------------------------------------------------------------*/
int countx = 0; //counter for function at line 199
void stack (int coneNumber){

}

void drive_Forward(int power) {
	motor[drive_Left]= power;
	motor[drive_Right] =power;
}

void turn_Left(int power) {
	motor[drive_Left]= power;
	motor[drive_Right] =-power;
}

void turn_Right(int power) {
	motor[drive_Left]= -power;
	motor[drive_Right] = power;
}

void drive_Backward(int power) {
	motor[drive_Left]= -power;
	motor[drive_Right] =-power;
}

void arm_Up (int power) {
	motor[lift_Left] =power;
	motor[lift_Right] =power;
}

void arm_Down (int power) {
	motor[lift_Left] =-power;
	motor[lift_Right] =-power;
}

void claw_Open (int power) {
	motor[claw] =power;
}

void claw_Close (int power) {
	motor[claw] =-power;
}

void mogo_In (int power) {
	motor[mogo] =-power;
}

void mogo_Out (int power) {
	motor[mogo] =power;
}

void fourBar_Forward (int power) {
	motor[fourBar_Left] =power;
	motor[fourBar_Right] = power;
}

void fourBar_Backwards (int power) {
	motor[fourBar_Left] =-power;
	motor[fourBar_Right] = -power;
}

#define average ((SensorValue[drive_LeftSensor]+SensorValue[drive_RightSensor])/2)
void auton_DriveForward(int degrees){
	while (average < degrees){
		drive_Forward(127);
	}
	drive_Forward(0);
	SensorValue[drive_LeftSensor] = 0;
	SensorValue[drive_RightSensor] = 0;

}

void auton_MogoOut(int degrees){
while (SensorValue [mogo] < degrees){		//Need to check the encoddr value
mogo_Out(127);
}
mogo_Out(0);
SensorValue[mogo] = 0;
}

void auton_MogoIn( int degrees){
while (SensorValue [mogo] > -degrees){		//Need to check the encoder value
mogo_In(127);
}
mogo_In(0);
SensorValue[mogo] = 0;
}
void auton_TurnRight( int rotations){
	while (SensorValue [drive_Right] < rotations){
		turn_Right(127); // Test this, it may be the other way around
	}
	turn_Right(0);
	SensorValue[drive_RightSensor] = 0;
}
void auton_TurnLeft( int rotations){
	while (SensorValue [drive_LeftSensor] < rotations){
		turn_Left(127); // Test this, it may be the other way around (it is, same with lift)
	}
	turn_Left(0);
	SensorValue[drive_LeftSensor] = 0;
}
void auton_DriveBackwards(int degrees){

	while (average < degrees){
		drive_Backward(127);
	}
	drive_Backward(0);
	SensorValue[drive_LeftSensor] =0;
	SensorValue[drive_RightSensor] =0;
}
void resetSensors(){
	SensorValue[drive_Left] = 0;
	SensorValue[drive_Right] = 0;

}
task pidController()
{
	float  pidSensorCurrentValue;
	float  pidError;
	float  pidArm;

	while( true )
	{
		// Read the sensor value and scale
		pidSensorCurrentValue = SensorValue[Left_Arm];

		// calculate error
		pidError =  SensorValue[Right_Arm] - pidSensorCurrentValue;
		pidArm = (pid_Kp * pidError);

		// limit drive
		if( pidArm > 127 )
			pidArm = 127;
		if( pidArm < (-127) )
			pidArm = (-127);

		// send to motor
		motor[lift_Left ] = pidArm;

		// Don't hog cpu
		wait1Msec( 25 );
	}
}
	void stack_ArmUp (int rotations){
  		while (SensorValue [lift_Left] < rotations){
		arm_Up(127); // Test this, it may be the other way around (it is, same with lift)
	}
	arm_Up(0);
	SensorValue[lift_Left] = 0;

}
void testFunction(int rotations){
// if this function is called the thing raises according to a value in an array.
//everytime the button is pressed a counter variable is incremented
// the counter variable will index the array to determine certain height raised

int heights [] = {10}; //figure out the predetermined heights
//Don't know which part is being used//

while(SensorValue[Lift_Left] <heights[countx]){
	arm_Down(127);
}
wait1Msec(25);

//Manual control to allign the cone needs to somehow be implemented
claw_Open(1);claw_Close(1);
while(SensorValue[Lift_Left] <heights[countx -1]){
	arm_Up(127);
}
	//I assume that dropping it down to the previous height is suitable
wait1Msec(25);
motor [lift_Left] = heights[countx +1] //This will raise the thing high enough
wait1Msec(25);
motor [lift_Left] = 0; //resets the thing back down
countx++;//Not sure if this is what you want but I got down the basic logic
}
void pre_auton()
{
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

//---------------------------------------------------------------------------//
/*                                                                           /
/                              Autonomous Task                              /
/                                                                           /
/  This task is used to control your robot during the autonomous phase of   /
/  a VEX Competition.                                                       /
/                                                                           /
/  You must modify the code to add your own robot specific commands here.   /
/---------------------------------------------------------------------------*/

task autonomous()
{
	/*    claw_Close(127);
	wait10Msec(100);
	claw_Close(80);
	arm_Down(127);
	wait10Msec(150);
	arm_Down(0);
	drive_Forward(127);
	wait10Msec(150);
	drive_Forward(0);
	arm_Up(127);
	wait10Msec(100);
	arm_Up(0);
	claw_Open(127);
	wait10Msec(250);
	claw_Open(0);

	resetSensors();
	*/
	//Cleared the sensor values
	/*
	resetSensors();
	//
	arm_Down(127);
	wait10Msec(115);
	arm_Down(0);
	//
	fourBar_Backwards(127);
	wait10Msec(115);
	fourBar_Backwards(0);
	//
	mogo_In(127);
	wait10Msec(115);
	mogo_In(0);
	//
	auton_DriveForward(803);
	resetSensors();
	//
	mogo_Out(127);
	wait10Msec(115);
	mogo_Out(0);
	//
	auton_TurnRight(250);
	resetSensors();
	//
	auton_DriveForward(3409);
	resetSensors();
	//
	auton_TurnLeft(100);
	resetSensors();
	//
	mogo_In(127);
	wait10Msec(115);
	mogo_In(0);
	//
	auton_DriveBackwards(196);
	resetSensors();

	//Stop the mobile goal intake
	*/
	/* Auton Two
	auton_MogoOut(510);
	auton_DriveForward(1380);
	auton_MogoIn(-510);
	auton_TurnLeft(2228);
	auton_DriveForward(1718);
	auton_MogoOut(510);
	auton_DriveBackwards(690);

	*/
	arm_Down(127);
	wait10Msec(50);
	arm_Down(0);
	mogo_In(127);
	wait10Msec(115);
	mogo_In(0);
	drive_Forward(127);
	wait10Msec(230);
	drive_Forward(0);
	mogo_Out(127);
	wait10Msec(155);
	mogo_Out(0);
  fourBar_Backwards(127);
  wait10Msec(15);
  fourBar_Backwards(0);
	claw_Open(127);
	wait10Msec(115);
	claw_Open(0);
	mogo_In(127);
	wait10Msec(125);
	mogo_In(0);
	drive_Backward(127);
	wait10Msec(90);
	drive_Backward(0);
	/*
	drive_Backward(127);
	wait10Msec(255);
	drive_Backward(0);
	turn_Left(127);
	wait10Msec(130)
	turn_Left(0);

	drive_Forward(127);
	wait10Msec(220);

	drive_Forward(0);
	mogo_In(127);
	wait10Msec(125);
	mogo_In(0);
	drive_Backward(127);
	wait10Msec(300);
	drive_Backward(0);*/

}
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................

	// Remove this function call once you have "real" code.


//---------------------------------------------------------------------------//
/*                                                                           /
/                              User Control Task                            /
/                                                                           /
/  This task is used to control your robot during the user control phase of /
/  a VEX Competition.                                                       /
/                                                                           /
/  You must modify the code to add your own robot specific commands here.   /
/---------------------------------------------------------------------------*/

task usercontrol()
{
	while(true) {
	if(vexRT[Btn6UXmtr2]) {   //Claw stuffs
		arm_Down(127);
		} else if(vexRT[Btn6DXmtr2]) {
		arm_Up(127);
	}
	else{
		arm_Down(0);
	}
	if(vexRT[Btn6D]){
		mogo_In(127);
	}
	else if(vexRT[Btn6U]){
		mogo_Out(127);
	}
	else{
		mogo_In(0);
	}

	if(vexRT[Btn5DXmtr2]){
		fourBar_Forward(127);
	}
	else if(vexRT[Btn5UXmtr2]){
		fourBar_Forward(-127);
	}
	else{
		fourBar_Forward(0);
	}
/*
	if(vexRT[Btn7U]){
		fourBar_Backwards(127);
	}
	else if(vexRT[Btn7R]){
		fourBar_Forward(127);
	}
	else{
		fourBar_Forward(0);
	}*/
	if(vexRT[Btn5D]) {   //Claw stuffs
		claw_Close(0);
		} else if(vexRT[Btn5U]) {
		claw_Open(127);
	}
	else{
		claw_Close(127);

	}
  if(vexRT[Btn8DXmtr2]){//Claw stuffs
	mogo_Out(127);
		} else if(vexRT[Btn8RXmtr2]) {
		mogo_In(127);
	}
	else{
		mogo_Out(0);

	}


	motor[drive_Left]  = -(abs(vexRT[Ch2])> drivethreshhold)?((vexRT[Ch2]>drivelimit)?drivelimit:((vexRT[Ch2]<(-drivelimit))?-drivelimit:vexRT[Ch2])):0;  //Driving Stuffs I need to figure out (is that a ternary inside of a ternary?)
	motor[drive_Right]  = (abs(vexRT[Ch3])> drivethreshhold)?((vexRT[Ch3]>drivelimit)?drivelimit:((vexRT[Ch3]<(-drivelimit))?-drivelimit:vexRT[Ch3])):0;



}
}
