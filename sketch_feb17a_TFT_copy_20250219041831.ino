#include "TFT_eSPI.h"
#define encS1 18 
#define encS2 19

TFT_eSPI tft = TFT_eSPI();
//TFT_eSprite circle = TFT_eSprite(&tft);


int current = 0;
int xTemp;
int x = 60;
bool curMult = true;
float xRad;
int circlePosX;
int circlePosY;
int circlePrevX;
int circlePrevY;
int curs1, curs2;
int prevS1;
bool encFlag = true;


void drawCircleOnCur(int x, bool toLow) {
  if (toLow){
    xRad = radians(x + 1);
    circlePosY = 120 + (100 * sin(xRad));
    circlePosX = 120 + (100 * cos(xRad));
    tft.fillCircle(circlePosX, circlePosY, 20, TFT_BLACK);
  }
    xRad = radians(x);
    circlePosY = 120 + (100 * sin(xRad));
    circlePosX = 120 + (100 * cos(xRad));
    tft.fillCircle(circlePosX, circlePosY, 20, TFT_RED);
}


void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  pinMode(encS1, INPUT);
  pinMode(encS2, INPUT);
  prevS1 = digitalRead(encS1);
  Serial.begin(115200);
}


void loop() {

  curs1 = digitalRead(encS1);

  if (curs1 != prevS1){
    curs2 = digitalRead(encS2);
    if(encFlag){
    if (curs1 == curs2){
      current--;
    }else{
      current++;
    }
    prevS1 = curs1;
    encFlag = !encFlag;
    Serial.println(current);
    }else{
      encFlag = !encFlag;
    }
  }



 // if (xTemp == x){
  //  current = Serial.parseInt();
  //}
  current = constrain(current, 0, 100);
  xTemp = map(current, 0, 100, 60, 300);
  if(xTemp > x){
    x = x + 1;
    drawCircleOnCur(x, false);
  }else if(xTemp < x){
    x = x - 1;
    drawCircleOnCur(x, true);
  }
}



