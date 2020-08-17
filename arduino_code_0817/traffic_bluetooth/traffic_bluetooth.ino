#include <SoftwareSerial.h>

const int RED_BUTTON_PIN = 2;
const int GREEN_BUTTON_PIN = 4;
const int RED_LED_PIN = 11;
const int YELLOW_LED_PIN = 10;
const int GREEN_LED_PIN = 9;
const int BT_RX_PIN = 7;
const int BT_TX_PIN = 6;

const int RED_PWM = 20;
const int YELLOW_PWM = 200;
const int GREEN_PWM = 50;

bool currentIsRed = true;

SoftwareSerial bt(BT_TX_PIN, BT_RX_PIN);

void setup() {
  analogWrite(RED_LED_PIN, RED_PWM);
  bt.begin(9600);
  Serial.begin(9600);
}

void redLight() {
  analogWrite(GREEN_LED_PIN, 0);
  analogWrite(YELLOW_LED_PIN, YELLOW_PWM);
  delay(1000);
  analogWrite(YELLOW_LED_PIN, 0);
  analogWrite(RED_LED_PIN, RED_PWM);
  currentIsRed = true;
}

void greenLight() {
  analogWrite(RED_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, GREEN_PWM);
  currentIsRed = false;
}

void loop() {
  if (bt.available()) {
    char cmd = bt.read();
    if (cmd == 'r' && !currentIsRed) redLight();
    else if (cmd == 'g' && currentIsRed) greenLight();
    else {
      Serial.print("Invalid command: ");
      Serial.println(cmd);
    }
  }
  delay(10);
}
