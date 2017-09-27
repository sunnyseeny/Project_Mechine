
#include "motorpin.h"
#include "control.h"
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); //Rx,Tx
//int Rxapp = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("start");

  //Motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENC, OUTPUT);

  //Bluetooth
  BT.begin(9600);

}

void loop() {
  
  // put your main code here, to run repeatedly:
  if (BT.available()) {
    
    char Rxapp = BT.read();
    if(Rxapp=='F'){
      forward();
    }
    else if(Rxapp =='B'){
      backward();
    }
    else if(Rxapp =='L'){
      left();
    }
    else if(Rxapp =='R'){
      right();
    }
    else if(Rxapp =='Z'){
      QL();
    }
    else if(Rxapp =='C'){
      BER();
    }
    else if(Rxapp =='X'){
      ER();
    }
    else if(Rxapp =='V'){
      BQL();
    }
    else if(Rxapp =='S'){
      CW();
    }
    else if(Rxapp =='A'){
      CCW();
    }
    else if(Rxapp =='P'){
      stopp();
    }
  }

}


