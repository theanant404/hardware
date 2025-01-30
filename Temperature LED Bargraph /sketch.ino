// Reference https://docs.wokwi.com/parts/wokwi-ntc-temperature-sensor

#define sensorPin A0
#define BETA 3950

int ledArray[] = {4,5,6,7,8,9,10,11,12,13};
int size=sizeof(ledArray)/sizeof(ledArray[0]);

void setup() {
    // initialize LEDs and sensor pin
    for (int ledpin=0;ledpin<size;ledpin++){
      pinMode(ledArray[ledpin], OUTPUT);
    }
    
    Serial.begin(9600);
}

void loop() {  
  // Read the sensor value , calculate the temperature, light up the leds
  int analogValue = analogRead(sensorPin);
  int celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  int ledLevel=map(celsius,-24,80,0,9);
  for (int ledpin=0;ledpin<size;ledpin++){
    if(ledpin<=ledLevel && celsius>-24){
      digitalWrite(ledArray[ledpin], HIGH);
    }else{
      digitalWrite(ledArray[ledpin], LOW);
    }
    
  }
  
  delay(10); // this speeds up the simulation
}
