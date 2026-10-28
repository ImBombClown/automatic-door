// C++ code
//
#include <Servo.h>

const int trig = 5;
const int echo = 6;
const int servo_pin = 9;
Servo my_servo;
unsigned long duration;
unsigned long open_time = 0;
float distance;
const float safe_open = 30;
const float safe_close = 35;
char value = 'c';
char old = 'c';
void setup()
{
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  my_servo.attach(servo_pin);
  my_servo.write(0);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
}

void loop()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH,30000UL);
  distance = duration*0.0343/2;
  Serial.print("khoang cach: ");
  Serial.println(distance);
  if(distance == 0){
    Serial.println("Not receive value");
    delay(60);
    return;
  }

  if (old == 'c' ){
    if (distance<safe_open){
      value = 'o';}
    else{value = 'c';}
    
    }
  else{
    if(distance>safe_close){
      value = 'c';
    }
    else{value = 'o';}
  }
 
   if (value == 'o' ){
      my_servo.write(90);
      open_time = millis();
     old = 'o';
    }
    else if (value == 'c' && old == 'o' && millis() - open_time >=2000){
      my_servo.write(0);
    old = 'c';}
    delay(60);
  }

