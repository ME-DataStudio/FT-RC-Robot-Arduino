#include <IBusBM.h>
#include <Servo.h>


/*
  Translate iBUS signal to servo and motor.
  
  Based on example from IBusBM.
 
  Supports any Arduino board where serial0 is available. 
 
  For boards where serial0 is connected to the onboard USB port (such as MEGA, UNO and micro) you need
  to disconnect the RX line from the receiver during programming. 

  Please use 5V boards only.

  Serial port RX/TX connected as follows:
  - RX connected to the iBUS servo pin (disconnect during programming on MEGA, UNO and micro boards!)
  - TX left open or for Arduino boards without an onboard USB controler - connect to an 
    USB/Serial converter to display debug information on your PC (set baud rate to 115200).  

*/

IBusBM IBus; // IBus object
Servo myservo;  // create servo object to control a servo
Servo mymotor;  // create motor object to be controlled with PWM on H-bridge

void setup() {
  IBus.begin(Serial);    // iBUS connected to Serial0 - change to Serial1 or Serial2 port when required
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  mymotor.attach(11);
}

int savevalservo=0;
int savevalmotor=0;

void loop() {
  int valservo;
  int valmotor;
  
  valservo = IBus.readChannel(0); // get latest value for servo channel 1
  valmotor = iBus.readChanlle(2); // get latest value for motor channel 3
  
  if (savevalservo != valservo) {
    savevalservo = valservo;    
    myservo.writeMicroseconds(valservo);   // sets the servo position 
  }
  
   if (savevalmotor != valmotor) {
    savevalmotor = valmotor;    
    mymotor.writeMicroseconds(valmotor);   // sets the servo position 
  }
  
  delay(100);
}

