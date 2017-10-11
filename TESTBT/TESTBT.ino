#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); //Rx,Tx
byte num[4] = {0, 0, 0, 0};
void setup() {
  Serial.begin(9600);
  Serial.println("start");
  BT.begin(9600);
}

void loop() {
  static byte cnt = 0;
  if (BT.available()) {
    int x = BT.read();
    if (x >= 14) {
      if (cnt % 4 == 0) num[0] = x - 48;
      if (cnt % 4 == 1) num[1] = x - 48;
      if (cnt % 4 == 2) num[2] = x - 48;
      if (cnt % 4 == 3) num[3] = 0;
      cnt++;
    }
    if (x == 11) {
      if (cnt == 3) {
        byte rpml = num[0] * 100 + num[1] * 10 + num[2];
        Serial.print("rpml= ");
        Serial.println(rpml);
      }
      if (cnt == 2) {
        byte rpml = num[0] * 10 + num[1];
        Serial.print("rpml= ");
        Serial.println(rpml);
      }
      if (cnt == 1) {
        byte rpml = num[0];
        Serial.print("rpml= ");
        Serial.println(rpml);
      }
      cnt = 0;
      x = 0;
    }
    else if (x == 12) {
      if (cnt == 3) {
        byte rpmr = num[0] * 100 + num[1] * 10 + num[2];
        Serial.print("rpmr= ");
        Serial.println(rpmr);
      }
      if (cnt == 2) {
        byte rpmr = num[0] * 10 + num[1];
        Serial.print("rpmr= ");
        Serial.println(rpmr);
      }
      if (cnt == 1) {
        byte rpmr = num[0];
        Serial.print("rpml= ");
        Serial.println(rpmr);
      }
      cnt = 0;
      x = 0;
    }
    Serial.print("Number= ");
    Serial.println(x);
  }

}
