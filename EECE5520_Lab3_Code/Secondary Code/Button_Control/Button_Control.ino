/* 
 *  Ernest Pellegrino
 *  April 15th 2022
 *  
 *  Button Control
 */

/*
 * Generally, an ISR should be as short and fast as possible. 
 * If your sketch uses multiple ISRs, only one can run at a time. 
 * Other interrupts will be executed after the current one finishes 
 * in an order that depends on the priority they have.
 */

#define ENABLE 5
#define DIRA 3
#define DIRB 4

const int buttonPin = 2;
boolean buttonState = LOW;
volatile int counter = 0;

/*-----( Function )-----*/
void buttonPressed()
{
  if(debounceButton(buttonState) == HIGH && buttonState == LOW)
  {
    // Contact bounce issue should be solved.
    switch(counter)
    {
      case 0:
        counter += 1;
        digitalWrite(DIRA,HIGH); //Rotate Clockwise
        digitalWrite(DIRB,LOW);
  
        Serial.println("");
        Serial.println("Rotation: None");
        Serial.println("Speed: 0");
        analogWrite(ENABLE,0); // "0" Speed
      break;
  
      case 1:
        counter += 1;
        Serial.println("Rotatation: Clockwise");
        Serial.println("Speed: 1/2");
        analogWrite(ENABLE,127); //"1/2" Speed
      break;
      
      case 2:
        counter += 1;
        Serial.println("Rotatation: Clockwise");
        Serial.println("Speed: 3/4");
        analogWrite(ENABLE,191); //"3/4" Speed
      break;
      
      case 3:
        counter += 1;
        Serial.println("Rotatation: Clockwise:");
        Serial.println("Speed: Full");
        analogWrite(ENABLE,255); //"Full" Speed
      break;
      
      case 4:
        counter += 1;
        digitalWrite(DIRA,LOW); //Rotate Counter-clockwise
        digitalWrite(DIRB,HIGH);
  
        Serial.println("");
        Serial.println("Rotatation: Counter-clockwise");
        Serial.println("Speed: Full");
        analogWrite(ENABLE,255); //"Full" Speed
      break;
  
      case 5:
        counter += 1;
        Serial.println("Rotatation: Counter-clockwise");
        Serial.println("Speed: 3/4");
        analogWrite(ENABLE,191); //"3/4" Speed
      break;
  
      case 6:
        counter += 1;
        Serial.println("Rotatation: Counter-clockwise");
        Serial.println("Speed: 1/2");
        analogWrite(ENABLE,127); //"1/2" Speed
      break;
  
      case 7:
        counter = 0;
        digitalWrite(DIRA,LOW); //Rotate Clockwise
        digitalWrite(DIRB,LOW);
        
        Serial.println("Rotatation: None");
        Serial.println("Speed: 0");
        analogWrite(ENABLE,0); // "0" Speed
        Serial.println("");
      break;
  
      default: 
        Serial.println("!!  Error  !!");
    }// End Case
  }
  else if(debounceButton(buttonState) == LOW && buttonState == HIGH){
    buttonState = LOW;
  }
} //END buttonPressed

boolean debounceButton(boolean state)
{
  boolean stateNow = digitalRead(buttonPin);
  if(state!=stateNow){
    delay(10);
    stateNow = digitalRead(buttonPin);
  }
  return stateNow;
}

void setup() /*----( SETUP: RUNS ONCE )----*/
{
  pinMode(buttonPin,INPUT);
  attachInterrupt(0,buttonPressed,RISING);

  Serial.begin(9600);

} /*--(end setup )---*/

void loop() /*--(end setup )---*/
{
  
} /* --(end main loop )-- */
