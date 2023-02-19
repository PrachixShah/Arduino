#include "Arduino_SensorKit.h"

int button = 4;
int buzzer = 8;
int blue = 10;
int red = 11;
int yellow = 13;
int green = 12;
int state = 0;
int prev = 0;
long num = 0;
int count = 3;

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

}

void loop() {
  prev = state;
  state = digitalRead(button);
  // put your main code here, to run repeatedly:

  while (prev != state && state == HIGH) {
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
          digitalWrite(blue, HIGH);
          delay(750);
          digitalWrite(blue, LOW);  

        }
        else if (num == 2)
        {
          digitalWrite(red, HIGH);
          delay(750);
          digitalWrite(red, LOW);
        }
        else if (num == 3)
        {
          digitalWrite(yellow, HIGH);
          delay(750);
          digitalWrite(yellow, LOW);
        }
        else if (num == 4)
        {
          digitalWrite(green, HIGH);
          delay(750);
          digitalWrite(green, LOW);
        }        
      }
      count+=2;
    }
    // tone(buzzer, 500); // Send 1KHz sound signal...
    // delay(500);        // ...for 1 sec
    // noTone(buzzer);     // Stop sound...
    // delay(500);        // ...for 1sec
    

  }
  if (state == LOW && prev != state)
    {
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
    }
    
  

}
