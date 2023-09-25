#include <stdlib.h>
#include <PS2X_lib.h>   
PS2X ps2x; 

#define m1pin1 6
#define m1pin2 5
#define m1pwm 7

#define m2pin1 4
#define m2pin2 3
#define m2pwm 2

int psclock=8;
int pscommand=11;
int psattention=10;
int psdata=9;

int error=0;
byte type=0;

int m1speed=100;
int m2speed=110;

void setup() 
{
  pinMode(m1pwm, OUTPUT);
  pinMode(m1pin1, OUTPUT);
  pinMode(m1pin2, OUTPUT);
    
  pinMode(m2pwm, OUTPUT);
  pinMode(m2pin1, OUTPUT);
  pinMode(m2pin2, OUTPUT);

  Serial.begin(57600);
 
  error=ps2x.config_gamepad(psclock,pscommand,psattention,psdata, true, true);   //GamePad(clock, command, attention, data, Pressures?, Rumble?) 
  if(error==0)
    Serial.println("Found Controller, configured successful");
  
  type=ps2x.readType();
  if(type==1)
    Serial.println("DualShock Controller Found");
}

void loop() 
{
  ps2x.read_gamepad();  
  if(ps2x.Button(PSB_PAD_UP))
  {
      digitalWrite(m2pin1,HIGH);
      digitalWrite(m2pin2,LOW);
      analogWrite(m2pwm,m2speed);
      
      digitalWrite(m1pin1,LOW);
      digitalWrite(m1pin2,HIGH);
      analogWrite(m1pwm,m1speed);
      Serial.println("Going Front");
  }     
  else if(ps2x.Button(PSB_PAD_DOWN))
  {
      digitalWrite(m2pin2,HIGH);
      digitalWrite(m2pin1,LOW);
      analogWrite(m2pwm,m2speed);
      
      digitalWrite(m1pin2,LOW);
      digitalWrite(m1pin1,HIGH);
      analogWrite(m1pwm,m1speed);
      Serial.println("Going Back");
  }
  else if(ps2x.Button(PSB_PAD_RIGHT))
  {
      digitalWrite(m2pin2,LOW);
      digitalWrite(m2pin1,HIGH);
      analogWrite(m2pwm,m2speed);
      
      digitalWrite(m1pin2,LOW);
      digitalWrite(m1pin1,HIGH);
      analogWrite(m1pwm,m1speed);
      Serial.println("Rotating Clockwise");
  }
  else if(ps2x.Button(PSB_PAD_LEFT))
  {
      digitalWrite(m2pin2,HIGH);
      digitalWrite(m2pin1,LOW);
      analogWrite(m2pwm,m2speed);
      
      digitalWrite(m1pin2,HIGH);
      digitalWrite(m1pin1,LOW);
      analogWrite(m1pwm,m1speed); 
      Serial.println("Rotating Anti Clockwise");
  }
   else
    {
      digitalWrite(m2pin1,HIGH);
      digitalWrite(m2pin2,HIGH);

      digitalWrite(m1pin1,HIGH);
      digitalWrite(m1pin2,HIGH);
      

      Serial.println("stop");
    }
  delay(50);
}
