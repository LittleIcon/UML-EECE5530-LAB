/* 
 *  Ernest Pellegrino
 *  April 15th 2022
 *  
 *  Button Interrupt Service Routine (ISR) Test
 */

volatile boolean ledOn = false;

void setup()
{
  pinMode(8,OUTPUT);
  pinMode(2,INPUT);
  attachInterrupt(0,buttonPressed,RISING);
}

void loop()
{
  // put your main code here, to run repeatedly:

}

void buttonPressed()
{
  if(ledOn)
  {
    ledOn = false;
    digitalWrite(8,LOW);
  }
  else
  {
    ledOn = true;
    digitalWrite(8,HIGH);
  }
}
