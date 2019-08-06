/*
The KIPR Gyroscope Library
by: Zachary Sasser

This library utilizes the Wallaby (and later Wombat) Gyroscope to 
make accurate turns, drive straight, and apply other useful functions of the gyroscope.
*/


#include <kipr/botball.h>
double bias; //Make bias a global variable so that all functions can see it
double conversion = 1024/250;

int findBias(){
	//Stop the motors to make bot stand still
	ao();
	msleep(300);
	
	//Find the average noise
	int i = 0;
	double avg = 0;
	while(i < 50){
		avg += gyro_z();
		msleep(1);
		i++;
	}
	bias = avg / 50.0;
	return bias;
}

int readGyro(){
	return gyro_z() - bias;
}

void turn(int angle, int speed){
	int targetAngle = angle*conversion; //Conversion is 1024/250 to convert KIPR Units to degrees
	int currentAngle = 0; 
	int timeInterval = 10;
	
	double newGyro = readGyro();
	while(abs(currentAngle) < targetAngle){
		oldGyro = newGyro;
		
		if(currentAngle<targetAngle){
			motor(0,-speed);
			motor(1,speed);
		}
		else{
			motor(0,speed);
			motor(1,-speed);
		}
		
		msleep(timeInterval);
		newGyro = readGyro();
		
		//Trapezoid Sum to find new angle approximation
		currentAngle += 0.5*(newGyro-oldGyro)*timeInterval/1000 + oldGyro * timeInterval/1000;
	}
}

void arc(int leftSpeed, int rightSpeed, double targetAngle){
	double angle = 0;
	mav(0, rightSpeed);
	mav(1, leftSpeed);
	while(abs(angle) < targetAngle*conversion){
		msleep(timeInterval);
		angle += readGyro() * timeInterval/1000;
	}
	mav(0,0);
	mav(1,0);
}

/*
Drives straight using the gyroscope for a specified time and speed.
*/
int rightSpeed, leftSpeed; //Initialize Variables
double fixedAngle;
void drive(int speed, int time){
	int currentTime = 0;
	double currentAngle = 0;
	double newGyro = readGyro();
	
	while(currentTime<time){
		fixedAngle = currentAngle/conversion;
		rightSpeed = speed - (3.27 + 4.15*fixedAngle + 0.139 * pow(fixedAngle,2))/2;
		leftSpeed = speed + (3.27 + 4.15*fixedAngle + 0.139 * pow(fixedAngle,2))/2;
		
		oldGyro = newGyro;
		newGyro = readGyro(); //Update Gyro values for integration
		
		mav(1,rightSpeed);
		mav(0,leftSpeed);
		
		msleep(timeInterval);
		currentTime+=timeInterval;
		
		//Trapazoid Sum
		currentAngle += 0.5*(newGyro-oldGyro)*timeInterval/1000 + oldGyro * timeInterval/1000;
	}
}
