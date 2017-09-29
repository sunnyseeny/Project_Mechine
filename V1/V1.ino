#include "motorpin.h"
#include "control.h"
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); //Rx,Tx
unsigned int num[4] = {0, 0, 0, 0};
unsigned int rpm_l = 0, rpm_r = 0;
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
  static unsigned int cnt = 0;
  // put your main code here, to run repeatedly:
  if (BT.available()) {
    int Rxapp = BT.read();
    if (Rxapp >= 14) {
      if (cnt % 4 == 0) num[0] = Rxapp - 48;
      if (cnt % 4 == 1) num[1] = Rxapp - 48;
      if (cnt % 4 == 2) num[2] = Rxapp - 48;
      if (cnt % 4 == 3) num[3] = 0;
      cnt++;
    }
    if (Rxapp == 11) {
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
      Rxapp = 0;
    }
    else if (Rxapp == 12) {
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
      Rxapp = 0;
    }
    //controlCar
    if (Rxapp == 1) {
      forward();
    }
    else if (Rxapp == 2) {
      backward();
    }
    else if (Rxapp == 3) {
      left();
    }
    else if (Rxapp == 4) {
      right();
    }
    else if (Rxapp == 5) {
      QL();
    }
    else if (Rxapp == 7) {
      BER();
    }
    else if (Rxapp == 6) {
      ER();
    }
    else if (Rxapp == 8) {
      BQL();
    }
    else if (Rxapp == 9) {
      CW();
    }
    else if (Rxapp == 10) {
      CCW();
    }
    else if (Rxapp == 0){
      stopp();
    }
    Serial.print("Number= ");
    Serial.println(Rxapp);
  }

}

void left() {
  //Motor1 CCW
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, PWMA);

  //Motor2 CCW/slow
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, rpm_l);

  //Motor3 CW
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
  analogWrite(ENC, PWMC);
}

void right() {
  //Motor1 CCW/slow
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, rpm_r);

  //Motor2 CW
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, PWMB);

  //Motor3 CCW
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
  analogWrite(ENC, PWMC);
}
