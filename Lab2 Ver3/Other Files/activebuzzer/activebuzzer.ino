//www.elegoo.com
//2016.12.08

int buzzer = 12;//the pin of the active buzzer
int flag = 0;

void setup()
{
 pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
}
void loop()
{
 unsigned char i;
 
 while(flag == 0)
 {
   //output a frequency
   for(i=0;i<80;i++)
   {
    digitalWrite(buzzer,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(1);//wait for 1ms
    }
    flag = 1;
  }
} 
