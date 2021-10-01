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
  
  Combination with DC motor drive via H-Bridge from: https://www.tutorialspoint.com/arduino/arduino_dc_motor.htm
*/

IBusBM IBus; // IBus object
Servo myservo;  // create servo object to control a servo

// Pins 3, 5, 6, 9, 10, 11 on Arduino UNO are PWM capable
const int pwmDC = 3 ; //initializing pin 3 as pwm for DC motor
const int pwmServo = 11; //initializing pin 11 as pwm for Servo
const int in_1 = 8 ;
const int in_2 = 9 ;
//For providing logic to L298 IC to choose the direction of the DC motor


void setup() {
  IBus.begin(Serial);    // iBUS connected to Serial0 - change to Serial1 or Serial2 port when required
  
  myservo.attach(pwmServo);  // attaches the servo on pin 9 to the servo object
  
  pinMode(pwmDC,OUTPUT) ; //we have to set PWM pin as output
  pinMode(in_1,OUTPUT) ; //Logic pins are also set as output
  pinMode(in_2,OUTPUT) ;
}

int savevalservo=0;
int savevalmotor=0;

void loop() {
  int valservo;
  int valmotor;
  
  valservo = IBus.readChannel(0); // get latest value for servo channel 1
  valmotor = IBus.readChannel(2); // get latest value for motor channel 3
  
  if (savevalservo != valservo) {
    savevalservo = valservo;    
    myservo.writeMicroseconds(valservo);   // sets the servo position 
  }
  
   if (savevalmotor != valmotor) {
    savevalmotor = valmotor;    
    if valmotor
    // motor direction and speed
  }
  
 //For Clock wise motion , in_1 = High , in_2 = Low
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,LOW) ;
   analogWrite(pwmDC,255) ; //my motor can be used from 100 - 255 from 8.4V supply
   /* setting pwm of the motor to 255 we can change the speed of rotation
   by changing pwm input but we are only using arduino so we are using highest
   value to driver the motor */
   //Clockwise for 3 secs
   delay(3000) ;
   //For brake
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,HIGH) ;
   delay(1000) ;
   //For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
   digitalWrite(in_1,LOW) ;
   digitalWrite(in_2,HIGH) ;
   delay(3000) ;
   //For brake
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,HIGH) ;
   delay(1000) ;
}

