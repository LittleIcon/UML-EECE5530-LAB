/* 
 *  Ernest Pellegrino
 *  April 14th 2022
 *  
 *  This code showcases 
 */
 
#define ENABLE 5
#define DIRA 3
#define DIRB 4

volatile boolean button = true;

void setup(){
  // Set pins for DC motor
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  // Setup for Button Interrupt
  pinMode(2,INPUT);
  attachInterrupt(0,buttonPressed,RISING);
  
  // Initiallize serial port  
  Serial.begin(9600);
}

//Ernie's main loop
void loop()
{  
  /*
   * Fan starts as off
   * if button is pressed fan turns on
   */

  /*
  if (digitalRead(buttonApin) == LOW)
    {
      digitalWrite(ledPin, HIGH);
    }
    if (digitalRead(buttonApin) == HIGH)
    {
      digitalWrite(ledPin, LOW);
   }
   */
  
  /* Real Time Clock Control
   *  Update the current time and retrieve the new time. 
   *  Check if the clock is at the beginning of a minute. 
   *  If so, turn the fan on and let it run for 30 seconds.
   */
  
  /* DC Motor Control
   *  Control the DC motor's rotation direction
   *  Conrol the DC motor's speed
   */

  /*
   * control_dc_motor()
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
    * Each time we press the button an intterupt will be 
    *   triggered and the interrupt service routine will change the state of "an LED".
    */
    
  /* IR Reciever/Remote Control
   *  The IR remote changes the speed and rotation direction of the fan.
   */
}

/* Functions */
// Button Press Interrupt
void buttonPressed()
{
   if(button)
   {
    digitalWrite(13,HIGH);
    //control_dc_motor(button);
    //clockwise()
    //Rotate Clockwise
    Serial.println("Clockwise, Full Speed");
    analogWrite(ENABLE,255); //enable on
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
    button = false;
   }
   else
   {
    button = true;
    digitalWrite(13,LOW);
    //control_dc_motor(button);
    //counterclockwise()
    //Rotate counter-clockwise
    Serial.println("Counterclockwise, Full Speed");
    analogWrite(ENABLE,255);
    digitalWrite(DIRA,LOW);
    digitalWrite(DIRB,HIGH);
   }
}

//Control the DC motor.
int control_dc_motor(boolean button_pressed){
  // Control the rotation direction of the motor.

   if(button_pressed)
   {
    //Rotate Clockwise
    Serial.println("Clockwise, Full Speed");
    analogWrite(ENABLE,255); //enable on
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
   }
   else
   {
    //Rotate counter-clockwise
    Serial.println("Counterclockwise, Full Speed");
    analogWrite(ENABLE,255);
    digitalWrite(DIRA,LOW);
    digitalWrite(DIRB,HIGH);
   }
  
  /*
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
  */
  return 0;
}
