
//Include Json
#include <ArduinoJson.h>
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();


//Include Serial
#include <SoftwareSerial.h>
  SoftwareSerial SharkLife(10, 11); // RX, TX

int button;
int latch=false;

void setup() {
  //x
  pinMode(A0,INPUT);
  
  //y
  pinMode(A1,INPUT);

  //b
  pinMode(9,INPUT_PULLUP);
  
  //Serial
  SharkLife.begin(9600);
  SharkLife.println("Starting up");
   
}

void loop() {
  //JoyStck
    //x
    int x = analogRead(A0);
    //y
    int y = analogRead(A1);
    x = map(x,0,1024,-10,11);
    y = map(y,0,1024,-10,11);
    
  //Button
    button=digitalRead(9);

    
  //Latch
    if(button==0)
    {
        if(latch==false){
          latch=true;
        }else if(latch==true){
          latch=false;
        }
    }

    
  //Send
    
    root["x"] = x;
    root["y"] = y;
    root["b"] = latch;
    root.printTo(SharkLife);

    
  //Test x,y
    //SharkLife.print(x);
    //SharkLife.print(" , ");
    //SharkLife.println(y);
    //Y je brzina
    //X je Skretanje
    //X=0 levo
    //X=20 Desno
  
}
