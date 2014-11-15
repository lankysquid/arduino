/*------------------------------------------------------
Gauge_Pot01
Arduining.com 10 July 2011
Direct driving of Miniature Stepper Motor used as an indicator
drive for dashboard instrumentation.
Hardware:
-Arduino UNO.
-Potentiometer.
-Stepper Motor VID29-05P (Can be directly driven by MCU):
    -Low current consumption: <20mA 
    -Rotation Angle:Max 315°
    -0.5°/full step    
    -Coil resistance: 280 +/- 20Ω                           
 -----------------------------------------------------*/
#include <Stepper.h>
#define  STEPS  32    // steps per revolution (limited to 315°)
#define  COIL1  9
#define  COIL2  11
#define  COIL3  10
#define  COIL4  12
#define  COIL5  3
#define  COIL6  5
#define  COIL7  4
#define  COIL8  6

#define PotIn  0

// create an instance of the stepper class:
Stepper stepper(STEPS, COIL1, COIL2, COIL3, COIL4);
Stepper stepper_two(STEPS, COIL5, COIL6, COIL7, COIL8);

void setup(){
  stepper.setSpeed(100);    // set the motor speed to 30 RPM (360 PPS aprox.).
  stepper.step(25);       //Reset Position(630 steps counter-clockwise). 
//  Serial.begin(9600);    //for debuging.
}
int pos=0;                 //Position in steps(0-630)= (0°-315°)

void loop(){
  int val = analogRead(PotIn);   //get the potentiometer value (range 0-1023)
  val= map(val,0,1023,0,100);    // map pot range in the stepper range.

  if(abs(val - pos)> 2){         //if diference is greater than 2 steps.
      if((val - pos)> 0){
          stepper.step(-1); 
          stepper_two.step(-1);     // move one step to the left.
          pos++;
          }
      if((val - pos)< 0){
          stepper.step(1);
          stepper_two.step(1);       // move one step to the right.
          pos--;
          }
      }
//  Serial.println(pos);      //for debuging...
//  Serial.println(val);
//  delay(100);
} 
