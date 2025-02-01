#define g_ledpin 13
#define y_ledpin 12
#define r_ledpin 11

void setup() {
    pinMode(g_ledpin, OUTPUT);
    pinMode(y_ledpin, OUTPUT);
    pinMode(r_ledpin, OUTPUT);
}

void loop() {
  digitalWrite(g_ledpin, HIGH);
  digitalWrite(y_ledpin, LOW);
  digitalWrite(r_ledpin, LOW);
  delay(1000);
  digitalWrite(g_ledpin, LOW);
  digitalWrite(y_ledpin, HIGH);
  digitalWrite(r_ledpin, LOW);
  delay(200);
  digitalWrite(g_ledpin, LOW);
  digitalWrite(y_ledpin, LOW);
  digitalWrite(r_ledpin, HIGH);
  delay(1000);
  

}
