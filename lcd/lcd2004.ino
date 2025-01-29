#include <LiquidCrystal.h>
#include <Servo.h>

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
const int servoPin = 6;
const int voltageLedPin = 5;  // LED for voltage control
const int loadLedPin = 4;     // LED for load control

Servo myServo;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int potPin1 = A0;
int potPin2 = A1;
int potPin3 = A2;

void setup() {
  lcd.begin(20, 4);
  lcd.print("Potentiometer:");
  myServo.attach(servoPin);
  pinMode(voltageLedPin, OUTPUT);  // Set the voltage LED pin as output
  pinMode(loadLedPin, OUTPUT);     // Set the load LED pin as output
  Serial.begin(9600);
}

void loop() {
  // Reading the first potentiometer for servo control
  int servoValue = analogRead(potPin1);
  int angle = map(servoValue, 0, 1023, 0, 180);
  myServo.write(angle);

  // Display angle on LCD
  lcd.setCursor(0, 1);
  lcd.print("1st: ");
  lcd.print(angle);
  lcd.print(" deg");

  // Reading the second potentiometer for voltage control of LED brightness
  int sensorValue2 = analogRead(potPin2);
  float voltage = sensorValue2 * (5.0 / 1023.0);

  // Control LED brightness based on the second potentiometer voltage
  int ledBrightness = map(sensorValue2, 0, 1023, 0, 255);
  analogWrite(voltageLedPin, ledBrightness);

  // Display voltage on LCD
  lcd.setCursor(0, 2);
  lcd.print("2nd: ");
  lcd.print(voltage);
  lcd.print(" V");

  // Reading the third potentiometer for load status
  int sensorValue3 = analogRead(potPin3);
  String loadStatus = (sensorValue3 > 512) ? "HIGH" : "LOW ";

  // Control the load LED based on the load status
  if (loadStatus == "HIGH") {
    digitalWrite(loadLedPin, HIGH);  // Turn on the load LED
  } else {
    digitalWrite(loadLedPin, LOW);   // Turn off the load LED
  }

  // Display load status on LCD
  lcd.setCursor(0, 3);
  lcd.print("3rd: ");
  lcd.print(loadStatus);
}
