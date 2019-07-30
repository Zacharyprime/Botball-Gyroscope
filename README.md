# Botball-Gyroscope
**The KIPR Gyroscope Library**

*by: Zachary Sasser*

This library utilizes the Wallaby (and later Wombat) Gyroscope to make accurate turns, drive straight, and apply other useful functions of the gyroscope. There is also example code in the "examples" folder for students and teachers to learn how the gyroscope works, teach it to students, and create new code off of it. 

**Link to Presentation:**

https://docs.google.com/presentation/d/1ClOTfmCep9FR-3RnECOgyUgoa9bkWh01geF6Dl38U3A/edit?usp=sharing

**Function List:**

*findBias()* - Finds the bias value for the gyroscope, run before the rest of your program.

*readGyro()* - Gets a filtered reading of the gyroscope output (Z axis)

*turn(angle, speed)* - Turns a desired angle at a desired speed using the gyroscope.

*arc(leftWheelSpeed, rightWheelSpeed, angle)* - Arcs the robot by setting the wheels at the specified speed until the controller has rotated the angle specified. This can also be used as a more versitile turn function.

*drive(speed, time)* - Drives in a straight line using the gyroscope and tries to keep the wheels up to the speed specified for the amount of time specified.

**Issues/Bugs:**

-The Wallaby must have the screen facing up for this library to work (Z-axis readings only). This will be fixed soon.
