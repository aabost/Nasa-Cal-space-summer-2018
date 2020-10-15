//including all the lib needed
#include <LiquidCrystal.h>




//intialize the pins for input
const int START = 6;
const int STOP = 7;
const int RESET = 8;
const int NEW = 9;

//intialize the pins for output
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int RELASE = 13;

//intialize variables needed in the program
unsigned long startTime = 0;
unsigned long endTime = 0;
int  prevSec = 0, prevFra = 0;
char prevTime[7];
bool endCond = false;
void setup() 
{
  
  // set up the LCD
  lcd.begin(16, 2);
  lcd.print("Cycloids PRO Ph2");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("PREV TIME:00:000");
  lcd.setCursor(0, 1);
  lcd.print("EXP TIME: 00:000");
  //set up the pins
  pinMode(START, INPUT);
  pinMode(STOP, INPUT);
  pinMode(RESET, INPUT);
  pinMode(NEW, INPUT);
  pinMode(RELASE, OUTPUT);
  
}

void loop() 
{
  // START button condition
  if(digitalRead(START) == HIGH)
  {
    startTime = millis();
    digitalWrite(RELASE, HIGH);
    endCond = true;
  }
  
  // STOP button condition
  
  if(digitalRead(STOP) == HIGH && endCond)
  {
    endTime = millis();
    digitalWrite(RELASE, LOW);
    prevSec = calc_sec(endTime - startTime);
    prevFra = calc_fra(endTime - startTime);
    lcd.setCursor(10, 1);
    sprintf(prevTime, "%02d:%03d", prevSec, prevFra);
    lcd.print(prevTime);
    endCond = false;
  }
  
  //RESET button condition
  
  if(digitalRead(RESET) == HIGH)
  {
    lcd.setCursor(10, 0);
    lcd.print(prevTime);
    startTime = 0;
    endTime = 0;
    lcd.setCursor(10, 1);
  lcd.print("00:000");
  }
  if(digitalRead(NEW) == HIGH && digitalRead(RELASE) == LOW)
  {
    lcd.setCursor(0, 0);
    lcd.print("PREV TIME:00:000");
    lcd.setCursor(0, 1);
    lcd.print("EXP TIME: 00:000");
    startTime = 0;
    endTime = 0;
    prevSec = 0;
    prevFra = 0;
    sprintf(prevTime, "");
  }
  delay(10);
}
 
// @param t_milli time in milliseconds
// @return int seconds
  
int calc_sec(unsigned long t_milli)
{
   unsigned long inttime;
   inttime  = t_milli / 1000;
   inttime  = inttime % (24*3600);
   inttime  = inttime % 3600;

   return inttime % 60;
}
  
int calc_fra(unsigned long t_milli)
{
   return t_milli % 1000;
}
