//www.elegoo.com
//2018.10.24
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#include "IRremote.h"

#define ENABLE 5
#define DIRA 3
#define DIRB 4

int receiver = 6;

int counter = 0;
int interruptPin = 2; //For button interrupt
unsigned long lastDebounceTime = 0; //For debouncing

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

DS3231 clock;
RTCDateTime dt;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 
char time_char[16];
char speed_char[16];
unsigned int reload = 0xF424; // Value equivalento to 1 second

void setup()
{
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  //For button interrupt
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), count_up, FALLING);
  
  // Initialize DS3231
  clock.begin();

  // Send sketch compiling time to Arduino
  clock.setDateTime(__DATE__, __TIME__);    

  //LCD setup
  lcd.begin(16, 2);

  //Setup registers for interrupts
  TCCR1A = 0;
  TCCR1B = 0; 
  OCR1A = reload;
  TCCR1B = (1<<WGM12) | (1<<CS12); 
  TIMSK1 = (1<<OCIE1A); 

  irrecv.enableIRIn(); // Start the receiver

}
ISR(TIMER1_COMPA_vect)
{
  lcd.setCursor(0, 0);
  lcd.print(time_char);
  lcd.setCursor(0, 1);
  lcd.print(speed_char);
}



void loop()
{
  dt = clock.getDateTime();
  sprintf (time_char,"%0.2d:%0.2d:%0.2d",dt.hour,dt.minute,dt.second);

switch(counter)
    {
  case 0:
    analogWrite(ENABLE,255); //enable on
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
    sprintf (speed_char,"C  FULL SPEED");
    break;
  case 1:
    analogWrite(ENABLE,180); // 3/4 speed
    sprintf (speed_char,"C  3/4  SPEED");
    break;
  case 2:
    analogWrite(ENABLE,128); // 1/2 speed
    sprintf (speed_char,"C  1/2  SPEED");
    break;
  case 3:
    digitalWrite(ENABLE,LOW);
    sprintf (speed_char,"OFF            ");
    break;
  case 4:
    analogWrite(ENABLE,255); //enable on
    digitalWrite(DIRA,LOW); // the other way
    digitalWrite(DIRB,HIGH);
    sprintf (speed_char,"CC FULL SPEED");
    break;
  case 5:
    analogWrite(ENABLE,180); // 3/4 speed
    sprintf (speed_char,"CC 3/4  SPEED");
    break;
  case 6:
    analogWrite(ENABLE,128); // 1/2 speed
    sprintf (speed_char,"CC 1/2  SPEED");
    break;
  case 7:
    digitalWrite(ENABLE,LOW);
    sprintf (speed_char,"OFF            ");
    break;
  case 8:
    counter = 0;
    break;
  default:
    digitalWrite(ENABLE,LOW);
    counter = 0; 
    break;
    }// End Case

  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    switch(results.value)
    {
      case 0xFF6897: counter = 0;    break;
      case 0xFF30CF: counter = 1;    break;
      case 0xFF18E7: counter = 2;    break;
      case 0xFF7A85: counter = 3;    break;
      case 0xFF10EF: counter = 4;    break;
      case 0xFF38C7: counter = 5;    break;
      case 0xFF5AA5: counter = 6;    break;
      case 0xFF42BD: counter = 7;    break;
      default: 
        counter = 0;
        break;
    }// End Case

    delay(500); 
    irrecv.resume(); // receive the next value
  }      
  delay(100);
}

void count_up(){

  if ((millis() - lastDebounceTime) > 200) {
    counter = counter + 1;
  }
  lastDebounceTime = millis();
}
