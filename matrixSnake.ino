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
const char msg1[36] = "BY BX LOVE VITA! Happy Valentine!!! ";
const int msg1_size = 35;
const char msg2[35] = "BX: You are my blessing. Love you! ";
const int msg2_size = 34;
const char msg3[43] = "BY: Thanks for stepping into my life! Kiss ";
const int msg3_size = 42;

const uint8_t PROGMEM
 heart_bmp[8]=
    {
      B01100110,
      B11111111,
      B10011001,
      B10000001,
      B11000011,
      B01100110,
      B00111100,
      B00011000
    },
 smile_bmp[8] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100
  };

/* CLK -> A05
 *  DAT -> A04
 *  GND
 *  VCC 5V
 */
int leftPin = 2;
int rightPin = 3;
unsigned long lastGameUpdateTime = 0;
unsigned long lastInputUpdateTime = 0;
unsigned long currTime;

enum DisplayState{
  LOVE,
  GAME
};
DisplayState state;
bool gameStarted = false;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(leftPin), LeftInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(rightPin), RightInterrupt, FALLING);
  matrix.begin(0x70);
  state = DisplayState::LOVE;
  
}

void LeftInterrupt(){
  if(state == DisplayState::LOVE){
    state = DisplayState::GAME;
  }
  manager.PressLeft();  
}

void RightInterrupt(){
  if(state == DisplayState::LOVE){
    state = DisplayState::GAME;
  }
  manager.PressRight(); 
}

void displayText(char text[], int delayMs, const int size){
  matrix.clear();
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  for (int x=12; x>=int(-6*size); x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(text);
    matrix.writeDisplay();
    delay(delayMs);
  }
}

void DisplayImage(const uint8_t img[], int delayMs){
  matrix.clear();
  matrix.drawBitmap(0, 0, img, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(delayMs);
}

void DisplayLoveMessage() {
  DisplayImage(smile_bmp, 5000);
  if(state == DisplayState::GAME) return;
  displayText(msg1, 100, msg1_size);
  if(state == DisplayState::GAME) return;
  displayText(msg2, 100, msg2_size);
  if(state == DisplayState::GAME) return;
  displayText(msg3, 100, msg3_size);
  if(state == DisplayState::GAME) return;
  DisplayImage(heart_bmp, 5000);
}

void GameStart() {
  matrix.clear();
  manager.OnGameStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  currTime = millis();
  if(state == DisplayState::LOVE)
  {
    DisplayLoveMessage();
  }
  else if(state == DisplayState::GAME)
  {
    if(!gameStarted)
    {
      GameStart();
      gameStarted = true;
    }
    manager.Update(currTime);
  }
}
