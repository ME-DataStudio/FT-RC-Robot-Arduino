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
  To boost output the 1ms - 2ms duty cycle of the 20ms period is converted as:
  1 ms - 1,5 ms is backward/forward 1ms is full throttle so 100% gives 20ms, 1,5ms is 0% which coorespondd with 0ms
  1,5 ms - 2ms is backward/forward 2ms is full throttle so 100% gives 20ms, 1,5ms is 0% which coorespondd with 0ms
*/

IBusBM IBus; // IBus object
Servo myservo;  // create servo object to control a servo

// Pins 3, 5, 6, 9, 10, 11 on Arduino UNO are PWM capable
const int pwmDC = 3 ; //initializing pin 3 as pwm for DC motor
const int pwmServo = 11; //initializing pin 11 as pwm for Servo
//For providing logic to L298 IC to choose the direction of the DC motor
const int in_1 = 8 ;
const int in_2 = 9 ;



void setup() {
   IBus.begin(Serial);    // iBUS connected to Serial0 - change to Serial1 or Serial2 port when required
   mymotor.attach(pwmDC); // speed control for DC motor
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
      switch  (valmotor) {
         case < 1490 :   
            val = map(valmotor, 1000, 1500, 20000, 0);   
            digitalWrite(in_1,HIGH) ;
            digitalWrite(in_2,LOW) ;
            mymotor.writeMicroseconds(val);
            break;
        case valmotor > 1510 :
           val = map(valmotor, 1510, 2000, 0, 20000);
           digitalWrite(in_1,LOW) ;
           digitalWrite(in_2,HIGH) ;
           mymotor.writeMicroseconds(val);
           break;
        default:
          val=0;
          mymotor.writeMicroseconds(val);
          digitalWrite(in_1,HIGH) ;
          digitalWrite(in_2,HIGH) ;
      }
   }
}
 

