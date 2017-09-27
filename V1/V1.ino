
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
    else if(Rxapp =="FL"){
      QL();
    }
    else if(Rxapp =="BL"){
      BER();
    }
    else if(Rxapp =="FR"){
      ER();
    }
    else if(Rxapp =="BR"){
      BQL();
    }
    else if(Rxapp =="SPR"){
      CW();
    }
    else if(Rxapp =="SPL"){
      CCW();
    }
    else{
      stopp();
    }
  }

}


