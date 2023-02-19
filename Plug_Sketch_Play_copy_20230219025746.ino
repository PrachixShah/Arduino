#include "Arduino_SensorKit.h"
#include <Wire.h>
#include "paj7620.h"

#define GES_REACTION_TIME       500             // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME          800             // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME           1000


int button = 4;
int buzzer = 6;
int blue = 10;
int red = 11;
int yellow = 13;
int green = 12;
int state = 0;
int prev = 0;
long num = 0;
int count = 3;
int s = 0;
bool GES = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(button , INPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzzer, OUTPUT); 

  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  uint8_t error = 0;
  Serial.begin(9600);
  error = paj7620Init(); 
}

void loop() {
  int numArr[count];
  prev = state;
  state = digitalRead(button);
  // put your main code here, to run repeatedly:

  while (prev != state && state == HIGH) 
  { 
    prev = state;
    state = digitalRead(button);
    if (prev != state && state == LOW)
    {
      break;
    }
    else
    {  
      for (int i = 0; i <= count; i++)
      {
        num = random(1,5);
        if (num == 1)
        {
          numArr[i] = blue;
          Serial.print(numArr[i]);
          digitalWrite(blue, HIGH);
          delay(750);
          digitalWrite(blue, LOW);  
        }
        else if (num == 2)
        {
          numArr[i] = red;
          Serial.print(numArr[i]);
          digitalWrite(red, HIGH);
          delay(750);
          digitalWrite(red, LOW);
        }
        else if (num == 3)
        {
          numArr[i] = yellow;
          Serial.print(numArr[i]);
          digitalWrite(yellow, HIGH);
          delay(750);
          digitalWrite(yellow, LOW);
        }
        else if (num == 4)
        {
          numArr[i] = green;
          Serial.print(numArr[i]);          
          digitalWrite(green, HIGH);
          delay(750);
          digitalWrite(green, LOW);
        }        
      }
      count+=2;
    }

    

}
  uint8_t data = 0, error;

  error = paj7620ReadReg(0x43, 1, &data);   
  switch (data)                                   // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
  {
    case GES_RIGHT_FLAG:
      delay(GES_ENTRY_TIME);
      paj7620ReadReg(0x43, 1, &data);
      s = green;
      Serial.print(s);
      GES = true;
      break;
    case GES_LEFT_FLAG: 
      delay(GES_ENTRY_TIME);
      paj7620ReadReg(0x43, 1, &data);
      s = yellow;
      Serial.print(s);
      GES = true;
      break;
    case GES_UP_FLAG:
      delay(GES_ENTRY_TIME);
      paj7620ReadReg(0x43, 1, &data);
      s = red;
      Serial.print(s);
      GES = true;
      break;
    case GES_DOWN_FLAG:
      delay(GES_ENTRY_TIME);
      paj7620ReadReg(0x43, 1, &data);
      s = blue;
      Serial.print(s);
      GES = true;
      break;
  }
  delay(100);

  if (GES == true)
  {
     for (int i = 0; i <= count; i++)
    {
    if (numArr[i] != s)   
    {
      tone(buzzer, 50); // Send 1KHz sound signal...
      delay(100);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...    
      delay(500);
    } 
    }
    GES == false;
  }
 
}