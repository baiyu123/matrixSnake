#include <ArduinoSTL.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "snake.h"
#include "food.h"
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
/* CLK -> A05
 *  DAT -> A04
 *  GND
 *  VCC 5V
 */
int leftPin = 2;
int rightPin = 3;
bool leftPressed = false;
bool rightPressed = false;
bool firstTime = true;
unsigned long lastTime = 0;
unsigned long currTime;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  matrix.begin(0x70);
  
}
static uint8_t
test[] = {
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100
  };

static snake s(1, 1, 0, 1);
static food f;

void processInput(){
    if(digitalRead(leftPin)){
      leftPressed = true;  
    }
    if(digitalRead(rightPin)){
      rightPressed = true;  
    }
}

void clearInput(){
    leftPressed = false;
    rightPressed = false;  
}

void update(){
  if(leftPressed){
    s.turnLeft();  
  }
  if(rightPressed){
    s.turnRight();  
  }
  std::pair<int, int> head = s.getHead();
  if(f.checkEat(head)){
    s.moveAndGrow();
    s.getMapBinary(test); 
    f.generateFood(test);
  }
  else{
    s.move();
    s.getMapBinary(test); 
  }
  //first time run the program initilize food
  if(firstTime){
    f.generateFood(test);  
    firstTime = false;
  }
  f.drawLastFood(test);
  matrix.clear();
  matrix.drawBitmap(0, 0, test, 8, 8, LED_ON);
  matrix.writeDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
  processInput();
  currTime = millis();
  if((currTime - lastTime) > 500){
    update();
    clearInput();
    lastTime = currTime;
  }
}
