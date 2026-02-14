#include <SoftwareSerial.h>

const int stretchPin = A0;
const int buzzerPin = 2;
SoftwareSerial bluetooth(10, 11); // RX, TX

int baseline = 0;
int apneaThreshold = 10;
unsigned long lastBreathTime = 0;
unsigned long apneaDelay = 8000;
unsigned long flatLineStartTime = 0;
const unsigned long maxFlatTime = 30000;
bool alertTriggered = false;

int breathCount = 0;
const int activationBreathCount = 3;
bool monitoringStarted = false;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  
  // Baseline calibration
  long total = 0;
  for (int i = 0; i < 100; i++) {
    total += analogRead(stretchPin);
    delay(10);
  }
  baseline = total / 100;
  
  Serial.print("Baseline: ");
  Serial.println(baseline);
  bluetooth.print("Baseline: ");
  bluetooth.println(baseline);
}

void loop() {
  int value = analogRead(stretchPin);
  int delta = abs(value - baseline);
  
  Serial.print("Breath delta: ");
  Serial.println(delta);
  bluetooth.print("Breath delta: ");
  bluetooth.println(delta);
  
  if (!monitoringStarted) {
    if (delta > apneaThreshold) {
      breathCount++;
      if (breathCount >= activationBreathCount) {
        monitoringStarted = true;
        lastBreathTime = millis();
        Serial.println("✅ Monitoring started.");
        bluetooth.println("✅ Monitoring started.");
      }
    } else {
      bluetooth.println("🕓 Waiting for breathing activity...");
    }
  } 
  else {
    if (delta > apneaThreshold) {
      lastBreathTime = millis();
      flatLineStartTime = 0;
      alertTriggered = false;  // Reset alert for next apnea event
    } 
    else {
      if (flatLineStartTime == 0) {
        flatLineStartTime = millis();
      }
      
      if (millis() - flatLineStartTime > maxFlatTime) {
        Serial.println("🛑 Device removed — deactivating.");
        bluetooth.println("🛑 Device removed — deactivating.");
        monitoringStarted = false;
        breathCount = 0;
        flatLineStartTime = 0;
        alertTriggered = false;
        return;
      }
    }
    
    if ((millis() - lastBreathTime > apneaDelay) && !alertTriggered) {
      Serial.println("🚨 Apnoea detected!");
      bluetooth.println("🚨 Apnoea detected!");
      
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      
      alertTriggered = true;
    }
  }
  
  delay(250);
}
