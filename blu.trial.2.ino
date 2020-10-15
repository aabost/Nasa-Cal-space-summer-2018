/**
 * PHYsy.finalStage
 * blu.trial.2
 * summer 2018
 * Cal-space NASA reasearch internship
 */
 
//intialize the pins for input
const int START = 6;
const int STOP = 7;
const int RESET = 8;
const int NEW = 9;

//intialize the pins for output
const int RELASE = 13;

//intialize variables needed in the program
unsigned long startTime = 0;
unsigned long endTime = 0;
int  count = 0;
int  scount = 0;
char prevTime[20];
bool endCond = false;
int TEST[20][2];
char rec;


int milsec1 = 0;
int milsec2 = 0;

float difsec = 0;

//setup loop runs once in the beging of the prog.
void setup() 
{
  
  
  //set up the pins
  pinMode(START, INPUT);
  pinMode(STOP, INPUT);
  pinMode(RESET, INPUT);
  pinMode(NEW, INPUT);
  pinMode(RELASE, OUTPUT);
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);

  //setup bluetooth
  Serial.begin(9600);
}

//main loop 
void loop() 
{
  if (Serial.available() > 0)
  {
    rec = Serial.read();
  }
  
  // START button condition
  if(rec == '1' && digitalRead(RELASE) == LOW && count < 20)
  {
    startTime = millis();
    digitalWrite(RELASE, HIGH);
    endCond = true;
  }
  
  // STOP button condition
  if(digitalRead(STOP) == LOW && endCond == true)
  {
    //calculating the time
    endTime = millis();
    
    //reput the realsing system in ready position
    digitalWrite(RELASE, LOW);
    
    //saving the data in vector
    TEST[count][0] = calc_sec(endTime - startTime);
    TEST[count][1] = calc_fra(endTime - startTime);
    
    //print the time on the screen
    sprintf(prevTime, "*DThe least time:%01d:%03d", TEST[count][0], TEST[count][1]);
    Serial.write(prevTime);

    //increasing the count vari (related to the previous time shows)
    count++;
    
    //prevtime cond
    if (count == 1) {scount++;}
    
    prin(scount, count);
    endCond = false;
  }
  
  //RESET button condition
  
  if(rec == '2')
  {
    startTime = 0;
    endTime = 0;
    Serial.write("*DThe least time:0:000");
  }
  
  //NEW button condition
  if(rec == '3' && digitalRead(RELASE) == LOW)
  {
    Serial.write("*CThe time of test 0: 0:000");
    Serial.write("*DThe least time: 0:000");
    Serial.write("*GThe time of test 0: 0:000");
    Serial.write("*A%Difference: 0.00%");
    startTime = 0;
    endTime = 0;
    count = 0;
    scount = 0;
    sprintf(prevTime, "");
    for (int i = 0; i < 20; i++)
   {
      for (int j = 0; j < 2; j++)
      {
        TEST[i][j] = 0;
      }
    }
  }
  
  //UP button 1 condition
  if(rec == '4' && count > 0)
  {
    if(scount < count)
    {
      scount++;
      milsec1 = (TEST[scount - 1][0] * 1000) + TEST[scount - 1][1];
      prin(scount, count);
    }
    else
    {
      scount = 1;
      milsec1 = (TEST[scount - 1][0] * 1000) + TEST[scount - 1][1];
      prin(scount, count);
    }
  }
  
  //Down button 1 condition
  if(rec == '5' && count > 0)
  {
    if(scount == 1)
    {
      scount = count;
      milsec1 = (TEST[scount - 1][0] * 1000) + TEST[scount - 1][1];
      prin(scount, count);
    }
    else
    {
      scount--;
      milsec1 = (TEST[scount - 1][0] * 1000) + TEST[scount - 1][1];
      prin(scount, count);
    }
  }
  
  //UP button 2 condition
  if(rec == '6' && count > 0)
  {
    if(scount < count)
    {
      scount++;
      milsec2 = (TEST[scount - 1][0] * 1000) + TEST[scount - 1][1];
      prinf(scount, count);
    }
    else
    {
      scount = 1;
      milsec2 = (TEST[scount - 1][0] * 1000) + TEST[scount - 1][1];
      prinf(scount, count);
    }
  }
  
  //Down button 2 condition
  if(rec == '7' && count > 0)
  {
    if(scount == 1)
    {
      scount = count;
      milsec2 = (TEST[scount - 1][0] * 1000) + TEST[scount - 1][1];
      prinf(scount, count);
    }
    else
    {
      scount--;
      milsec2 =  (TEST[scount - 1][0] * 1000) + TEST[scount - 1][1];
      prinf(scount, count);
    }
  }

  
  //%Difference calculation
  if(rec == '8')
  {
  difsec =  (abs(milsec1 - milsec2) / ((milsec1 + milsec2)/2)) * 100;
  sprintf(prevTime, "*A%Difference: %.2f%",difsec);
  Serial.write(prevTime);
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
void  prin(int sc, int c)
{
      sprintf(prevTime, "*CThe time of test %01d: %01d:%03d", sc, TEST[sc - 1][0], TEST[sc - 1][1]);
      Serial.write(prevTime);
      delay(100);
      
}

void  prinf( int sc, int c)
{
      sprintf(prevTime, "*GThe time of test %01d: %01d:%03d", sc, TEST[sc - 1][0], TEST[sc - 1][1]);
      Serial.write(prevTime);
      delay(100);
}
