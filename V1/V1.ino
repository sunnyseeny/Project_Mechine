#include "motorpin.h"
#include "control.h"
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); //Rx,Tx

byte num[4] = {0, 0, 0, 0};

void setup() {
  Serial.begin(38400);
  Serial.println("start");
  
  //Motor
  for(int i=2;i<=7;i++){
     pinMode(i, OUTPUT);
  }
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENC, OUTPUT);

  //Bluetooth
  BT.begin(38400);

}

void loop() {
  static byte cnt = 0;
  // put your main code here, to run repeatedly:
  if (BT.available()) {
   // int Rxapp = BT.read();
    if (BT.read() >= 14) {
      if (cnt % 4 == 0) num[0] = BT.read() - 48;
      if (cnt % 4 == 1) num[1] = BT.read() - 48;
      if (cnt % 4 == 2) num[2] = BT.read() - 48;
      if (cnt % 4 == 3) num[3] = 0;
      cnt++;
    }
    if (BT.read() == 11) {
      if (cnt == 3) {
        rpm_l = num[0] * 100 + num[1] * 10 + num[2];
        Serial.print("rpm_l= ");
        Serial.println(rpm_l);
      }
      if (cnt == 2) {
        rpm_l = num[0] * 10 + num[1];
        Serial.print("rpm_l= ");
        Serial.println(rpm_l);
      }
      if (cnt == 1) {
        rpm_l = num[0];
        Serial.print("rpm_l= ");
        Serial.println(rpm_l);
      }
      cnt = 0;
    }
    else if (BT.read() == 12) {
      if (cnt == 3) {
        rpm_r = num[0] * 100 + num[1] * 10 + num[2];
        Serial.print("rpm_r= ");
        Serial.println(rpm_r);
      }
      if (cnt == 2) {
        rpm_r = num[0] * 10 + num[1];
        Serial.print("rpm_r= ");
        Serial.println(rpm_r);
      }
      if (cnt == 1) {
        rpm_r = num[0];
        Serial.print("rpm_r= ");
        Serial.println(rpm_r);
      }
      cnt = 0;
    }
    //controlCar
    if (BT.read() == 1) {
      forward();
    }
    else if (BT.read() == 2) {
      backward();
    }
    else if (BT.read() == 3) {
      left();
    }
    else if (BT.read() == 4) {
      right();
    }
    else if (BT.read() == 5) {
      QL();
    }
    else if (BT.read() == 7) {
      BER();
    }
    else if (BT.read() == 6) {
      ER();
    }
    else if (BT.read() == 8) {
      BQL();
    }
    else if (BT.read() == 9) {
      CW();
    }
    else if (BT.read() == 10) {
      CCW();
    }
    else {
      stopp();
    }
    Serial.print("Number= ");
    Serial.println(BT.read());
  }

}
