#include "CurieIMU.h"
#include <Servo.h>
int pos1;
int a,b;
Servo nservo;
const int z = 7;     // the number of the pushbutton pin
// variables will change:
int bState = 0; 
Servo myservo;
Servo mservo;
Servo meservo;
int pos,pos2;
int av1=A0;
int av2=A1;
int led =13;
int lastval,lval,lv;
void setup() 
{
  //Serial.begin(9600); // initialize Serial communication   // wait for the serial port to open
  lv=90;
  lastval=90;
  lval=90;
  pinMode(led,OUTPUT);
  // initialize device
  //Serial.println("Initializing IMU device...");
  CurieIMU.begin();
  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  mservo.attach(6);
  meservo.attach(5);
  nservo.attach(3);
  // initialize the LED pin as an output:
  // initialize the pushbutton pin as an input:
  pinMode(z, INPUT);
}

void loop() 
{
  int axRaw, ayRaw, azRaw;         // raw accelerometer values
  // read raw accelerometer measurements from device
  CurieIMU.readAccelerometer(axRaw, ayRaw, azRaw);
  a=analogRead(av1);
  b=analogRead(av2);
  // convert the raw accelerometer data to G's
  pos=map(ayRaw,-16384,16384,0,180);  
  pos=max(pos,0);
  pos=min(pos,180);
  if (lastval-pos>3 || pos-lastval>3)  //CHECK THIS DEGREE IN FINAL OPTIMISATION LOWER TO 4
  {
    lastval=pos;
    //Serial.print("shoulder");
    //Serial.println(pos);
    mservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
  pos1=map(a,400,610,0,180);
  pos1=max(pos1,0);
  pos1=min(pos1,180);  
  if (lval-pos1>3 || pos1-lval>3)
  {
    if (pos1-pos>=0)
    {
      //Serial.print("1case ");
      //Serial.println(pos1-pos+90);
      lval=pos1;
      myservo.write(max((pos1-pos+90),90));              // tell servo to go to position in variable 'pos'
      delay(15);
    }
    else if (pos-pos1>0)
    {
      //Serial.print("2case ");
      //Serial.println(pos1+pos-90);
      lval=pos1;
      myservo.write(max((pos1+pos-90),90));              // tell servo to go to position in variable 'pos'
      delay(15);
    }
  }
  pos2=map(b,420,620,0, 180);
  pos2=max(pos2,0);
  pos2=min(pos2,180); 
  if (lv-pos2>5 || pos2-lv>5)  //CHECK THIS DEGREE IN FINAL OPTIMISATION LOWER TO 4
  {
    lv=pos2;
    meservo.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);
  }
  bState = digitalRead(z);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (bState == HIGH) 
  {
    // turn LED on:
    digitalWrite(led,HIGH);
    nservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(15);   
   } 
  else //if (bState==LOW) 
  {
    // turn LED off:
    digitalWrite(led,LOW);
    nservo.write(80);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }      
  //Serial.println(pos2);
  delay(40);                    //CHECK THIS TOO REDUCE OR REMOVE TO STABALIZE MAX
 }
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
