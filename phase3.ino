//including all the lib needed
#include <LiquidCrystal.h>




//intialize the pins for input
const int START = 6;
const int STOP = 7;
const int RESET = 8;
const int NEW = 9;

//intialize the pins for output
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd1(12, 10, 5, 4, 3, 2);

const int RELASE = 13;

//intialize variables needed in the program
unsigned long startTime = 0;
unsigned long endTime = 0;
int  count = 0;
int  scount = 0;
char prevTime[20];
bool endCond = false;
int TEST[20][2];

//setup loop runs once in the beging of the prog.
void setup() 
{
  
  // set up the LCD
  lcd.begin(16, 2);
  lcd1.begin(16, 2);
  lcd1.print("PHYSY NASA TR#3");
  lcd1.setCursor(0,1);
  lcd1.print("TEST# 0 out of 0");
  lcd.setCursor(0, 0);
  lcd.print("TEST 0 DUR:0:000");
  lcd.setCursor(0, 1);
  lcd.print("LEAST  DUR:0:000");
  
  //set up the pins
  pinMode(START, INPUT);
  pinMode(STOP, INPUT);
  pinMode(RESET, INPUT);
  pinMode(NEW, INPUT);
  pinMode(RELASE, OUTPUT);
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  
}

//main loop 
void loop() 
{
  
  // START button condition
  if(digitalRead(START) == HIGH && digitalRead(RELASE) == LOW && count < 20)
  {
    startTime = millis();
    digitalWrite(RELASE, HIGH);
    endCond = true;
  }
  
  // STOP button condition
  if(digitalRead(STOP) == HIGH && endCond == true)
  {
    //calculating the time
    endTime = millis();
    
    //reput the realsing system in ready position
    digitalWrite(RELASE, LOW);
    
    //saving the data in vector
    TEST[count][0] = calc_sec(endTime - startTime);;
    TEST[count][1] = calc_fra(endTime - startTime);
    
    //print the time on the screen
    lcd.setCursor(11, 1);
    sprintf(prevTime, "%01d:%03d", TEST[count][0], TEST[count][1]);
    lcd.print(prevTime);
    
    //increasing the count vari (related to the previous time shows)
    count++;
    
    //prevtime cond
    if (count == 1)
    {
      scount++;
      prin(scount, count);
    }
    else 
    {
      lcd1.setCursor(14,1);
      sprintf(prevTime, "%02d", count);
      lcd1.print(prevTime);
    }
    endCond = false;
  }
  
  //RESET button condition
  
  if(digitalRead(RESET) == HIGH)
  {
    startTime = 0;
    endTime = 0;
    lcd.setCursor(11, 1);
  lcd.print("0:000");
  }
  
  //NEW button condition
  if(digitalRead(NEW) == HIGH && digitalRead(RELASE) == LOW)
  {
    lcd1.print("PHYSY NASA PROJ1");
    lcd1.setCursor(0,1);
    lcd1.print("TEST# 0 out of 0");
    lcd.setCursor(0, 0);
    lcd.print("TEST 0 DUR:0:000");
    lcd.setCursor(0, 1);
    lcd.print("LEAST  DUR:0:000");
    startTime = 0;
    endTime = 0;
    count = 0;
    sprintf(prevTime, "");
    for (int i = 0; i < 20; i++)
   {
      for (int j = 0; j < 2; j++)
      {
        TEST[i][j] = 0;
      }
    }
  }
  
  //UP button condition
  if(digitalRead(A5) == HIGH && count > 0)
  {
    if(scount < count)
    {
      scount++;
      prin(scount, count);
    }
    else
    {
      scount = 1;
      prin(scount, count);
    }
  }
  
  //Down button condition
  if(digitalRead(A4) == HIGH && count > 0)
  {
    if(scount == 1)
    {
      scount = count;
      prin(scount, count);
    }
    else
    {
      scount--;
      prin(scount, count);
    }
  }
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

//update the prev time print
void prin( int sc, int c)
{
      lcd1.setCursor(0, 1);
      sprintf(prevTime, "TEST# %01d out of %01d", sc, c);
      lcd1.print(prevTime);
      lcd.setCursor(0, 0);
      sprintf(prevTime, "TEST %01d DUR:%01d:%03d", sc, TEST[sc - 1][0], TEST[sc - 1][1]);
      lcd.print(prevTime);
      delay(100);
}
