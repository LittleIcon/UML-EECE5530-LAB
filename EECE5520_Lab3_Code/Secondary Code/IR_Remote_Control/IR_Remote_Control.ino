/* 
 *  Ernest Pellegrino
 *  April 15th 2022
 *  
 *  IR Remote Control
 */

#include <IRremote.hpp>

#define ENABLE 5
#define DIRA 3
#define DIRB 4

int receiver = 6; // Signal Pin of IR receiver to Arduino Digital Pin 6
uint32_t code = 0;

volatile int counter = 3;

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received
{
  // describing Remote IR codes 
  switch(code)
  { 
    // Raw-Data
    case 0xBA45FF00: 
      Serial.println("POWER");
    break;
    
    case 0xB847FF00: 
      Serial.println("FUNC/STOP"); 
    break;
    
    case 0xB946FF00: 
      Serial.println("VOL+");
    break;
    
    case 0xBB44FF00: 
      Serial.println("FAST BACK");
    break;
    
    case 0xBF40FF00: 
      Serial.println("PAUSE");
    break;
    
    case 0xBC43FF00: 
      Serial.println("FAST FORWARD");
    break;
    
    case 0xF807FF00: 
      Serial.println("DOWN");
      if (counter >= 1)
      {
        counter -= 1;
        if(counter >= 1){
          DC_Motor();
        }
        else{
          counter += 1;
          DC_Motor();
        }
      }
      else
      {
        Serial.println("Maximum counterclockwise speed reached");
        counter += 1;
      }
    break;
    
    case 0xEA15FF00: 
      Serial.println("VOL-");
    break;
    
    case 0xF609FF00: 
      Serial.println("UP");
      if (counter <= 7)
      {
        counter += 1;
        if(counter<=7){
          DC_Motor();
        }
        else{
          counter -= 1;
          DC_Motor();
        }
      }
      else
      {
        Serial.println("Maximum clockwise speed reached");
        counter -= 1;
      }
    break;
    
    case 0xE619FF00: 
      Serial.println("EQ");    
    break;
    
    case 0xF20DFF00: 
      Serial.println("ST/REPT");
    break;
    
    case 0xE916FF00: 
      Serial.println("0");
    break;
    
    case 0xF30CFF00: 
      Serial.println("1");
    break;
    
    case 0xE718FF00: 
      Serial.println("2");
    break;
    
    case 0xA15EFF00: 
      Serial.println("3");
    break;
    
    case 0xF708FF00: 
      Serial.println("4");
    break;
    
    case 0xE31CFF00: 
      Serial.println("5");
    break;
    
    case 0xA55AFF00: 
      Serial.println("6");
    break;
    
    case 0xBD42FF00: 
      Serial.println("7");
    break;
    
    case 0xAD52FF00: 
      Serial.println("8");
    break;
    
    case 0xB54AFF00: 
      Serial.println("9");
    break;
    
    default: 
      Serial.println("Other button ");
  }// End Case

  delay(100); // Do not get immediate repeat

} //END translateIR


void DC_Motor() // 
{
  switch(counter)
  { 
    case 1:
      digitalWrite(DIRA,LOW); //Rotate Counter-clockwise
      digitalWrite(DIRB,HIGH);
      Serial.println("Rotatation: Counter-clockwise");
      Serial.println("Speed: Full");
      analogWrite(ENABLE,255); //"Full" Speed
    break;
  
    case 2:
      digitalWrite(DIRA,LOW); //Rotate Counter-clockwise
      digitalWrite(DIRB,HIGH);
      Serial.println("Rotatation: Counter-clockwise");
      Serial.println("Speed: 3/4");
      analogWrite(ENABLE,191); //"3/4" Speed
    break;
  
    case 3:
      digitalWrite(DIRA,LOW); //Rotate Counter-clockwise
      digitalWrite(DIRB,HIGH);
      Serial.println("Rotatation: Counter-clockwise");
      Serial.println("Speed: 1/2");
      analogWrite(ENABLE,127); //"1/2" Speed
      
    break;
  
    case 4:
      digitalWrite(DIRA,LOW); //No rotation
      digitalWrite(DIRB,LOW);
      Serial.println("Rotation: None");
      Serial.println("Speed: 0");
      analogWrite(ENABLE,0); // "0" Speed
    break;
  
    case 5:
      digitalWrite(DIRA,HIGH); //Rotate Clockwise
      digitalWrite(DIRB,LOW);
      Serial.println("Rotatation: Clockwise");
      Serial.println("Speed: 1/2");
      analogWrite(ENABLE,127); //"1/2" Speed
    break;
  
    case 6:
      digitalWrite(DIRA,HIGH); //Rotate Clockwise
      digitalWrite(DIRB,LOW);
      Serial.println("Rotatation: Clockwise");
      Serial.println("Speed: 3/4");
      analogWrite(ENABLE,191); //"3/4" Speed
    break;

    case 7:
      digitalWrite(DIRA,HIGH); //Rotate Clockwise
      digitalWrite(DIRB,LOW);
      Serial.println("Rotatation: Clockwise");
      Serial.println("Speed: Full");
      analogWrite(ENABLE,255); //"Full" Speed
    break;

    default: 
      Serial.println("Error");
    
  }// End Case
} //END function

void setup() /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK);
} /*--(end setup )---*/

void loop() /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (IrReceiver.decode()) // have we received an IR signal?
  {
    code = IrReceiver.decodedIRData.decodedRawData; 
    translateIR();
    IrReceiver.resume(); // receive the next value
  }
} /* --(end main loop )-- */
