#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
// The two Adafruit libraries are included in GitHub. You need to install them into your 
// Arduino IDE or go to Sketch, Include Library, Manage Libraries and install from there


// OLED display TWI address
#define OLED_ADDR   0x3C  // Found this address iwth i2c_Scanner sketch (included in git) only use if nothing is displaying. the address should be the same for both screens
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// navigation input variables
int toggleBTNpin = 7;
int encoderPinA = 6;
int encoderPinB = 5;
int encoderSigA = 0;
int lastEncoderSigA = 0;
int input = 0;
int enCountUp = 0;
int enCountDn = 0;
// menu display variables
int currSelectPos = 1;
int prevSelectPos = currSelectPos;
int currLineStart = currSelectPos*10;
int prevLineStart = prevSelectPos*10;


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

void setup() {
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  // highlight line initial draw
  display.drawLine(0, currLineStart, 0, currLineStart+6, WHITE);
  display.drawLine(1, currLineStart, 1, currLineStart+6, WHITE);
  
  // display a pixel in each corner of the screen  
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

  // display a line of text
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(5,0);
  display.print("MAIN MENU");
  // Items
  display.setCursor(5,10);
  display.print("ITEM 1");
  display.setCursor(5,20);
  display.print("ITEM 2");
  display.setCursor(5,30);
  display.print("ITEM 3");
  display.setCursor(5,40);
  display.print("ITEM 4");
  display.setCursor(5,50);
  display.print("ITEM 5");
  
  // update display with all of the above graphics
  display.display();

  pinMode(toggleBTNpin,INPUT);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  encoderSigA = digitalRead(encoderPinA);
  lastEncoderSigA = encoderSigA;
//  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  input = digitalRead(toggleBTNpin);
  encoderSigA = digitalRead(encoderPinA);
//  int encoderSigB = digitalRead(encoderPinB);
//  Serial.print("A: ");
//  Serial.println(encoderSigA);
//  Serial.print("B: ");
//  Serial.println(encoderSigB);
  

//  if(input==LOW){
//    prevSelectPos = currSelectPos;
//    currSelectPos = (currSelectPos%5)+1;
//    currLineStart = currSelectPos*10;
//    prevLineStart = prevSelectPos*10;
//    display.drawLine(0, currLineStart, 0, currLineStart+6, WHITE);
//    display.drawLine(1, currLineStart, 1, currLineStart+6, WHITE);  
//    display.drawLine(0, prevLineStart, 0, prevLineStart+6, BLACK);
//    display.drawLine(1, prevLineStart, 1, prevLineStart+6, BLACK);
//    display.display();
//    Serial.print("Current Pos");
//    Serial.println(currSelectPos);
//    Serial.print("Current Line Start");
//    Serial.println(currLineStart);
//    delay(200);
//  }
    if(input == LOW){
      display.drawRect(3, currLineStart-1, 50, 10, WHITE);
      display.drawRect(3, prevLineStart-1, 50, 10, BLACK);
      display.display();
    }

    if(encoderSigA != lastEncoderSigA){
      if(digitalRead(encoderPinB) != lastEncoderSigA){
          enCountDn ++;
//          delay(20);
//        prevSelectPos = currSelectPos;
//        currSelectPos = (currSelectPos%5)+1;
//        currLineStart = currSelectPos*10;
//        prevLineStart = prevSelectPos*10;
          if( enCountDn == 3 ){
            enCountUp = 0;
            enCountDn = 0;
            prevSelectPos = currSelectPos;
            currSelectPos = (((currSelectPos-1)+5-1)%5)+1;
            currLineStart = currSelectPos*10;
            prevLineStart = prevSelectPos*10;
            display.drawLine(0, currLineStart, 0, currLineStart+6, WHITE);
            display.drawLine(1, currLineStart, 1, currLineStart+6, WHITE);  
            display.drawLine(0, prevLineStart, 0, prevLineStart+6, BLACK);
            display.drawLine(1, prevLineStart, 1, prevLineStart+6, BLACK);
            display.drawRect(3, prevLineStart-1, 50, 10, BLACK);
            display.display();
          }
      }else{
          enCountUp ++;
//          delay(20);
//        prevSelectPos = currSelectPos;
//        currSelectPos = (((currSelectPos-1)+5-1)%5)+1;
//        currLineStart = currSelectPos*10;
//        prevLineStart = prevSelectPos*10;
//        Serial.println(currSelectPos);
          if( enCountUp == 3 ){
            enCountUp = 0;
            enCountDn = 0;
            prevSelectPos = currSelectPos;
            currSelectPos = (currSelectPos%5)+1;
            currLineStart = currSelectPos*10;
            prevLineStart = prevSelectPos*10;
            display.drawLine(0, currLineStart, 0, currLineStart+6, WHITE);
            display.drawLine(1, currLineStart, 1, currLineStart+6, WHITE);  
            display.drawLine(0, prevLineStart, 0, prevLineStart+6, BLACK);
            display.drawLine(1, prevLineStart, 1, prevLineStart+6, BLACK);
            display.drawRect(3, prevLineStart-1, 50, 10, BLACK);
            display.display();
          }
      }
    }
    
    lastEncoderSigA = encoderSigA;
}

