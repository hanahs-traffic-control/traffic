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

int lastRedButtonState = 0;
int lastGreenButtonState = 0;
bool currentIsRed = 1;

SoftwareSerial bt(BT_TX_PIN, BT_RX_PIN);

void setup() {
  pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  
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
  currentIsRed = 1;
}

void greenLight() {
  analogWrite(RED_LED_PIN, 0);
  analogWrite(GREEN_LED_PIN, GREEN_PWM);
  currentIsRed = 0;
}

void loop() {
  int currentRedButtonState = digitalRead(RED_BUTTON_PIN);
  int currentGreenButtonState = digitalRead(GREEN_BUTTON_PIN);

  if (currentIsRed == 0 && currentRedButtonState == 0) {
    redLight();
  }
  
  if (currentIsRed == 1 && currentGreenButtonState == 0) {
    greenLight();
  }

  if (bt.available()) Serial.write(bt.read());
  delay(10);
}
