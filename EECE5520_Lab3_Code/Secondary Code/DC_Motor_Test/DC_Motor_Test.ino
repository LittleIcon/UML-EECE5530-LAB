/* 
 *  Ernest Pellegrino
 *  April 14th 2022
 *  
 *  DC Motor
 */
#define ENABLE 5
#define DIRA 3
#define DIRB 4

int i;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Starting DC motor specified speed test:");
  delay(5000);
  
  Serial.println("Rotate Clockwise:");
  digitalWrite(DIRA,HIGH); //Rotate Clockwise
  digitalWrite(DIRB,LOW);

  Serial.println("Full Speed:");
  analogWrite(ENABLE,255); //"Full" Speed
  delay(3000);

  Serial.println("3/4 Speed:");
  analogWrite(ENABLE,191); //"3/4" Speed
  delay(3000);
  
  Serial.println("1/2 Speed:");
  analogWrite(ENABLE,127); //"1/2" Speed
  delay(3000);

  Serial.println("0 Speed:");
  analogWrite(ENABLE,0); // "0" Speed
  delay(3000);
  
  Serial.println("Rotate Counter-clockwise:");
  digitalWrite(DIRA,LOW); //Rotate Counter-clockwise
  digitalWrite(DIRB,HIGH);

  Serial.println("Full Speed:");
  analogWrite(ENABLE,255); //"Full" Speed
  delay(3000);

  Serial.println("3/4 Speed:");
  analogWrite(ENABLE,191); //"3/4" Speed
  delay(3000);
  
  Serial.println("1/2 Speed:");
  analogWrite(ENABLE,127); //"1/2" Speed
  delay(3000);

  Serial.println("0 Speed:");
  analogWrite(ENABLE,0); // "0" Speed
  delay(3000);

  Serial.println("Test Completed");
  delay(5000);
}

   
