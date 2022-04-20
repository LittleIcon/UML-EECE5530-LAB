#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>
#define ENABLE 5
#define DIRA 3
#define DIRB 4

DS3231 clock;
RTCDateTime dt;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 
char time_char[16];
unsigned int reload = 0xF424; // Value equivalento to 1 second

void setup()
{
  Serial.begin(9600);

  Serial.println("Initialize RTC module");
  // Initialize DS3231
  clock.begin();

  // Send sketch compiling time to Arduino
  clock.setDateTime(__DATE__, __TIME__);    

  //LCD setup
  lcd.begin(16, 2);

  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);

//Setup registers for interrupts
TCCR1A = 0;
TCCR1B = 0; 
OCR1A = reload;
TCCR1B = (1<<WGM12) | (1<<CS12); 
TIMSK1 = (1<<OCIE1A); 
  
}
ISR(TIMER1_COMPA_vect)
{
  lcd.setCursor(0, 0);
  lcd.print(time_char);
}

// Program Loop
void loop()
{
  dt = clock.getDateTime();
  sprintf (time_char,"%0.2d:%0.2d:%0.2d",dt.hour,dt.minute,dt.second);

  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");

  delay(500);
}

/* Functions */
//Control the DC motor.
void control_dc_motor(){
  // Control the rotation direction of the motor.
  if (){
    //Rotate Clockwise
    digitalWrite(DIRA,HIGH);
    digitalWrite(DIRB,LOW);
  }
  else if(){
    //Rotate counter-clockwise
    digitalWrite(DIRA,LOW);
    digitalWrite(DIRB,HIGH);
  }
  
  // Run the DC motor at specified speeds
  if (){
    analogWrite(ENABLE,255); //"Full" Speed
  }
  else if(){
    analogWrite(ENABLE,191); //"3/4" Speed
  }
  else if(){
  analogWrite(ENABLE,127); //"1/2" Speed
  }
  else if(){
    analogWrite(ENABLE,0); // "0" Speed
  }
}

//Ernie's main loop
void main()
{
  /* Real Time Clock Control
   *  Update the current time and retrieve the new time. 
   *  Check if the clock is at the beginning of a minute. 
   *  If so, turn the fan on and let it run for 30 seconds.
   */
  
  /* DC Motor Control
   *  Control the DC motor's rotation direction
   *  Conrol the DC motor's speed
   */

  /* LCD Control
   * Display the current time.
   * Display the current fan rotation direction.
   * Display the current fan speed.
   * The display should always be on, even when the fan is not rotating.
   */

  /* Setup for Timer Interrupt
   * Use the Interrupt Service routine (ISR)
   * Update the clock, rpm and direction information every second.
   */

   /* Setup an ISR for Button Press
    * Use the Interrupt Service routine (ISR) 
    * Detect and respond to the button press
    * When the button is pressed, the fan's rotation direction is switched.
    */
    
  /* IR Reciever/Remote Control
   *  The IR remote changes the speed and rotation direction of the fan.
   */

  
}
