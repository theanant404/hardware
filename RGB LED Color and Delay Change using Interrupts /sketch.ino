#define colorBtn 6     
#define durationBtn 7  
#define redPin 13      
#define greenPin 12    
#define bluePin 11    

// Button debounce variables
unsigned long btnPrevDebouncedely;
bool btnStatedely, btnReadingdely;
bool btnValuedely, btnPrevValuedely;
int delaysIndex = 0;

// Color change debounce variables
unsigned long btnPrevDebouncecolor;
bool btnStatecolor, btnReadingcolor;
bool btnValuecolor, btnPrevValuecolor;
int colorsIndex = 0;


bool colors[][3] = {
  {1,1,1} , {1,0,0},{0,1,0},{0,0,1},  // wrgb
  {0,1,1} , {1,1,0},{1,0,1},{0,0,0} // cymk
};
char* colorNames[] = {
  "white","red","green","blue",
  "cyan","yellow","megenta","black" // black is just off so do not need to toggle to black
};
int delays[] = {
  1000, 800, 600, 400, 200
};
unsigned long previousMillis = 0;
bool ledState = false; 
int currentDelayTime = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(durationBtn, INPUT_PULLUP);
  pinMode(colorBtn, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initial color and duration
  Serial.print("Color: ");
  Serial.println(colorNames[colorsIndex]);
  Serial.print("Duration: ");
  Serial.print(delays[delaysIndex]);
  Serial.println(" ms");

  // Set initial LED state (Off)
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void loop() {

  handleColorButton();
  handleDurationButton();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= currentDelayTime) {
    previousMillis = currentMillis;
    ledState = !ledState;
    updateLED(ledState);
  }
}

void handleColorButton() {
  btnReadingcolor = digitalRead(colorBtn) == LOW;
  if (btnReadingcolor != btnStatecolor) {
    btnPrevDebouncecolor = millis();
    btnStatecolor = btnReadingcolor;
  }
  if ((millis() - btnPrevDebouncecolor) > 50) {
    if (btnValuecolor != btnStatecolor) {
      btnPrevValuecolor = btnValuecolor;
      btnValuecolor = btnStatecolor;
      if (btnValuecolor && !btnPrevValuecolor) {
        colorsIndex = (colorsIndex + 1) % 8; 
        Serial.print("Color: ");
        Serial.println(colorNames[colorsIndex]);
        Serial.print("Duration: ");
        Serial.print(currentDelayTime);
        Serial.println(" ms");
        updateLED(ledState);
      }
    }
  }
}

void handleDurationButton() {
  btnReadingdely = digitalRead(durationBtn) == LOW;
  if (btnReadingdely != btnStatedely) {
    btnPrevDebouncedely = millis();
    btnStatedely = btnReadingdely;
  }
  if ((millis() - btnPrevDebouncedely) > 50) {
    if (btnValuedely != btnStatedely) {
      btnPrevValuedely = btnValuedely;
      btnValuedely = btnStatedely;
      if (btnValuedely && !btnPrevValuedely) {
        delaysIndex = (delaysIndex + 1) % 5;  
        currentDelayTime = delays[delaysIndex];  
        Serial.print("Color: ");
        Serial.println(colorNames[colorsIndex]);
        Serial.print("Duration: ");
        Serial.print(currentDelayTime);
        Serial.println(" ms");
      }
    }
  }
}

void updateLED(bool state) {
  digitalWrite(redPin, state ? colors[colorsIndex][0] : LOW);
  digitalWrite(greenPin, state ? colors[colorsIndex][1] : LOW);
  digitalWrite(bluePin, state ? colors[colorsIndex][2] : LOW);
}
