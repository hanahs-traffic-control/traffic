#include <SoftwareSerial.h>

const int RED_BUTTON_PIN = 3;
const int GREEN_BUTTON_PIN = 4;
const int RED_LED_PIN = 11;
const int YELLOW_LED_PIN = 10;
const int GREEN_LED_PIN = 9;
const int BT_RX_PIN = 7;
const int BT_TX_PIN = 6;

const int RED_PWM = 20;
const int YELLOW_PWM = 50;
const int GREEN_PWM = 5;

int lastRedButtonState = 0;
int lastGreenButtonState = 0;
bool currentIsRed = true;

SoftwareSerial bt(BT_TX_PIN, BT_RX_PIN);

void setup() {
  pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);
  analogWrite(RED_LED_PIN, RED_PWM);
  bt.begin(9600);
  Serial.begin(9600);
}

void loop() {
  int currentRedButtonState = digitalRead(RED_BUTTON_PIN);
  int currentGreenButtonState = digitalRead(GREEN_BUTTON_PIN);
  if (currentRedButtonState == HIGH && lastRedButtonState == HIGH) return;
  else if (currentGreenButtonState == HIGH && lastGreenButtonState == HIGH) return;

  if (currentRedButtonState - lastRedButtonState == 1 && !currentIsRed) {
    analogWrite(GREEN_LED_PIN, 0);
    analogWrite(YELLOW_LED_PIN, YELLOW_PWM);
    delay(1000);
    analogWrite(YELLOW_LED_PIN, 0);
    analogWrite(RED_LED_PIN, RED_PWM);
    currentIsRed = true;
  } else if (currentGreenButtonState - lastGreenButtonState == 1 && currentIsRed) {
    analogWrite(RED_LED_PIN, 0);
    analogWrite(GREEN_LED_PIN, GREEN_PWM);
    currentIsRed = false;
  }

  if (bt.available()) Serial.write(bt.read());

  lastRedButtonState = currentRedButtonState;
  lastGreenButtonState = currentGreenButtonState;
  delay(10);
}
