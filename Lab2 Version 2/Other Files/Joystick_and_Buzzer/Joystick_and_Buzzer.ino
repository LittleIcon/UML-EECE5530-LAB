/*
 * Lab Assignment 2: Joystick and Buzzer
 * 
 * Output to Serial: Joystick data
 *   If the joystick is up send 'w'.
 *   If the joystick is down send 's'.
 *   If the joystick is left send 'a'.
 *   If the joystick is right send 'd'.
 * Read input from Serial: Buzzer 
 *   If there is a 'b' detected, buzz the buzzer.
 * 
 * Code written by Ernest Pellegrino
 */
 
/*
  Joystick
    GND to GND
    VCC to 5V
    VRx to A0
    VRy to A1
    SW to D2
    
    
  Accelerometer & Gyroscope
    VCC to 3.3V
    GND to GND
    SCL to SCL
    SDA to SDA
*/


// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int buzzer = 12; //the pin of the active buzzer

//Define Variables
int incomingByte = 0;
int buzz_time = 1;
int sleep = 100;

#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize Joystick and Buzzer
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  pinMode(buzzer,OUTPUT); //initialize the buzzer pin as an output

  // initialize MPU-6050
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

// initialize digital pin LED_BUILTIN as an output.
void loop() 
{
  int Switch = digitalRead(SW_pin);
  int X_axis = analogRead(X_pin);
  int Y_axis = analogRead(Y_pin);

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX = Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //go_up
  //if ((1) && (0))
  if (((X_axis >= 682) && (X_axis <= 1023)) && ((Y_axis >= 341) && (Y_axis <= 682)))
  //if ((682 < X_axis < 1023) && (341 < Y_axis < 682))
  {
    Serial.print('w');
    //Serial.print("11910");
    delay(sleep);
  }

  //go_down
  //if (0)
  if (((X_axis >= 0) && (X_axis <= 341)) && ((Y_axis >= 341) && (Y_axis <= 682)))
  //else if ((0 < X_axis < 341) && (341 < Y_axis < 682))
  {
    Serial.print('s');
    //Serial.print("11510");
    delay(sleep);
  }
  
  //go_left
  //if (0)
  if (((X_axis >= 341) && (X_axis <= 682)) && ((Y_axis >= 0) && (Y_axis <= 341)))
  //else if ((341 < Y_axis < 682) && (0 < X_axis < 341))
  {
    Serial.print('a');
    //Serial.print("9710");
    delay(sleep); 
  }
  
  //go_right
  //if (0)
  if (((X_axis >= 341) && (X_axis <= 682)) && ((Y_axis >= 682) && (Y_axis <= 1023)))
  //else if ((341 < Y_axis < 682) && (682 < X_axis < 1023))
  {
    Serial.print('d');
    //Serial.print('10010');
    delay(sleep);
  }

  /*
  Serial.print("Switch:  ");
  Serial.print(Switch);
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(X_axis);
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.print(Y_axis);
  Serial.print("\n\n");
  delay(500);
  */

  // read from the Serial port:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.print(incomingByte);
  }
  
  // Buzzer
  if (incomingByte == 'b')
  {
    digitalWrite(buzzer, HIGH);
    delay(buzz_time);
    digitalWrite(buzzer, LOW);
  }
  incomingByte = 0;
  
}
