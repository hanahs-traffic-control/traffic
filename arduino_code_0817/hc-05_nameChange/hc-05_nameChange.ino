#include <SoftwareSerial.h>

const int BT_RX_PIN = 7;
const int BT_TX_PIN = 6;
SoftwareSerial bt(BT_TX_PIN, BT_RX_PIN);

void setup() {
  bt.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (bt.available())
    Serial.write(bt.read());
  if (Serial.available())
    bt.write(Serial.read());
}

/*
 * both NL & CR
 * 9600
 * button push to enter AT mode
 * try "at", should say "ok"
 * at+name=TFL_n
 */
