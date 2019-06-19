//Json
#include <ArduinoJson.h>
StaticJsonBuffer<200> jsonBuffer;

//SharkLife
#include <SoftwareSerial.h>
SoftwareSerial SharkLife(10, 11); // RX, TX

//Motor
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield Motor = Adafruit_MotorShield(); 

//String
String readString;

//Motor
Adafruit_DCMotor *M1 = Motor.getMotor(1);
Adafruit_DCMotor *M2 = Motor.getMotor(2);
Adafruit_DCMotor *M3 = Motor.getMotor(3);
Adafruit_DCMotor *M4 = Motor.getMotor(4);

void setup() 
{ 

  SharkLife.begin(9600);
  Motor.begin();
  M1->setSpeed(150);
  M2->setSpeed(150);
  M3->setSpeed(150);
  M4->setSpeed(150);

  
  M1->run(FORWARD);
  M1->run(RELEASE);
  
  M2->run(FORWARD);
  M2->run(RELEASE);
  
  M3->run(FORWARD);
  M3->run(RELEASE);
  
  M4->run(FORWARD);
  M4->run(RELEASE);
}

void loop() 
{       
      
      while (SharkLife.available()){
        delay(10);
        char c = SharkLife.read();
        if (c == '}') 
        {
          readString += c; 
          break;
        }
        readString += c; 
      } 
    
      if (readString.length() >0) 
      {
        JsonObject& root = jsonBuffer.parseObject(readString);
         int y = root["y"];
         int x = root["x"];
         int b = root["b"];
         
         M1->setSpeed(150);
         M2->setSpeed(150);
         M3->setSpeed(150);
         M4->setSpeed(150);
         if(y>0)
         {
           M1->run(BACKWARD);
           M2->run(BACKWARD);
           M3->run(BACKWARD);
           M4->run(FORWARD); 
         }else if(y<0)
         {
           M1->run(FORWARD);
           M2->run(FORWARD);
           M3->run(FORWARD);
           M4->run(BACKWARD); 
         }else if(x==0 && y==0)
         {
           M1->run(RELEASE);
           M2->run(RELEASE);
           M3->run(RELEASE);
           M4->run(RELEASE); 
         }
          
         delay(1000);
         
         
         //Test x,y
         //SharkLife.print(x);
         //SharkLife.print(" , ");
         //SharkLife.println(y);
         //Y je brzina
         //X je Skretanje
         //X=0 levo
         //X=20 Desno

         
      }
    
        readString=""; //clears variable for new input
}
       

