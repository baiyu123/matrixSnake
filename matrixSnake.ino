#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "TimingEventManager.h"
#include "GameManager.h"
extern Adafruit_8x8matrix matrix;
extern GameManager manager;
extern unsigned long gameUpdateIntval;

/* CLK -> A05
 *  DAT -> A04
 *  GND
 *  VCC 5V
 */
int leftPin = 2;
int rightPin = 3;
unsigned long lastGameUpdateTime = 0;
unsigned long lastInputUpdateTime = 0;
extern unsigned long gameUpdateIntval; 
unsigned long currTime;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  matrix.begin(0x70);
  manager.OnGameStart();
}

void processInput(){
  if(!digitalRead(leftPin)){
    manager.PressLeft();  
  }
  if(!digitalRead(rightPin)){
    manager.PressRight(); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  processInput();
  currTime = millis();
  // matrix.clear();
  // matrix.drawBitmap(0, 0, heart_bmp, 8, 8, LED_ON);
  // matrix.writeDisplay();
  // delay(500);

  if((currTime - lastGameUpdateTime) > gameUpdateIntval){
    manager.Update();
    lastGameUpdateTime = currTime;
  }
  TimingEventManager::getInstance();
}
